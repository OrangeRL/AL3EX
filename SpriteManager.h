#pragma once
#include "object.h"
#include "ViewProjection.h"
#include "Input.h"
#include "Utill.h"
#include "PlayerBullet.h"
#include "DebugText.h"
#include <memory>
#include <list>
#include "Audio.h"


class SpriteManager : public object
{
public:

	//�Ȃ܂ۂ�delete�ł��Ȃ��̂Ŋ�Ȃ�
	Input* input_ = Input::GetInstance();
	DebugText* debugText = DebugText::GetInstance();

	//���x�N�g��
	Vector3 sideVec = { 0,0,0 };
	//���ʃx�N�g��
	Vector3 centerVec = { 0,0,0 };
	//������x�N�g��
	Vector3 upVec = { 0,1,0 };

	void End();

	void Initialize(Model* model_, Model* bodyModel, Model* taiyaModel);
	void SetSpawnPos(Vector3 pos);
	void Update();
	void UpdateMatrixAndMove();
	void Draw(ViewProjection viewProjection_);
	void SpriteDraw();

	bool CheckHitBox(WorldTransform box);

	void JumpReady();
	void StockPlus();
	void OnDamage(int damage);

	//���G���Ԃ���I�H
	int mutekiTimer = 0;

	float GetJumpSpd() { return jumpSpd; };

	//�����W�����v�C�x���g�p
	void EnforceJumpOnCol();

	//�S�[���p
	void EnforceGoalOnCol();

	bool isJumpCheck = false;

	bool IsDash() { return isDash; };
	void SetMuteki() { mutekiTimer = MUTEKI_TIME; };

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	float GetMouseVRota() { return verticalRotation; };

	float enforceJumpSpd = 2.0f;

	bool IsDead() { return isDead; };

	void HealEffect(int heal);
	void DeadInit();

	int GetBulletCool() { return bulletCool; };

	int GetHeartCount() { return getHeartCount; };
	void HeartCountUp() { getHeartCount++; };

	bool GetNoHitFlag() { return nohitFlag; };

	Vector4 scrennAlpha;
	//Vector4 blueA;
	//float redA = 0;
	//float blueA = 0;

private:

	WorldTransform prevPos;

	bool isDead = false;

	bool hitGround = false;
	bool hitCeiling = false;

	bool oldIsJumpCheck = false;

	bool isBossMove = false;

	bool isDamageHit = false;

	//�X�e�[�^�X�֌W
	int bulletCool = 0;
	static const int MAX_BULLET_COOL = 30;

	//�ړ������l
	Vector3 move = { 0,0,0 };

	//�ړ������̃x�N�g��
	Vector3 moveVec;

	Vector3 tempMoveVec;
	Vector3 tempSideVec;

	Vector3 respawnPos;

	//�c�����̉�]�p�x
	float verticalRotation = 0;
	float horizontalRotation = 0;

	//�}�E�X�̊��x
	float mouseSpd = 0.005f;

	//hp
	int stock = 3;
	int hp = 30;
	static const int MUTEKI_TIME = 120;

	//�ړ��֌W
	float InitMoveSpd = 0.21f;
	float moveSpeed = InitMoveSpd;
	float jumpSpd = 0.0f;
	float gravity = 0.01f;
	bool jumpEfectManageFlag = false;

	//�X�L���֌W
	float oldMoveSpd = 0;
	int dashCoolTime = 0;
	bool isDash = false;

	float posY[3] = { 0,0,0 };

	//���U���g�֌W
	int getHeartCount = 0;
	bool nohitFlag = true;

	//�`��֌W
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;

	static const int MAX_STACK = 10;
	Sprite* newstocks[MAX_STACK] = { nullptr };

	Vector2 HPPOS_INIT[MAX_STACK];

	Sprite* skillIconSp = nullptr;
	Sprite* skillCoolAlpha = nullptr;
	Sprite* backWhite = nullptr;
	Sprite* backWhite2 = nullptr;
	Sprite* backWhite3 = nullptr;
	Sprite* lShift = nullptr;
	Sprite* shotIconSp = nullptr;
	Sprite* mouseIcon = nullptr;
	Sprite* jumpIcon = nullptr;
	Sprite* spaceIcon = nullptr;

	Sprite* hpRed = nullptr;

	void Move();
	void Dash();
	void InputMove();
	void Attack();
	void DamageHitEffect();

	void PlayerUpdateMatrix();
};

