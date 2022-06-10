#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>
#include"AxisIndicator.h"
#include"PrimitiveDrawer.h"


GameScene::GameScene() {

}

GameScene::~GameScene() {

	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	textureHandle_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(seed_gen());
	//乱数範囲(回転角)
	std::uniform_real_distribution<float> dist(-50.0f, 50.0f);
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> scaDist(1.0f, 5.0f);
	std::uniform_real_distribution<float> rotDist(0.0f, 5.0f);


	//worldTransforms_[0].Initialize();
	////子(1番)
	//worldTransforms_[1].Initialize();
	//worldTransforms_[1].translation_ = { 0,4.5f,0 };
	//worldTransforms_[1].parent_ = &worldTransforms_[0];

// キャラクターの大元
	//親(0番)
	worldTransforms_[PartId::kRoot].Initialize();
	//子(1番)
	worldTransforms_[PartId::kSpine].translation_ = { 0, 4.5f, 0 };
	worldTransforms_[PartId::kSpine].parent_ = &worldTransforms_[PartId::kRoot];
	worldTransforms_[PartId::kSpine].Initialize();

	worldTransforms_[PartId::kHead].translation_ = { 0, 6.0f, 0 };
	worldTransforms_[PartId::kHead].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kHead].Initialize();

	worldTransforms_[PartId::kChest].translation_ = { 0, 3.5f, 0 };
	worldTransforms_[PartId::kChest].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kChest].Initialize();

	worldTransforms_[PartId::kHip].translation_ = { 0, 1.0f, 0 };
	worldTransforms_[PartId::kHip].parent_ = &worldTransforms_[PartId::kSpine];
	worldTransforms_[PartId::kHip].Initialize();

	worldTransforms_[PartId::kArmL].translation_ = { 3.0f, 3.5, 0 };
	worldTransforms_[PartId::kArmL].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmL].Initialize();

	worldTransforms_[PartId::kArmR].translation_ = { -3.0f, 3.5, 0 };
	worldTransforms_[PartId::kArmR].parent_ = &worldTransforms_[PartId::kChest];
	worldTransforms_[PartId::kArmR].Initialize();


	worldTransforms_[PartId::kLegL].translation_ = { 3.0f, -1.5f, 0 };
	worldTransforms_[PartId::kLegL].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegL].Initialize();

	worldTransforms_[PartId::kLegR].translation_ = { -3.0f, -1.5f, 0 };
	worldTransforms_[PartId::kLegR].parent_ = &worldTransforms_[PartId::kHip];
	worldTransforms_[PartId::kLegR].Initialize();

	Matrix4 matIdentity;
	matIdentity.m[0][0] = 1.0f;
	matIdentity.m[1][1] = 1.0f;
	matIdentity.m[2][2] = 1.0f;
	matIdentity.m[3][3] = 1.0f;

	//x,y,z方向のスケーリングを設定
	worldTransforms_[PartId::kRoot].scale_ = { 0,0,0 };
	//スケーリング行列を宣言
	Matrix4 matScale;
	matScale.m[0][0] = worldTransforms_[PartId::kRoot].scale_.x;
	matScale.m[1][1] = worldTransforms_[PartId::kRoot].scale_.y;
	matScale.m[2][2] = worldTransforms_[PartId::kRoot].scale_.z;
	matScale.m[3][3] = 1.0f;


	//worldTransform_.matWorld_ *= matScale;

	//x,y,z軸周りの回転角を設定
	worldTransforms_[PartId::kRoot].rotation_ = { 0,0,0 };
	//各軸用回転行列を宣言
	Matrix4 matRotZ;
	matRotZ.m[0][0] = cos(worldTransforms_[PartId::kRoot].rotation_.z);
	matRotZ.m[0][1] = sin(worldTransforms_[PartId::kRoot].rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransforms_[PartId::kRoot].rotation_.z);
	matRotZ.m[1][1] = cos(worldTransforms_[PartId::kRoot].rotation_.z);
	matRotZ.m[2][2] = 1.0f;
	matRotZ.m[3][3] = 1.0f;

	Matrix4 matRotY;

	//Y軸回転行列の各要素を設定する
	matRotY.m[0][0] = cos(worldTransforms_[PartId::kRoot].rotation_.y);
	matRotY.m[0][2] = -sin(worldTransforms_[PartId::kRoot].rotation_.y);
	matRotY.m[2][0] = sin(worldTransforms_[PartId::kRoot].rotation_.y);
	matRotY.m[2][2] = cos(worldTransforms_[PartId::kRoot].rotation_.y);
	matRotY.m[1][1] = 1.0f;
	matRotY.m[3][3] = 1.0f;

	Matrix4 matRotX;

	//X軸回転行列の各要素を設定する
	matRotX.m[1][1] = cos(worldTransforms_[PartId::kRoot].rotation_.x);
	matRotX.m[1][2] = sin(worldTransforms_[PartId::kRoot].rotation_.x);
	matRotX.m[2][1] = -sin(worldTransforms_[PartId::kRoot].rotation_.x);
	matRotX.m[2][2] = cos(worldTransforms_[PartId::kRoot].rotation_.x);
	matRotX.m[0][0] = 1.0f;
	matRotX.m[3][3] = 1.0f;


	Matrix4 matRot = matIdentity;
	//各軸の回転行列を合成
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	//平行移動を設定

	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldTransforms_[PartId::kRoot].translation_.x;
	matTrans.m[3][1] = worldTransforms_[PartId::kRoot].translation_.y;
	matTrans.m[3][2] = worldTransforms_[PartId::kRoot].translation_.z;
	matTrans.m[3][3] = 1;

	// 単位行列の代入
	worldTransforms_[PartId::kRoot].matWorld_ = matIdentity;
	// matScaleの代入
	worldTransforms_[PartId::kRoot].matWorld_ *= matScale;
	// matScaleの代入
	worldTransforms_[PartId::kRoot].matWorld_ *= matRot;
	// matTransの代入
	worldTransforms_[PartId::kRoot].matWorld_ *= matTrans;

	// 行列の転送
	worldTransforms_[PartId::kRoot].TransferMatrix();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::SetTargetViewProjection(&viewProjection_);

	// ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());


}



void GameScene::Update() {
	debugCamera_->Update();
	{

		// キャラクターの移動ベクトル
		Vector3 move = { 0,0,0 };

		// キャラクターの移動速さ
		const float kCharacterSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_A)) {
			move = { -kCharacterSpeed,0,0 };
		}
		else if (input_->PushKey(DIK_D)) {
			move = { kCharacterSpeed,0,0 };
		}
		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			worldTransforms_[PartId::kChest].rotation_.y -= 0.02f;
			worldTransforms_[PartId::kArmL].rotation_.y -= 0.02f;
			worldTransforms_[PartId::kArmR].rotation_.y -= 0.02f;
		}
		else if (input_->PushKey(DIK_I)) {
			worldTransforms_[PartId::kChest].rotation_.y += 0.02f;
			worldTransforms_[PartId::kArmL].rotation_.y += 0.02f;
			worldTransforms_[PartId::kArmR].rotation_.y += 0.02f;
		}

		// 下半身回転処理
			// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			worldTransforms_[PartId::kHip].rotation_.y -= 0.02f;
			worldTransforms_[PartId::kLegL].rotation_.y -= 0.02f;
			worldTransforms_[PartId::kLegR].rotation_.y -= 0.02f;
		}
		else if (input_->PushKey(DIK_K)) {
			worldTransforms_[PartId::kHip].rotation_.y += 0.02f;
			worldTransforms_[PartId::kLegL].rotation_.y += 0.02f;
			worldTransforms_[PartId::kLegR].rotation_.y += 0.02f;
		}

		for (int i = 0; i < 9; i++) {
			worldTransforms_[i].translation_ += move;
		}
		debugText_->SetPos(50, 150);
		debugText_->Printf(
			"move:(%f,%f,%f)",
			worldTransforms_[PartId::kRoot].translation_.x,
			worldTransforms_[PartId::kRoot].translation_.y,
			worldTransforms_[PartId::kRoot].translation_.z);
	}
	//子の更新
	{
		for (int i = 0; i < 9; i++) {

			Matrix4 matIdentity;
			matIdentity.m[0][0] = 1.0f;
			matIdentity.m[1][1] = 1.0f;
			matIdentity.m[2][2] = 1.0f;
			matIdentity.m[3][3] = 1.0f;


			Matrix4 matScale;
			matScale.m[0][0] = worldTransforms_[i].scale_.x;
			matScale.m[1][1] = worldTransforms_[i].scale_.y;
			matScale.m[2][2] = worldTransforms_[i].scale_.z;
			matScale.m[3][3] = 1.0f;

			Matrix4 matRotZ;
			matRotZ.m[0][0] = cos(worldTransforms_[i].rotation_.z);
			matRotZ.m[0][1] = sin(worldTransforms_[i].rotation_.z);
			matRotZ.m[1][0] = -sin(worldTransforms_[i].rotation_.z);
			matRotZ.m[1][1] = cos(worldTransforms_[i].rotation_.z);
			matRotZ.m[2][2] = 1.0f;
			matRotZ.m[3][3] = 1.0f;

			Matrix4 matRotY;

			//Y軸回転行列の各要素を設定する
			matRotY.m[0][0] = cos(worldTransforms_[i].rotation_.y);
			matRotY.m[0][2] = -sin(worldTransforms_[i].rotation_.y);
			matRotY.m[2][0] = sin(worldTransforms_[i].rotation_.y);
			matRotY.m[2][2] = cos(worldTransforms_[i].rotation_.y);
			matRotY.m[1][1] = 1.0f;
			matRotY.m[3][3] = 1.0f;

			Matrix4 matRotX;

			//X軸回転行列の各要素を設定する
			matRotX.m[1][1] = cos(worldTransforms_[i].rotation_.x);
			matRotX.m[1][2] = sin(worldTransforms_[i].rotation_.x);
			matRotX.m[2][1] = -sin(worldTransforms_[i].rotation_.x);
			matRotX.m[2][2] = cos(worldTransforms_[i].rotation_.x);
			matRotX.m[0][0] = 1.0f;
			matRotX.m[3][3] = 1.0f;

			Matrix4 matRot = matIdentity;
			//各軸の回転行列を合成
			matRot *= matRotZ;
			matRot *= matRotX;
			matRot *= matRotY;

			Matrix4 matTrans = MathUtility::Matrix4Identity();
			matTrans.m[3][0] = worldTransforms_[i].translation_.x;
			matTrans.m[3][1] = worldTransforms_[i].translation_.y;
			matTrans.m[3][2] = worldTransforms_[i].translation_.z;
			matTrans.m[3][3] = 1;

			//のスケーリング・回転・平行移動を合成した行列を計算する
			worldTransforms_[i].matWorld_ = matIdentity;
			worldTransforms_[i].matWorld_ *= matScale;
			worldTransforms_[i].matWorld_ *= matRot;
			worldTransforms_[i].matWorld_ *= matTrans;

			//worldTransforms_[i].parent_ = &worldTransforms_[PartId::kRoot];//にworldTransforms_[0](parent_)のワールド行列を掛け算代入する

			worldTransforms_[i].TransferMatrix();//のワールド行列を転送
		}
	}

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
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	/*for (int i = 0; i < 9; i++)
	{
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}*/
	//for (int i = kRoot; i != kLegR; i++)
	//{
	//	PartId ID = static_cast<PartId>(i);
	//	model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	//}
	/*	model_->Draw(worldTransforms_[0], viewProjection_, textureHandle_);
		model_->Draw(worldTransforms_[1], viewProjection_, textureHandle_);*/

	for (int i = 0; i < 9; i++) {
		if (i < 2) {
			continue;
		}
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}


	//PrimitiveDrawer::GetInstance()->DrawLine3d({ 0,0,0 }, { 10,0,0 }, { 0,0,0,10 });

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