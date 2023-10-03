#pragma once
#include "Pedestrian.h"
#include "object.h"
#include "audio.h"
#include <memory>
#include <list>

class PedestrianManager
{
public:
	void Initialize(Model* model_);
	void Update();
	void Update2();
	void Draw(ViewProjection viewProjection_);

	const std::list <std::unique_ptr<Pedestrian>>& GetObjects() {
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
	std::list <std::unique_ptr<Pedestrian>> Objects;
	float pos;


	Model* model_ = nullptr;
	Vector3 spawnPos = { 0,20,0 };
	Vector3 bossStagePos = { 0,0,0 };
	Vector3 bossStageScale = { 0,0,0 };
};