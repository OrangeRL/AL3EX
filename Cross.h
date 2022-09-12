#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "PlayerBullet.h"
#include <memory>
#include <list>
#include "object.h"
class Cross : public object
{
public:
	void Initialize(Model* model_);
	void Update();
	void Draw(ViewProjection viewProjection, Vector3 shake = { 0,0,0 });

	bool GetCheckUpdate();

	void LoadTexture(TextureHandle tex);
	void OnCollision();
	void Reset();

private:
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

