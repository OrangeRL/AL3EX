#pragma once
#include "object.h"
#include "DebugText.h"
class Pedestrian : public object
{
public:
	void Initialize(Model* model_);
	void Update();
	void Update2();
	void Draw(ViewProjection viewProjection, Vector3 shake = { 0,0,0 });

	bool GetCheckUpdate();

	void LoadTexture(TextureHandle tex);
	void OnCollision();
	void Reset();
	void Randomize();
private:
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	bool isCheckPointUpdate = false;
	float pos;
	DebugText* debugText_ = nullptr;
	//行動フェーズ
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Approach;
};

