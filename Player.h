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
#include "SpeedParticleManager.h"
#include "ModelManager.h"
#include <memory>
#include <list>
#include "BuildingManager.h"
#include "SoundDataManager.h"
//カメラクラス
class RailCamera;
//<summary>
//自キャラ
//</summary>
class Player
{
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>

	///<summary>///初期化///</summary>///<paramname="model">モデル</param>///<paramname="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model_, Model* bodyModel, Model* taiyaModel, WorldTransform* parent, const Vector3& position);

	///<summary>
	///更新
	///</summary>
	void Update();
	void SetSpawnPos(Vector3 pos);
	///<summary>
	///描画
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw(ViewProjection& viewProjection);
	void SpriteDraw();
	void Move();

	void Attack();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	void WindCollision();
	void nextStage();
	void resetStage();
	bool nexxtStage() { return NexxtStage; };
	bool NexxtStage = false;
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	void Reset();
	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	void SetParent(WorldTransform* worldTransform) {
		worldTransform_.parent_ = worldTransform;
	}
	void boostUseReset() { boostUsed = false; };
	bool boostUse() { return boostUsed; }
	bool boostUnuse() { return boostUsed ;}
	bool IsSpeed() { return speedBooster; }
	bool IsGoal() { return isGoal; }
	void slow() { speedBooster = false; };
	void fast() { speedBooster = true; };
private:
	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;
	WorldTransform worldTransform_;
	// モデル
	SpeedParticleManager* spManager;
	BuildingManager bManager;
	Model* model_ = nullptr;
	ModelManager* modelManager;
	SoundDataManager SDManager;
	Audio* audio_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 入力処理
	Input* input_ = nullptr;
	// デバックテキスト
	DebugText* debugText_ = nullptr;
	Vector3 respawnPos;
	//弾
	std::list<std::unique_ptr<PlayerBullet>>bullets_;

	//カメラクラス
	RailCamera* railCamera_ = nullptr;
	bool isWin_ = false;
	bool isGoal = false;
	enum class Phase {
		Drive,//接近する
		Brake,//離脱する

	};
	//フェーズ
	Phase phase_ = Phase::Drive;
	//移動関係
	float turnSpeed = 0.0;
	float speed = 0.4;
	float speedBoost = 0.4;
	float speedBoostTimer = 0;
	bool boostUsed = false;
	float InitMoveSpd = 0.21f;
	float moveSpeed = InitMoveSpd;
	float jumpSpd = 0.0f;
	float gravity = 0.01f;
	float windSpeed = 0.00f;
	float posY[3] = { 0,0,0 };
	//スキル
	Sprite* brakeIcon = nullptr;
	bool speedBooster = false;

};