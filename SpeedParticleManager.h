#pragma once
#include "SpeedParticle.h"
#include "Model.h"
#include <memory>
#include <list>
#include "DebugText.h"
#include "SoundDataManager.h"
#include "Input.h"

class SpeedParticleManager
{
public:
	std::list<std::unique_ptr<SpeedParticle>> enemys;

	void Initialize(Model* model_, Model* partModel, TextureHandle tex);
	void EnemyPop();
	void Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager);
	void Draw(ViewProjection viewProjection_);
	void EnemyDead();
	void EnemyRevival();
	void EnemyReset();
	void EventStart(Audio* audio, SoundDataManager sdmanager, int PopEnemyNum = 1);

	int GetEventCount() { return eventSlayCount; };
	bool IsBossBattle() { return isBossBattle; };
	SpeedParticleManager(Model* model_, Model* partModel, TextureHandle tex);
	~SpeedParticleManager();

	void DeadInit();
	std::list<std::unique_ptr<SpeedParticle>> camel;
private:
	int popCount = 0;
	float speed2 = 0.0f;
	int eventSlayCount = 0;
	bool isBossBattle = false;
	Vector3 popPos = { 0,0,0 };
	DebugText* debugText_ = nullptr;
	//VanishParticleManager vpManager;
	Input* input_ = nullptr;
	//パソコンが壊れたら嫌なので一応エネミー発生数の上限をつけておく
	int maxEnemyCount = 0;
	static const int MAX_ENEMY = 0;

	Model* model_ = nullptr;
	Model* partModel_ = nullptr;
	TextureHandle tex = 0;

	enum class Phase {
		Drive,//接近する
		Brake,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Drive;
};

