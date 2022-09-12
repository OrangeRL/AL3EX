#include "Pyramid.h"
#include "GetMatrix.h"
#include "assert.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


void Pyramid::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
{
	assert(model_);
	assert(bodyModel);
	assert(taiyaModel);
	LoadModel(model_);
	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;
	LoadTexture(TextureManager::Load("oudanhodou.png"));
	worldTransform_.Initialize();
}

void Pyramid::Update()
{
	if (worldTransform_.translation_.x == 10.0f) {
		worldTransform_.rotation_.y = 3.2;
	}
	//worldTransform_.rotation_.y = 0.0;
	if (worldTransform_.translation_.x >= 10.1f) {
		worldTransform_.rotation_.y = 1.5;
	}

	MatUpdate();
}
void Pyramid::Reset()
{

}
void Pyramid::Draw(ViewProjection viewProjection)
{
	WorldTransform tempworld = worldTransform_;
	//s—ñŒvŽZ
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	tempworld.TransferMatrix();


	//model_->Draw(tempworld, viewProjection, textureHandle_);
	model_->Draw(tempworld, viewProjection);
	bodyModel->Draw(tempworld, viewProjection);
	taiyaModel->Draw(tempworld, viewProjection);
}

bool Pyramid::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void Pyramid::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void Pyramid::OnCollision()
{

}
