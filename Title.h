#pragma once
#include <cassert>
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
#include "Enemy.h"

using namespace MathUtility;

///<summary>
///敵
///</summary>

class Title {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Title();

	///<summary>///初期化///</summary>///<paramname="model">モデル</param>///<paramname="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);
	///<summary>
	///更新
	///</summary>
	void Update();
	///<summary>
	///描画
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw(ViewProjection& viewProjection);
	void OnCollision();
	void Restart();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	DebugText* debugText_ = nullptr;
	Enemy* enemy_ = nullptr;
};