#include "Cross.h"
#include "GetMatrix.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
void Cross::Initialize(Model* model_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("oudanhodou.png"));
	worldTransform_.Initialize();
}

void Cross::Update()
{
	//worldTransform_.translation_.x -= 0.1;


	MatUpdate();
}
void Cross::Reset()
{
	
}
void Cross::Draw(ViewProjection viewProjection, Vector3 shake)
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

bool Cross::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void Cross::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void Cross::OnCollision()
{
	
}
