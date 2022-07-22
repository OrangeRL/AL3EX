﻿#pragma once
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
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include "skydome.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();


	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	bool isDebugCameraActive_ = false;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	Model* model_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	//自キャラ
	Player* player_ = nullptr;
	//std::unique_ptr<Player> player_;
	Enemy* enemy_ = nullptr;
	//teki
	//std::unique_ptr<Enemy> enemy_;
	//カメラ上方向の角度
	float viewAngle = 0.0f;
	//ワールドトランスフォーム
	WorldTransform worldTransforms_[100];
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// 3dモデル
	Model* modelSkydome_;
	std::unique_ptr<skydome>skydome_;
	//3Dモデル
	//std::unique_ptr<Skydome> modelSkydome_;
	/// </summary>

	//Matrix4 GetMatrix(const WorldTransform& worldTransforms_);

	///<summary>
	///衝突判定と応答
	///</summary>

public:
	enum PartId {
		kRoot,		// 大元
		kSpine,		// 脊髄
		kChest,		// 胸
		kHead,		// 頭
		kArmL,		// 左腕
		kArmR,		// 右腕
		kHip,		// 尻
		kLegL,		// 左足
		kLegR,		// 右足

		kNumPartId
	};
};
