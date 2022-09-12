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

//自機クラスの前方前言
class Player;

///<summary> 
///レールカメラ
///</summary>
class RailCamera {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RailCamera() = default;


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	void OnCollision();
	void WindCollision();
	void Restart();
	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	const ViewProjection& GetViewProjection() { return viewProjection_;}

	Matrix4 GetWorldMatrix() const { return worldTransform_.matWorld_; }
	//ワールド行列を取得
	WorldTransform* GetWorldMatrix() { return &worldTransform_;}
	void boostUseReset() { boostUsed = false; };
	bool boostUse() { return boostUsed; }
private:
	enum class Phase {
		Drive,//接近する
		Brake,//離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Drive;
	float speed = 0.4;
	float speedBoost = 0.4;
	float speedBoostTimer = 0;
	bool boostUsed = false;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
	//デバックテキスト
	DebugText* debugText_ = DebugText::GetInstance();

	bool isWin_ = false;
};