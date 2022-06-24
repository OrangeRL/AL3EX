#pragma once
#include "assert.h"
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
//<summary>
//�G
//</summary>
class Enemy
{
public:
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	Enemy();

	///<summary>///������///</summary>///<paramname="model">���f��</param>///<paramname="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, const Vector3& position,uint32_t textureHandle);
	///<summary>
	///�X�V
	///</summary>
	void Update();
	///<summary>
	///�`��
	///</summary>
	void Draw(ViewProjection& viewProjection);

	void TransferMatrix();
	void Move();
	//�s���t�F�[�Y
	enum class Phase {
		Approach,   //�ڋ߂���
		Leave,      //���E����
	};
	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
private:
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//3D���f��
	Model* model_ = nullptr;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���x
	Vector3 velocity_;
};