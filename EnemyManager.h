#pragma once
#include "Enemy2.h"
#include "Model.h"
#include <memory>
#include <list>
#include "DebugText.h"
#include "SoundDataManager.h"

class EnemyManager
{
public:
	std::list<std::unique_ptr<Enemy2>> enemys;

	void Initialize(Model* model_, Model* partModel, TextureHandle tex);
	void EnemyPop();
	void Update(Vector3 PPos, bool NotSpawnTerm, Audio* audio, SoundDataManager sdmanager);
	void Draw(ViewProjection viewProjection_);
	void EnemyDead();
	void EnemyRevival();
	void EnemyReset();
	void EventStart( Audio* audio, SoundDataManager sdmanager, int PopEnemyNum = 1);
	
	int GetEventCount() { return eventSlayCount; };
	bool IsBossBattle() { return isBossBattle; };
	EnemyManager(Model* model_, Model* partModel, TextureHandle tex);
	~EnemyManager();

	void DeadInit();
	std::list<std::unique_ptr<Enemy2>> camel;
private:
	int popCount = 0;

	int eventSlayCount = 0;
	bool isBossBattle = false;
	Vector3 popPos = { 0,0,0 };
	DebugText* debugText_ = nullptr;
	//VanishParticleManager vpManager;
	
	//パソコンが壊れたら嫌なので一応エネミー発生数の上限をつけておく
	int maxEnemyCount = 0;
	static const int MAX_ENEMY = 0;

	Model* model_ = nullptr;
	Model* partModel_ = nullptr;
	TextureHandle tex = 0;
};

