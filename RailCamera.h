#pragma once
#include <cassert>
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

//���@�N���X�̑O���O��
class Player;

///<summary> 
///���[���J����
///</summary>
class RailCamera {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RailCamera() = default;


	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	void OnCollision();
	void WindCollision();
	void Restart();
	/// <summary>
	/// �r���[�v���W�F�N�V�������擾
	/// </summary>
	const ViewProjection& GetViewProjection() { return viewProjection_;}

	Matrix4 GetWorldMatrix() const { return worldTransform_.matWorld_; }
	//���[���h�s����擾
	WorldTransform* GetWorldMatrix() { return &worldTransform_;}
	void boostUseReset() { boostUsed = false; };
	bool boostUse() { return boostUsed; }
private:
	enum class Phase {
		Drive,//�ڋ߂���
		Brake,//���E����
	};
	//�t�F�[�Y
	Phase phase_ = Phase::Drive;
	float speed = 0.4;
	float speedBoost = 0.4;
	float speedBoostTimer = 0;
	bool boostUsed = false;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = DebugText::GetInstance();

	bool isWin_ = false;
};