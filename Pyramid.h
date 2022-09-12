#pragma once
#include "object.h"
class Pyramid : public object
{
public:
	void Initialize(Model* model_, Model* bodyModel, Model* taiyaModel);
	void Update();
	void Draw(ViewProjection viewProjection);

	bool GetCheckUpdate();

	void LoadTexture(TextureHandle tex);
	void OnCollision();
	void Reset();

private:
	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;
	Model* model_ = nullptr;

	bool isCheckPointUpdate = false;
	float pos;
	//行動フェーズ
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Approach;
};

