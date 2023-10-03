#include "AsteroidManager.h"
#include <cassert>
#include <random>

using namespace std;

AsteroidManager::AsteroidManager(Model* model_, Model* partModel, TextureHandle tex)
{
	Initialize(model_, partModel, tex);
}

AsteroidManager::~AsteroidManager()
{

}

void AsteroidManager::DeadInit()
{
	for (std::unique_ptr<Asteroid>& enemy : enemys)
	{
		enemy->revival();
	}
	eventSlayCount = 0;
	enemys.clear();
}

void AsteroidManager::Initialize(Model* model_, Model* partModel, TextureHandle tex)
{

	assert(model_);
	this->model_ = model_;
	this->partModel_ = partModel;
	this->tex = tex;
	debugText_ = DebugText::GetInstance();
}

void AsteroidManager::EnemyPop()
{

	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-100, 100);
	tempPopPos.y += RNG(24, 200);
	//tempPopPos.y += RNG(0, 0);
	tempPopPos.z += RNG(10, 500);

	unique_ptr<Asteroid> newEnemy = make_unique<Asteroid>();
	newEnemy->Initialize(model_, partModel_, tex, tempPopPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));

}

void AsteroidManager::Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;
	/*debugText_->SetPos(50, 220);
	debugText_->Printf("slaycount:%d", eventSlayCount);*/
	//popCount++;
	//if ((popCount > 10 && maxEnemyCount < MAX_ENEMY) &&
	//	NotSpawnTerm == false)
	//{
	//	EnemyPop();
	//	popCount = 0;
	//}
	if (eventSlayCount < 50) {
		EnemyPop();
	}


	for (std::unique_ptr<Asteroid>& enemy : enemys)
	{
		enemy->Update(PPos, audio, sdmanager);
		if (enemy->worldTransform_.translation_.z < popPos.z - 40.0f || enemy->worldTransform_.translation_.z > 2200) {
			enemy->OnCollision();
		}
		if (enemy->worldTransform_.translation_.y < popPos.y - 40.0f) {
			enemy->OnCollision();
		}
		if (enemy->IsDead())
		{
			if (eventSlayCount > 0)
			{
				eventSlayCount -= 2;
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

	enemys.remove_if([](std::unique_ptr<Asteroid>& enemy) {
		return enemy->IsDead();
		});
}

void AsteroidManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<Asteroid>& enemy : enemys)
	{
		enemy->Draw(viewProjection_);
	}
	//vpManager.Draw(viewProjection_);
}
void AsteroidManager::EnemyDead()
{
	for (std::unique_ptr<Asteroid>& enemy : enemys)
	{
		enemy->OnCollision();
	}
}

void AsteroidManager::EnemyReset()
{
	for (std::unique_ptr<Asteroid>& enemy : enemys)
	{
		enemy->OnCollision();
		eventSlayCount = 0;
	}
}

void AsteroidManager::EventStart(Audio* audio, SoundDataManager sdmanager, int PopEnemyNum)
{
	for (int i = 0; i < PopEnemyNum; i++)
	{
		//EnemyPop();
		//audio->PlayWave(sdmanager.enemyPopSE, false, 0.1f);
		if (eventSlayCount < 50) {
			eventSlayCount++;
		}
	}
}
