#include "object.h"
#include <cassert>

object::object()
{
}

object::~object()
{
	//delete model_;
}

WorldTransform object::GetWorldTrans()
{
	return worldTransform_;
}
Vector3 object::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
void object::LoadModel(Model* model_)
{
	assert(model_);
	this->model_ = model_;
}

void object::LoadTexture(TextureHandle textureHandle_)
{
	this->textureHandle_ = textureHandle_;
}

void object::SetPos(Vector3 pos)
{
	worldTransform_.translation_ = pos;
	initPos = pos;
}

void object::SetScale(Vector3 scale)
{
	worldTransform_.scale_ = scale;
	initScale = scale;
}

void object::MatUpdate()
{
	//�s��v�Z
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//�s��̍Čv�Z(�X�V)
	worldTransform_.TransferMatrix();
}

Vector3 object::screenShake = { 0,0,0 };

void object::ScreenShake(Vector2 shake)
{
	screenShake = { shake.x,shake.y ,0 };
}
