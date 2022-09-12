#include "EnemyKid.h"
#include "MyMath.h"
#include "Collsion.h"
#include "GetMatrix.h"

using namespace std;

EnemyKid::EnemyKid()
{
}

EnemyKid::~EnemyKid()
{

}

void EnemyKid::Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
	worldTransform_.scale_ = { 0,0,0 };
}

void EnemyKid::Update(Vector3 pPos, Audio* audio)
{
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});


	if (worldTransform_.scale_.x < 1.5f)
	{
		worldTransform_.scale_.x += 0.01f;
		worldTransform_.scale_.y += 0.01f;
		worldTransform_.scale_.z += 0.01f;
	}

	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}



	worldTransform_.translation_ += moveVec;

	//s—ñŒvŽZ
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void EnemyKid::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);


	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}

	if (false)
	{
		debugText->SetPos(50, 200);
		debugText->Printf("kakudo %f", pdegree);
		debugText->SetPos(50, 230);
		debugText->Printf("moveVec %f %f %f", moveVec.x, moveVec.y, moveVec.z);
	}
}

void EnemyKid::OnCollision()
{
	isDead = true;
}





