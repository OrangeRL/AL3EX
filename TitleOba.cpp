#include "TitleOba.h"
#include "MyMath.h"
#include "Collsion.h"
#include "GetMatrix.h"
using namespace std;

TitleOba::TitleOba()
{
}

TitleOba::~TitleOba()
{

}

void TitleOba::Initialize(Model* model_, Model* partModel, TextureHandle tex, Vector3 popPos)
{
	worldTransform_.Initialize();
	this->model_ = model_;
	//this->textureHandle_ = TextureManager::Load("enemy.png");;

	worldTransform_.translation_ = popPos;
	worldTransform_.scale_ = { 0,0,0 };
	pManager.Initialize(partModel, tex);
	worldTransform_.rotation_.z = RNG(0, 20);

}

void TitleOba::Update(Vector3 pPos, Audio* audio, SoundDataManager sdmanager)
{
	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };
	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}
	/*if (worldTransform_.translation_.z < 80) {
		OnCollision();
	}*/
	//pManager.Update(worldTransform_.translation_);
	/*
		worldTransform_.scale_.x = 2.5f;
		worldTransform_.scale_.y = 2.5f;
		worldTransform_.scale_.z = 0.1f;
	*/
	if (worldTransform_.scale_.x < 2.5f)
	{
		worldTransform_.scale_.x += 0.1f;
		worldTransform_.scale_.y += 0.1f;
	}
	worldTransform_.scale_.z = 0.01f;
	worldTransform_.translation_.x -= 0.05f;
	/*if (worldTransform_.translation_.y > 1.0f)
	{*/
	worldTransform_.translation_.y -= 0.05f;
	//}

	//worldTransform_.rotation_.y -= 0.05f;
	
	//switch (phase_) {
	//case Phase::Approach:
	//default://移動（ベクトルを加算）
	//	worldTransform_.rotation_.y -= 0.03f;
	//	
	//	//規定の位置に到達したら離脱
	//	if (worldTransform_.rotation_.y < -5.0f) {
	//		phase_ = Phase::Leave;
	//	}
	//	break;
	//case Phase::Leave://移動（ベクトルを加算）
	//	
	//	worldTransform_.rotation_.y += 0.03f;
	//	if (worldTransform_.rotation_.x > 5.0f) {
	//		phase_ = Phase::Approach;
	//	}
	//	break;
	//}
	
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void TitleOba::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_);

	//pManager.Draw(viewProjection_);
}

void TitleOba::OnCollision()
{
	isDead = true;
}

