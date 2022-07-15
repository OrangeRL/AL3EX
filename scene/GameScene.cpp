#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>
#include"AxisIndicator.h"
#include"PrimitiveDrawer.h"
#include"DebugCamera.h"

GameScene::GameScene() {

}

GameScene::~GameScene() {

	delete model_;
	delete debugCamera_;
	//delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();


	//自キャラの生成
	player_ = new Player();
	player_->Initialize(model_, textureHandle_);

	//tekiキャラの生成
	Vector3 position = worldTransforms_->translation_;
	enemy_ = new Enemy();
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	enemy_->Initialize(model_, position, textureHandle_);


	//Enemy* newEnemy = new Enemy();
	//std::unique_ptr<Enemy>newEnemy = std::make_unique<Enemy>();
	////自キャラの初期化
	//newEnemy->Initialize(model_, position, textureHandle_);
	//enemy_.reset(newEnemy);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::SetTargetViewProjection(&viewProjection_);
}



void GameScene::Update() {
	debugCamera_->Update();

	//自キャラの更新
	player_->Update();
	//敵の更新
	enemy_->Update();

	CheckAllCollisions();
	//#ifdef _DEBUG 
	//	if (input_->TriggerKey(DIK_O))
	//	{
	//		//デバッグカメラ有効フラグをトグル 
	//		isDebugCameraActive_ = true;
	//	}
	//
	//	//カメラの処理
	//	if (isDebugCameraActive_)
	//	{
	//		
	//		debugCamera_->Update();
	//		viewProjection_.matView = debugCamera_->SetDistance(float distance) { distance_ = distance;};
	//		viewProjection_.matProjection = デバッグカメラのプロジェクション行列;
	//		ビュープロジェクションの転送
	//	}
	//	else 
	//	{
	//		ビュープロジェクション行列の再計算と転送;
	//	}
	//#endif
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	//3Dモデル描画
	//自機の描画
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::CheckAllCollisions()
{
	// 判定対象AとBの座標
	Vector3 posA, posB;
	// 半径AとBの距離の計算
	float posAR = 1.0f;
	float posBR = 1.0f;

	// 自弾リストの取得
	const std::list < std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list < std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();
		if (input_->TriggerKey(DIK_R))
		{
			bullet->OnCollision();
		}

		// 座標AとBの距離を求める
		float dx = posB.x - posA.x;
		float dy = posB.y - posA.y;
		float dz = posB.z - posA.z;

		float radius = (posAR + posBR) * (posAR + posBR);

		// 球と球の交差判定
		if ((dx * dx) + (dy * dy) + (dz * dz) <= radius) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		// 自弾の座標
		posB = bullet->GetWorldPosition();

		// 座標AとBの距離を求める
		float dx = posB.x - posA.x;
		float dy = posB.y - posA.y;
		float dz = posB.z - posA.z;

		float radius = (posAR + posBR) * (posAR + posBR);

		// 球と球の交差判定
		if ((dx * dx) + (dy * dy) + (dz * dz) <= radius) {
			// 自キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	// 自弾と敵弾の当たり判定
	for (const std::unique_ptr<PlayerBullet>& bulletA : playerBullets) {
		for (const std::unique_ptr<EnemyBullet>& bulletB : enemyBullets) {
			// 自弾の座標
			posA = bulletA->GetWorldPosition();
			// 敵弾の座標
			posB = bulletB->GetWorldPosition();

			// 座標AとBの距離を求める
			float dx = posB.x - posA.x;
			float dy = posB.y - posA.y;
			float dz = posB.z - posA.z;

			float distance = dx * dx + dy * dy + dz * dz;
			float radius = (posAR + posBR) * (posAR + posBR);

			// 球と球の交差判定
			if (distance <= radius) {
				// 自キャラの衝突時コールバックを呼び出す
				bulletB->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				bulletA->OnCollision();
			}
		}
	}

#pragma endregion
}
