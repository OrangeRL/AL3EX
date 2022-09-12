#include "EnemyManager.h"
#include <cassert>
#include <random>

using namespace std;

EnemyManager::EnemyManager(Model* model_, Model* partModel, TextureHandle tex)
{
	Initialize(model_, partModel, tex);

}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::DeadInit()
{
	for (std::unique_ptr<Enemy2>& enemy : enemys)
	{
		enemy->revival();
	}
	eventSlayCount = 0;
	enemys.clear();
}

void EnemyManager::Initialize(Model* model_, Model* partModel, TextureHandle tex)
{

	assert(model_);
	this->model_ = model_;
	this->partModel_ = partModel;
	this->tex = tex;
	debugText_ = DebugText::GetInstance();
}

void EnemyManager::EnemyPop()
{

	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-20, 20);
	tempPopPos.y = 0.0f;
	tempPopPos.z += RNG(600, 2300);

	unique_ptr<Enemy2> newEnemy = make_unique<Enemy2>();
	newEnemy->Initialize(model_, partModel_, tex, tempPopPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));
	
}

void EnemyManager::Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;
	debugText_->SetPos(50, 220);
	debugText_->Printf("slaycount:%d", eventSlayCount);
	//popCount++;
	//if ((popCount > 10 && maxEnemyCount < MAX_ENEMY) &&
	//	NotSpawnTerm == false)
	//{
	//	EnemyPop();
	//	popCount = 0;
	//}
	if (eventSlayCount < 4) {
		EnemyPop();
	}

	
	for (std::unique_ptr<Enemy2>& enemy : enemys)
	{
		enemy->Update(PPos, audio, sdmanager);
		if (enemy->worldTransform_.translation_.z < popPos.z-30.0f) {
			enemy->OnCollision();
		}

		
		if (enemy->IsDead())
		{
			if (eventSlayCount > 0 && enemy->worldTransform_.translation_.z < 2300)
			{
				eventSlayCount-=2;
				//enemy->OnCollision();
			}
		}
		if (enemy->IsDead())
		{
			//eventSlayCount--;
			//eventSlayCount = 0;
		}
		if (NotSpawnTerm)
		{
			enemy->OnCollision();
		}
		
	}

	enemys.remove_if([](std::unique_ptr<Enemy2>& enemy) {
		return enemy->IsDead();
		});
}

void EnemyManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<Enemy2>& enemy : enemys)
	{
		enemy->Draw(viewProjection_);
	}
	//vpManager.Draw(viewProjection_);
}
void EnemyManager::EnemyDead()
{
	for (std::unique_ptr<Enemy2>& enemy : enemys)
	{
		enemy->OnCollision();
	}
}

void EnemyManager::EnemyReset()
{
	for (std::unique_ptr<Enemy2>& enemy : enemys)
	{
		enemy->OnCollision();
		eventSlayCount = 0;
	}
}

void EnemyManager::EventStart(Audio* audio, SoundDataManager sdmanager, int PopEnemyNum)
{
	for (int i = 0; i < PopEnemyNum; i++)
	{
		//EnemyPop();
		//audio->PlayWave(sdmanager.enemyPopSE, false, 0.1f);
		if (eventSlayCount < 4) {
		eventSlayCount++;
		}
	}
}
