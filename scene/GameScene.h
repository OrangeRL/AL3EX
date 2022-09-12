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
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include "skydome.h"
#include "RailCamera.h"
#include "Victory.h"
#include "Title.h"
#include "Signal.h"
#include "TitleScreen.h"

#include "PyramidManager.h"
#include "BuildingManager.h"
#include "GroundManager.h"
#include "EnemyManager.h"
#include "AsteroidManager.h"
#include "TitleObaManager.h"
#include "SpeedParticleManager.h"
#include "PedestrianManager.h"
#include "CrossManager.h"
#include "SignalManager.h"
#include "CamelManager.h"
#include "WindManager.h"
#include "SoundDataManager.h"

#include "ModelManager.h"
#include "Utill.h"
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
	DebugText* timeText_ = nullptr;
	bool isDebugCameraActive_ = false;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	bool pBoostUse = false;
	//3Dモデル
	Model* model_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	//自キャラ
	Player* player_ = nullptr;
	//std::unique_ptr<Player> player_;
	EnemyManager* enemyManager;
	AsteroidManager* asteroidManager;
	TitleObaManager* toManager;
	TitleObaManager* to2Manager;
	TitleObaManager* to3Manager;
	TitleObaManager* to4Manager;
	SpeedParticleManager* spManager;
	Enemy* enemy_ = nullptr;

	Title* title_ = nullptr;
	Victory* victory_ = nullptr;
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
	Model* modelSkydomee_;
	Model* modelSkydomeee_;
	ModelManager* modelManager;
	GroundManager gManager;
	BuildingManager bManager;
	PedestrianManager pedestrianManager;
	CrossManager crossManager;
	SignalManager signalManager;
	PyramidManager pyramidManager;
	CamelManager camelManager;
	WindManager windManager;
	//BGM
	SoundDataManager SDManager;
	Signal signal;

	TitleScreen title;
	ViewProjection titleView;

	// 天球
	std::unique_ptr<skydome>skydome_;
	std::unique_ptr<skydome>skydomee_;
	std::unique_ptr<skydome>skydomeee_;

	// レールカメラ
	std::unique_ptr<RailCamera> railCamera_;
	Vector3 popPos = { 0,0,0 };
	///<summary>
	///衝突判定と応答
	///</summary>
	int overTimer = 30;

	//SoundDataHandle titleBGM = 0;
public:
	int scene = -1;
	bool isStart_ = false;
	bool isRestart_ = false;
	bool playerDead = false;
};
