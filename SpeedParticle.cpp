#include "SpeedParticle.h"
#include "MyMath.h"
#include "Collsion.h"
#include "GetMatrix.h"
using namespace std;

SpeedParticle::SpeedParticle()
{
}

SpeedParticle::~SpeedParticle()
{

}

void SpeedParticle::Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.translation_ = popPos;
	worldTransform_.scale_ = { 0,0,0 };
	pManager.Initialize(partModel, tex);
}

void SpeedParticle::Update(Vector3 pPos, Audio* audio, SoundDataManager sdmanager)
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
	worldTransform_.translation_.z -= 0.4f;
	/*if (worldTransform_.translation_.y > 1.0f)
	{*/

	//worldTransform_.rotation_.x -= 0.1f;
	//worldTransform_.rotation_.z += 0.01f;
	


	//s—ñŒvŽZ
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void SpeedParticle::Draw(ViewProjection viewProjection_)
{

	model_->Draw(worldTransform_, viewProjection_);
	//pManager.Draw(viewProjection_);
}

void SpeedParticle::OnCollision()
{
	isDead = true;
}

