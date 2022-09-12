#include "Building.h"
#include "GetMatrix.h"
void Building::Initialize(Model* model_)
{
	LoadModel(model_);
	LoadTexture(TextureManager::Load("Building.png"));
	worldTransform_.Initialize();
}

void Building::Update()
{
	//worldTransform_.rotation_.y -= 0.1;
	if (worldTransform_.translation_.z >= 100) {
		LoadTexture(TextureManager::Load("BIRU2.png"));
		worldTransform_.scale_ = { 8,20,5 };
		worldTransform_.translation_.y = { 20 };
		if (worldTransform_.translation_.z >= 110) {
			LoadTexture(TextureManager::Load("Building.png"));
			worldTransform_.scale_ = { 8,20,5 };
			worldTransform_.translation_.y = { 20 };
		}
	}

	if (worldTransform_.translation_.z >= 120) {
		LoadTexture(TextureManager::Load("BIRU2.png"));
	}
		if (worldTransform_.translation_.z >= 130) {
			LoadTexture(TextureManager::Load("Building.png"));

		}
	

	if (worldTransform_.translation_.z >= 150) {
		LoadTexture(TextureManager::Load("BIRU2.png"));
		worldTransform_.scale_ = { 8,20,5 };
		worldTransform_.translation_.y = { 20 };
		if (worldTransform_.translation_.z >= 180) {
			LoadTexture(TextureManager::Load("Building.png"));

		}
	}
	if(worldTransform_.translation_.z >= 500) {
		LoadTexture(TextureManager::Load("KONBINI2.png"));
		worldTransform_.scale_ = { 5,5,5 };
		worldTransform_.translation_.y = { 5 };
	}
	if (worldTransform_.translation_.z >= 550) {
		LoadTexture(TextureManager::Load("YOUBINKYOKU.png"));
		worldTransform_.scale_ = { 5,5,5 };
		worldTransform_.translation_.y = { 5 };
	}
	if (worldTransform_.translation_.z >= 600) {
		LoadTexture(TextureManager::Load("Building.png"));
		worldTransform_.scale_ = { 8,20,5 };
		worldTransform_.translation_.y = { 20 };
	}

	MatUpdate();
}

void Building::Draw(ViewProjection viewProjection, Vector3 shake)
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

bool Building::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void Building::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}
