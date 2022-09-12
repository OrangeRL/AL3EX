#include "BoxObj.h"
#include "GetMatrix.h"
void BoxObj::Initialize(Model* model_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("Road2.png"));
	worldTransform_.Initialize();
}

void BoxObj::Update()
{
	LoadTexture(TextureManager::Load("Road2.png"));
	MatUpdate();
}

void BoxObj::Update2()
{
	LoadTexture(TextureManager::Load("sabakuroad.png"));
	MatUpdate();
}

void BoxObj::Update3()
{
	LoadTexture(TextureManager::Load("rainbow.png"));
	MatUpdate();
}

void BoxObj::Draw(ViewProjection viewProjection, Vector3 shake)
{
	WorldTransform tempworld = worldTransform_;
	tempworld.translation_ += screenShake;
	tempworld.translation_ += shake;
	//s—ñŒvŽZ
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	tempworld.TransferMatrix();


	model_->Draw(tempworld, viewProjection, textureHandle_);
}

bool BoxObj::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void BoxObj::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}
