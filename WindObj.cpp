#include "WindObj.h"
#include "GetMatrix.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
void WindObj::Initialize(Model* model_)
{

	debugText_ = DebugText::GetInstance();
	LoadModel(model_);
	LoadTexture(TextureManager::Load("kaze.png"));
	worldTransform_.Initialize();

}
void WindObj::Randomize()
{
	//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	pos = r;
}
void WindObj::Update()
{
	
	MatUpdate();
}



void WindObj::Update2()
{
	
	MatUpdate();
}
void WindObj::Reset()
{
	worldTransform_.translation_.y = 2.0;
	Randomize();
}
void WindObj::Draw(ViewProjection viewProjection, Vector3 shake)
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

bool WindObj::GetCheckUpdate()
{
	return isCheckPointUpdate;
}

void WindObj::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void WindObj::OnCollision()
{
	worldTransform_.translation_.y = 200;
}
