#pragma once
#include "assert.h"
#include "Model.h"
#include "WorldTransform.h"

///<summary>
///���L�����̒e
///</summary>
class PlayerBullet
{

public:

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	PlayerBullet();

	///<summary>
	///������
	///</summary>
	///<paramname="model">���f��</param>
	///<paramname="position">�������W</param>
	///<paramname="Velocity">�������W</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	///<summary>
	///�X�V
	///</summary>
	void Update();

	///<summary>
	///�`��
	///</summary>
	///<paramname="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);
	void TransferMatrix();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//PlayerBullet* bullet_ = nullptr;
	//���x
	Vector3 velocity_;
};