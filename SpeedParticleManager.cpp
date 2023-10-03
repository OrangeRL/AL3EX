#include "SpeedParticleManager.h"
#include <cassert>
#include <random>

using namespace std;

SpeedParticleManager::SpeedParticleManager(Model* model_, Model* partModel, TextureHandle tex)
{
	Initialize(model_, partModel, tex);
}

SpeedParticleManager::~SpeedParticleManager()
{

}

void SpeedParticleManager::DeadInit()
{
	for (std::unique_ptr<SpeedParticle>& enemy : enemys)
	{
		enemy->revival();
	}
	eventSlayCount = 0;
	enemys.clear();
}

void SpeedParticleManager::Initialize(Model* model_, Model* partModel, TextureHandle tex)
{

	assert(model_);
	this->model_ = model_;
	this->partModel_ = partModel;
	this->tex = tex;
	debugText_ = DebugText::GetInstance();
	input_ = Input::GetInstance();
}

void SpeedParticleManager::EnemyPop()
{

	Vector3 tempPopPos = popPos;
	tempPopPos.x += RNG(-1.0f, 0.0f);
	tempPopPos.y += RNG(0, 1);
	//tempPopPos.y += RNG(0, 0);
	tempPopPos.z += RNG(-10, 10);

	unique_ptr<SpeedParticle> newEnemy = make_unique<SpeedParticle>();
	newEnemy->Initialize(model_, partModel_, tex, tempPopPos);

	//“G‚ð“o˜^‚·‚é
	enemys.push_back(std::move(newEnemy));

}

void SpeedParticleManager::Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager)
{
	maxEnemyCount = enemys.size();
	popPos = PPos;
	//debugText_->SetPos(50, 220);
	//debugText_->Printf("slaycount:%d", eventSlayCount);
	//popCount++;
	//if ((popCount > 10 && maxEnemyCount < MAX_ENEMY) &&
	//	NotSpawnTerm == false)
	//{
	//	EnemyPop();
	//	popCount = 0;
	//}
	if (eventSlayCount < 10) {
		EnemyPop();
	}


	for (std::unique_ptr<SpeedParticle>& enemy : enemys)
	{
		enemy->Update(PPos, audio, sdmanager);
		if (enemy->worldTransform_.translation_.z < popPos.z - 20.0f) {
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

	enemys.remove_if([](std::unique_ptr<SpeedParticle>& enemy) {
		return enemy->IsDead();
		});
	//switch (phase_) {
	//case Phase::Drive:
	//default://ˆÚ“®iƒxƒNƒgƒ‹‚ð‰ÁŽZj
	//	if (input_->PushKey(DIK_SPACE) == 1) {
	//		phase_ = Phase::Brake;
	//	}

	//	if (speed2 < 5.0f)
	//	{
	//		speed2 += 0.001f;
	//	}

	//	if (speed2 > 5.00f) {
	//		speed2 = 5.0f;
	//	}


	//	break;

	//case Phase::Brake://ˆÚ“®iƒxƒNƒgƒ‹‚ð‰ÁŽZj
	//	if (speed2 >= 0.03f) {
	//		speed2 -= 0.001;
	//	}
	//	if (speed2 < 0.03f) {
	//		speed2 = 0.03f;
	//	}

	//	if (input_->PushKey(DIK_SPACE) == 0) {
	//		phase_ = Phase::Drive;
	//	}
	//	break;
	//}

}

void SpeedParticleManager::Draw(ViewProjection viewProjection_)
{
	for (std::unique_ptr<SpeedParticle>& enemy : enemys)
	{
		/*if(speed2>1.0f)
		{*/
		enemy->Draw(viewProjection_);
		//}
	}
	//vpManager.Draw(viewProjection_);
}
void SpeedParticleManager::EnemyDead()
{
	for (std::unique_ptr<SpeedParticle>& enemy : enemys)
	{
		enemy->OnCollision();
	}
}

void SpeedParticleManager::EnemyReset()
{
	for (std::unique_ptr<SpeedParticle>& enemy : enemys)
	{
		enemy->OnCollision();
		eventSlayCount = 0;
	}
}

void SpeedParticleManager::EventStart(Audio* audio, SoundDataManager sdmanager, int PopEnemyNum)
{
	for (int i = 0; i < PopEnemyNum; i++)
	{
		//EnemyPop();
		//audio->PlayWave(sdmanager.enemyPopSE, false, 0.1f);
		if (eventSlayCount < 10) {
			eventSlayCount++;
		}
	}
}
