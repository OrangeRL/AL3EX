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
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
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
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//行列の再計算(更新)
	worldTransform_.TransferMatrix();
}

Vector3 object::screenShake = { 0,0,0 };

void object::ScreenShake(Vector2 shake)
{
	screenShake = { shake.x,shake.y ,0 };
}
