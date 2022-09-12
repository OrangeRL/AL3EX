#include "Enemy2.h"
#include "MyMath.h"
#include "Collsion.h"
#include "GetMatrix.h"
using namespace std;

Enemy2::Enemy2()
{
}

Enemy2::~Enemy2()
{

}

void Enemy2::Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
	worldTransform_.scale_ = { 0,0,0 };
	pManager.Initialize(partModel, tex);
}

void Enemy2::Update(Vector3 pPos, Audio* audio, SoundDataManager sdmanager)
{
	/*if (worldTransform_.translation_.z < 80) {
		OnCollision();
	}*/
	//pManager.Update(worldTransform_.translation_);
	if (worldTransform_.scale_.x < 0.5f)
	{
		worldTransform_.scale_.x += 0.01f;
		worldTransform_.scale_.y += 0.01f;
		worldTransform_.scale_.z += 0.01f;
	}
	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	approachMove = { 0.5,0.0f,-1.0 };
	leaveMove = { -0.5,0.0,-1.5 };

	switch (phase_) {
	case Phase::Approach:
	default://移動（ベクトルを加算）
		worldTransform_.rotation_.y = -3.7;
		worldTransform_.translation_ += approachMove;
		//worldTransform_.rotation_.y = 5.0;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.x > 20.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave://移動（ベクトルを加算）
		worldTransform_.rotation_.y = 3.5;
		worldTransform_.translation_ += leaveMove;
		//worldTransform_.rotation_.y = 0.0;
		/*if (worldTransform_.translation_.z > 45.0f) {
			worldTransform_.translation_.z = 10.0f;
		}*/
		if (worldTransform_.translation_.x < -20.0f) {
			phase_ = Phase::Approach;
		}
		break;
	}

	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Enemy2::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);

	//pManager.Draw(viewProjection_);
}

void Enemy2::OnCollision()
{
	isDead = true;
}

