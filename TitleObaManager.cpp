#include "TitleObaManager.h"
#include <cassert>
#include <random>

using namespace std;

TitleObaManager::TitleObaManager(Model* model_, Model* partModel, TextureHandle tex)
{
	Initialize(model_, partModel, tex);
}

TitleObaManager::~TitleObaManager()
{

}

void TitleObaManager::DeadInit()
{
	for (std::unique_ptr<TitleOba>& enemy : enemys)
	{
		enemy->revival();
	}
	eventSlayCount = 0;
	enemys.clear();
}

void TitleObaManager::Initialize(Model* model_, Model* partModel, TextureHandle tex)
{

	assert(model_);
	this->model_ = model_;
	this->partModel_ = partModel;
	this->tex = tex;
	debugText_ = DebugText::GetInstance();
}

void TitleObaManager::EnemyPop()
{
	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-200, 200);
	tempPopPos.y += RNG(0, 200);
	//tempPopPos.y += RNG(0, 0);
	tempPopPos.z += RNG(0, 0);

	unique_ptr<TitleOba> newEnemy = make_unique<TitleOba>();
	newEnemy->Initialize(model_, partModel_, tex, tempPopPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));

}

void TitleObaManager::Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;
	///*debugText_->SetPos(50, 220);
	//debugText_->Printf("slaycount:%d", eventSlayCount);*/
	//popCount++;
	//if ((popCount > 10 && maxEnemyCount < MAX_ENEMY) &&
	//	NotSpawnTerm == false)
	//{
	//	EnemyPop();
	//	popCount = 0;
	//}
	if (eventSlayCount < 30) {
		EnemyPop();
	}


	for (std::unique_ptr<TitleOba>& enemy : enemys)
	{
		enemy->Update(PPos, audio, sdmanager);
	/*	if (enemy->worldTransform_.translation_.z < popPos.z - 40.0f) {
			enemy->OnCollision();
		}
		if (enemy->worldTransform_.translation_.y < -22.0f) {
			enemy->OnCollision();
		}*/
		if (enemy->worldTransform_.translation_.z < popPos.z - 20.0f) {
			enemy->OnCollision();
		}
		if (enemy->worldTransform_.translation_.y < popPos.y - 20.0f) {
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

	enemys.remove_if([](std::unique_ptr<TitleOba>& enemy) {
		return enemy->IsDead();
		});
}

void TitleObaManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<TitleOba>& enemy : enemys)
	{
		enemy->Draw(viewProjection_);
	}
	//vpManager.Draw(viewProjection_);
}
void TitleObaManager::EnemyDead()
{
	for (std::unique_ptr<TitleOba>& enemy : enemys)
	{
		enemy->OnCollision();
	}
}

void TitleObaManager::EnemyReset()
{
	for (std::unique_ptr<TitleOba>& enemy : enemys)
	{
		enemy->OnCollision();
		eventSlayCount = 0;
	}
}

void TitleObaManager::EventStart(Audio* audio, SoundDataManager sdmanager, int PopEnemyNum)
{
	for (int i = 0; i < PopEnemyNum; i++)
	{
		//EnemyPop();
		//audio->PlayWave(sdmanager.enemyPopSE, false, 0.1f);
		if (eventSlayCount < 30) {
			eventSlayCount++;
		}
	}
}
