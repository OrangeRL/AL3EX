#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "EnemyBullet.h"
#include "DebugText.h"
#include "Input.h"

#include "ParticleManager.h"
#include "SoundDataManager.h"


class SpeedParticle : public object
{
public:
	SpeedParticle();
	~SpeedParticle();
	void Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos);
	void Update(Vector3 pPos, Audio* audio, SoundDataManager sdmanager);
	void Draw(ViewProjection viewProjection_);
	void OnCollision();

	bool IsDead() { return isDead; }
	void revival() { isDead = false; };

	void OnWallMove();

	void CheckHitBox(WorldTransform box);

	void SetAttackCount(int aCount) { attackCount = aCount; };

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
	//float speed = 0.4f;
private:
	bool isDead = false;
	float moveSpd = 0.3f;
	Input* input_ = nullptr;
	bool hitGround = false;
	bool hitCeiling = false;

	bool isBoxCol = false;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	int attackCount;
	static const int MAX_ATTACK_COUNT = 300;

	//なまぽでdeleteできないので危ない
	DebugText* debugText_ = DebugText::GetInstance();

	//プレイヤーへのベクトル
	Vector3 pCenterVec = { 0,0,0 };

	Vector3 sideVec = { 0,0,0 };

	Vector3 moveVec = { 0,0,0 };

	float pdegree = 0;

	ParticleManager pManager;

	void MoveOpp();
	void MoveCenter();
	void Attack(Audio* audio, SoundDataManager sdmanager);
	
	enum class Phase {
		Drive,//接近する
		Brake,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Drive;
};