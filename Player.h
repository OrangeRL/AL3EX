#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "PlayerBullet.h"
#include "SpeedParticleManager.h"
#include "ModelManager.h"
#include <memory>
#include <list>
#include "BuildingManager.h"
#include "SoundDataManager.h"
//�J�����N���X
class RailCamera;
//<summary>
//���L����
//</summary>
class Player
{
public:

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>

	///<summary>///������///</summary>///<paramname="model">���f��</param>///<paramname="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model_, Model* bodyModel, Model* taiyaModel, WorldTransform* parent, const Vector3& position);

	///<summary>
	///�X�V
	///</summary>
	void Update();
	void SetSpawnPos(Vector3 pos);
	///<summary>
	///�`��
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw(ViewProjection& viewProjection);
	void SpriteDraw();
	void Move();

	void Attack();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
	void WindCollision();
	void nextStage();
	void resetStage();
	bool nexxtStage() { return NexxtStage; };
	bool NexxtStage = false;
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	void Reset();
	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void SetParent(WorldTransform* worldTransform) {
		worldTransform_.parent_ = worldTransform;
	}
	void boostUseReset() { boostUsed = false; };
	bool boostUse() { return boostUsed; }
	bool boostUnuse() { return boostUsed ;}
	bool IsSpeed() { return speedBooster; }
	bool IsGoal() { return isGoal; }
	void slow() { speedBooster = false; };
	void fast() { speedBooster = true; };
private:
	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;
	WorldTransform worldTransform_;
	// ���f��
	SpeedParticleManager* spManager;
	BuildingManager bManager;
	Model* model_ = nullptr;
	ModelManager* modelManager;
	SoundDataManager SDManager;
	Audio* audio_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏���
	Input* input_ = nullptr;
	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	Vector3 respawnPos;
	//�e
	std::list<std::unique_ptr<PlayerBullet>>bullets_;

	//�J�����N���X
	RailCamera* railCamera_ = nullptr;
	bool isWin_ = false;
	bool isGoal = false;
	enum class Phase {
		Drive,//�ڋ߂���
		Brake,//���E����

	};
	//�t�F�[�Y
	Phase phase_ = Phase::Drive;
	//�ړ��֌W
	float turnSpeed = 0.0;
	float speed = 0.4;
	float speedBoost = 0.4;
	float speedBoostTimer = 0;
	bool boostUsed = false;
	float InitMoveSpd = 0.21f;
	float moveSpeed = InitMoveSpd;
	float jumpSpd = 0.0f;
	float gravity = 0.01f;
	float windSpeed = 0.00f;
	float posY[3] = { 0,0,0 };
	//�X�L��
	Sprite* brakeIcon = nullptr;
	bool speedBooster = false;

};