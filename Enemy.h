#pragma once
#include "assert.h"
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
#include "EnemyBullet.h"
#include <memory>
#include<list>
///<summary>
///敵
///</summary>
class Enemy {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Enemy();

	///<summary>///初期化///</summary>///<paramname="model">モデル</param>///<paramname="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, const Vector3& position, uint32_t textureHandle);
	///<summary>
	///更新
	///</summary>
	void Update();
	///<summary>
	///描画
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw(ViewProjection& viewProjection);
	void TransferMatrix();
	void Move();
	void Fire();
	//接近フェーズ初期化
	void ApproachInit();
	//発射間隔
	static const int kFireInterval = 60;

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	DebugText* debugText_ = nullptr;
	//行動フェーズ
	enum class Phase {
		Approach,//接近する
		Leave,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Approach;

	//弾
	std::list<std::unique_ptr<EnemyBullet>>bullets_;

	//発射タイマー
	int32_t fireTimer = 0;
};