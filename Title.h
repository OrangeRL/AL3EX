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
#include "Enemy.h"

using namespace MathUtility;

///<summary>
///�G
///</summary>

class Title {
public:
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	Title();

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
	void OnCollision();
	void Restart();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	DebugText* debugText_ = nullptr;
	Enemy* enemy_ = nullptr;
};