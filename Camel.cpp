#include "Camel.h"
#include "GetMatrix.h"
#include "assert.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


void Camel::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
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

void Camel::Update()
{
	
	if(worldTransform_.translation_.z<=10.0f){
		Reset();
	}

	/*if (worldTransform_.translation_.x == 10.0f) {
		worldTransform_.rotation_.y = 3.2;
	}*/
	//worldTransform_.rotation_.y = 0.0;
	/*if (worldTransform_.translation_.x >= 10.1f) {
		worldTransform_.rotation_.y = 1.5;
	}*/
	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	approachMove = { 0.5,0.0f,-1.0 };
	leaveMove = { -0.5,0.0,-1.5};

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


	MatUpdate();
}
void Camel::Reset()
{
	OnCollision();
	//worldTransform_.translation_.y = 0.0;
	//for (int i = 0; i < 2; i++)
	//{
	//	srand(time(NULL));
	//	pos = rand() % 5;
	//	//worldTransform_.translation_={ pos + 20 + i * 2.0f, 2.0f, 10.0f + i * 250.0f };
	//}
	//worldTransform_.translation_.z -= 300;
	//Randomize();
}
void Camel::Randomize()
{
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	pos = r;
}
void Camel::Draw(ViewProjection viewProjection)
{
	WorldTransform tempworld = worldTransform_;
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	tempworld.TransferMatrix();


	//model_->Draw(tempworld, viewProjection, textureHandle_);
	model_->Draw(tempworld, viewProjection);
	bodyModel->Draw(tempworld, viewProjection);
	taiyaModel->Draw(tempworld, viewProjection);
}

bool Camel::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void Camel::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void Camel::OnCollision()
{
	isDead = true;
}
