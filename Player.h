#pragma once
#include "assert.h"
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

//<summary>
//���L����
//</summary>
class Player
{
public:
	PlayerBullet* bullet_ = nullptr;
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	Player();

	///<summary>///������///</summary>///<paramname="model">���f��</param>///<paramname="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, uint32_t textureHandle);
	///<summary>
	///�X�V
	///</summary>
	void Update();
	///<summary>
	///�`��
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw(ViewProjection& viewProjection);

	void Move();

	void TransferMatrix();

	void Attack();

private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
};