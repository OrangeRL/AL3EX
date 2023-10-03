#include "Pedestrian.h"
#include "GetMatrix.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
void Pedestrian::Initialize(Model* model_)
{

	debugText_ = DebugText::GetInstance();
	LoadModel(model_);
	LoadTexture(TextureManager::Load("oba.png"));
	worldTransform_.Initialize();
	
}
void Pedestrian::Randomize()
{
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	pos = r;
}
void Pedestrian::Update()
{
	worldTransform_.scale_ = { 3.0f,2.0f,0.1f };
	//worldTransform_.translation_.x -= 0.1;
	LoadTexture(TextureManager::Load("oba.png"));
	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	approachMove = { 0.3,0.0f,0.0 };
	leaveMove = { -0.3,0.0,0.0 };

	if (worldTransform_.translation_.z >= 500) {
		approachMove = { 0.4,0.0f,0.0 };
		leaveMove = { -0.4,0.0,0.0 };
	}
	if (worldTransform_.translation_.z >= 1000) {
		approachMove = { 0.6,0.0f,0.0 };
		leaveMove = { -0.6,0.0,0.0 };
		LoadTexture(TextureManager::Load("superoba.png"));
	}
	if (worldTransform_.translation_.z >= 1600) {
		approachMove = { 0.8,0.0f,0.0 };
		leaveMove = { -0.8,0.0,0.0 };
		LoadTexture(TextureManager::Load("legendoba.png"));
	}
	//debugText_->SetPos(50, 100);
	//debugText_->Printf("randfloat:(%f)", pos);
	switch (phase_) {
	case Phase::Approach:
	default://移動（ベクトルを加算）
		worldTransform_.translation_ += approachMove;
		//worldTransform_.rotation_.y = 5.0;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.x > 20.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave://移動（ベクトルを加算）
		worldTransform_.translation_ += leaveMove;
		worldTransform_.rotation_.y = 0.0;
		/*if (worldTransform_.translation_.z > 45.0f) {
			worldTransform_.translation_.z = 10.0f;
		}*/
		if (worldTransform_.translation_.x < -20.0f) {
			phase_ = Phase::Approach;
		}
		break;
	}

	MatUpdate();
}



void Pedestrian::Update2()
{
	worldTransform_.scale_ = { 3.0f,2.0f,0.1f };
	//worldTransform_.translation_.x -= 0.1;
	LoadTexture(TextureManager::Load("sabakuteki2.png"));
	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	approachMove = { 0.3,0.0f,0.0 };
	leaveMove = { -0.3,0.0,0.0 };

	if (worldTransform_.translation_.z >= 500) {
		approachMove = { 0.4,0.0f,0.0 };
		leaveMove = { -0.4,0.0,0.0 };
	}

	debugText_->SetPos(50, 100);
	debugText_->Printf("randfloat:(%f)", pos);
	switch (phase_) {
	case Phase::Approach:
	default://移動（ベクトルを加算）
		worldTransform_.translation_ += approachMove;
		//worldTransform_.rotation_.y = 5.0;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.x > 20.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave://移動（ベクトルを加算）
		worldTransform_.translation_ += leaveMove;
		worldTransform_.rotation_.y = 0.0;
		/*if (worldTransform_.translation_.z > 45.0f) {
			worldTransform_.translation_.z = 10.0f;
		}*/
		if (worldTransform_.translation_.x < -20.0f) {
			phase_ = Phase::Approach;
		}
		break;
	}

	MatUpdate();
}
void Pedestrian::Reset()
{
	worldTransform_.translation_.y = 2.0;
	Randomize();
}
void Pedestrian::Draw(ViewProjection viewProjection, Vector3 shake)
{
	WorldTransform tempworld = worldTransform_;
	tempworld.translation_ += screenShake;
	tempworld.translation_ += shake;
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	tempworld.TransferMatrix();


	model_->Draw(tempworld, viewProjection, textureHandle_);
}

bool Pedestrian::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void Pedestrian::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void Pedestrian::OnCollision()
{
	worldTransform_.translation_.y = 200;
}
