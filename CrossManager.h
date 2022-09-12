#pragma once
#include "Cross.h"
#include "object.h"
#include <memory>
#include <list>

class CrossManager
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection viewProjection_);

	const std::list <std::unique_ptr<Cross>>& GetObjects() {
		return Objects;
	};


	Vector3 GetSpawnPos();
	void SetSpawnPos(Vector3 pos, float yScale);
	void SetBox(Vector3 pos, Vector3 scale);
	void EventSetBox(Vector3 pos, Vector3 scale);
	void EventStart(Vector3 playerPos);
	void EventEnd();

	Vector3 GetBossStagePos() { return bossStagePos; };
	Vector3 GetBossStageScale() { return bossStageScale; };

	void BossBattleStart();
	void BossBattleEnd();

	void EnforceEventStart();
	void EnforceEventEnd();

	void DeadInit();

private:
	std::list <std::unique_ptr<Cross>> Objects;
	float pos;


	Model* model_ = nullptr;
	Vector3 spawnPos = { 0,20,0 };
	Vector3 bossStagePos = { 0,0,0 };
	Vector3 bossStageScale = { 0,0,0 };
};