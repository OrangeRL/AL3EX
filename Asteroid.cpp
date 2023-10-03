#include "Asteroid.h"
#include "MyMath.h"
#include "Collsion.h"
#include "GetMatrix.h"
using namespace std;

Asteroid::Asteroid()
{
}

Asteroid::~Asteroid()
{
	
}

void Asteroid::Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
	worldTransform_.scale_ = { 0,0,0 };
	pManager.Initialize(partModel, tex);
}

void Asteroid::Update(Vector3 pPos, Audio* audio, SoundDataManager sdmanager)
{
	/*if (worldTransform_.translation_.z < 80) {
		OnCollision();
	}*/
	//pManager.Update(worldTransform_.translation_);
	if (worldTransform_.scale_.x < 1.0f)
	{
		worldTransform_.scale_.x += 0.1f;
		worldTransform_.scale_.y += 0.1f;
		worldTransform_.scale_.z += 0.1f;
	}
	worldTransform_.translation_.z -= 0.6f;
	/*if (worldTransform_.translation_.y > 1.0f)
	{*/
	worldTransform_.translation_.y -= 0.4f;
	//}
	
	//worldTransform_.rotation_.x -= 0.1f;
	worldTransform_.rotation_.z += 0.005f;
	//s—ñŒvŽZ
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Asteroid::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);

	//pManager.Draw(viewProjection_);
}

void Asteroid::OnCollision()
{
	isDead = true;
}

