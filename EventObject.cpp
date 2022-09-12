#include "EventObject.h"

void EventObject::Initialize(Model* model_, TextureHandle tex)
{
	object::LoadModel(model_);
	if (tex != 0)
	{
		object::LoadTexture(tex);
	}
	else
	{
		object::LoadTexture(TextureManager::Load("white.png"));
	}
	worldTransform_.Initialize();
}

void EventObject::Update()
{
	object::MatUpdate();
}

void EventObject::Draw(ViewProjection view, TextureHandle tex)
{
	WorldTransform tempworld = worldTransform_;
	tempworld.translation_ += screenShake;
	//�s��v�Z
	tempworld.matWorld_ = Scale(worldTransform_.scale_);
	tempworld.matWorld_ *= Rot(worldTransform_.rotation_);
	tempworld.matWorld_ *= Transform(worldTransform_.translation_);
	tempworld.TransferMatrix();
	if (tex == 0)
	{
		model_->Draw(tempworld, view, textureHandle_);
	}
	else
	{
		model_->Draw(tempworld, view, tex);
	}
}

void EventObject::LoadTexture(TextureHandle tex)
{
	object::LoadTexture(tex);
}

void EventObject::CountUp()
{
	eventCount++;
}

void EventObject::CountDown()
{
	eventCount--;
}

void EventObject::NotCol()
{
	worldTransform_.scale_ = { 0,0,0 };
}

void EventObject::InitScale()
{
	worldTransform_.scale_ = initScale;
}

void EventObject::InitPos()
{
	worldTransform_.translation_ = initPos;
}

void EventObject::RemoveScale()
{
	static float removeSpd = 0.2f;
	if (worldTransform_.scale_.x <= initScale.x)
	{
		worldTransform_.scale_.x += removeSpd;
		worldTransform_.scale_.y += removeSpd;
		worldTransform_.scale_.z += removeSpd;
	}

	if (worldTransform_.scale_.x > initScale.x)
	{
		worldTransform_.scale_ = initScale;
	}
}

void EventObject::Vibration(float min, float max)
{
	InitPos();

	int mn = min * 10;
	int mx = max * 10;

	//rng�֐���int��������Ȃ����߁A10�{���Ė߂����Ƃ�float�ɑΉ�
	float r = RNG(mn, mx);
	r /= 10;

	worldTransform_.translation_.x += r;

	r = RNG(mn, mx);
	r /= 10;

	worldTransform_.translation_.z += r;
}
