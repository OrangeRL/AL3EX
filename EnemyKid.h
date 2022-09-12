#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "EnemyBullet.h"
#include "DebugText.h"
#include "Audio.h"

enum class Phase {
	Approach,
	Leave,
	OnWall,
};

class EnemyKid : public object
{
public:
	EnemyKid();
	~EnemyKid();
	void Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos);
	void Update(Vector3 pPos, Audio* audio);
	void Draw(ViewProjection viewProjection_);
	void OnCollision();

	void PhaseChange(Phase phase_);

	bool IsDead() { return isDead; }
	void revival() { isDead = false; };

	void OnWallMove();

	void CheckHitBox(WorldTransform box);

	void SetAttackCount(int aCount) { attackCount = aCount; };

	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

private:
	bool isDead = false;
	float moveSpd = 0.3f;

	bool hitGround = false;
	bool hitCeiling = false;

	bool isBoxCol = false;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	Phase phase_ = Phase::Approach;

	int attackCount;
	static const int MAX_ATTACK_COUNT = 300;

	//�Ȃ܂ۂ�delete�ł��Ȃ��̂Ŋ�Ȃ�
	DebugText* debugText = DebugText::GetInstance();

	//�v���C���[�ւ̃x�N�g��
	Vector3 pCenterVec = { 0,0,0 };

	Vector3 sideVec = { 0,0,0 };

	Vector3 moveVec = { 0,0,0 };

	float pdegree = 0;


	void MoveOpp();
	void MoveCenter();
	void Attack(Audio* audio);

};