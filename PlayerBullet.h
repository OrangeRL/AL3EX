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
//���L����
//</summary>
class PlayerBullet
{
public:
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	PlayerBullet();

	/////<summary>
	/////������
	///</summary>
	///<paramname="model">���f��</param>
	///<paramname="position">�������W</param>

	void Initialize(Model* model, const Vector3& position);
	/////<summary>
	/////�X�V
	/////</summary>
	void Update();
	/////<summary>
	/////�`��
	/////</summary>
	void Draw(const ViewProjection& viewProjection);
	void TransferMatrix();
private:
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;
	//3D���f��
	Model* model_ = nullptr;
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	
};