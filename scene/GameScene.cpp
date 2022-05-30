#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>
#include"AxisIndicator.h"
#include"PrimitiveDrawer.h"

float getRadian(float degree)
{
	float radian = degree * 3.14f / 180.0f;
	return radian;
}


GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	float PI = 3.141592654f;
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
	//乱数範囲の指定
	std::uniform_real_distribution<float> dist(0.0f, 10.0f);
	//乱数範囲(回転角)
	std::uniform_real_distribution<float> rotDist(0.0f, 2 * PI);
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);

	//乱数エンジンを渡し,指定範囲からランダムな数値を得る
	float value = dist(engine);

	for (WorldTransform& worldTransform : worldTransforms_)
	{
		//ワールドトランスフォームの初期化
		worldTransform.Initialize();
		//x,y,z方向のスケーリングを設定
		worldTransform.scale_ = { 1,1,1 };
		//x,y,z軸周りの回転角を設定
		worldTransform.rotation_ = { rotDist(engine) ,rotDist(engine) ,rotDist(engine) };
		//x,y,z軸周りの平行移動を設定
		worldTransform.translation_ = { posDist(engine),posDist(engine),posDist(engine) };


		//スケーリング行列を宣言
		Matrix4 matScale;
		/*
		   Sx, 0, 0, 0
		   0 ,Sy ,0 ,0
		   0 ,0 ,Sz ,0
		   0, 0 ,0 ,1
		*/
		matScale.m[0][0] = worldTransform.scale_.x;
		matScale.m[1][1] = worldTransform.scale_.y;
		matScale.m[2][2] = worldTransform.scale_.z;
		matScale.m[3][3] = 1;


		/*
		  cos,sin,0,0
		  -sin,cos,0,0
		  0,0,1,0
		  0,0,0,1
		*/

		Matrix4 matIdentity;
		matIdentity.m[0][0] = 1;
		matIdentity.m[1][1] = 1;
		matIdentity.m[2][2] = 1;
		matIdentity.m[3][3] = 1;



		//合成回転行列を宣言
		Matrix4 matRot = matIdentity;
		//各軸用回転行列を宣言
		Matrix4 matRotX = matIdentity, matRotY = matIdentity, matRotZ = matIdentity;

		matRotZ.m[0][0] = cos(worldTransform.rotation_.z);
		matRotZ.m[0][1] = sin(worldTransform.rotation_.z);
		matRotZ.m[1][0] = -sin(worldTransform.rotation_.z);
		matRotZ.m[1][1] = cos(worldTransform.rotation_.z);

		matRotY.m[0][0] = cos(worldTransform.rotation_.y);
		matRotY.m[2][0] = sin(worldTransform.rotation_.y);
		matRotY.m[0][2] = -sin(worldTransform.rotation_.y);
		matRotY.m[2][2] = cos(worldTransform.rotation_.y);

		matRotX.m[1][1] = cos(worldTransform.rotation_.x);
		matRotX.m[1][2] = sin(worldTransform.rotation_.x);
		matRotX.m[2][1] = -sin(worldTransform.rotation_.x);
		matRotX.m[2][2] = cos(worldTransform.rotation_.x);


		//各軸の回転行列を合成
		matRot *= matRotZ;
		matRot *= matRotX;
		matRot *= matRotY;


		//worldTransform_.matWorld_ = matIdentity;
		//worldTransform_.matWorld_ *= matRotZ;
		////行列の転送
		//worldTransform_.TransferMatrix();



		//平行移動行列を宣言
		Matrix4 matTrans = MathUtility::Matrix4Identity();
		/*
		  1,0,0,0
		  0,1,0,0
		  0,0,1,0
		  Tx,Ty,Tz,1

		*/
		matTrans.m[3][0] = worldTransform.translation_.x;
		matTrans.m[3][1] = worldTransform.translation_.y;
		matTrans.m[3][2] = worldTransform.translation_.z;
		matTrans.m[3][3] = 1;


		worldTransform.matWorld_ = matIdentity;
		worldTransform.matWorld_ *= matScale;
		worldTransform.matWorld_ *= matRot;
		worldTransform.matWorld_ *= matTrans;

		//行列の転送
		worldTransform.TransferMatrix();


	}

	////カメラ視点座標を設定
	//viewProjection_.eye = { 0, 0,-10 };
	////カメラ注視点座標を設定
	//viewProjection_.target = { 10,0,0 };
	////カメラ上方向ベクトルを設定(右上45度指定)
	//viewProjection_.up = { cosf(PI / 4.0f),sinf(PI / 4.0f),0.0f };
	//カメラ垂直方向視野角を設定
	viewProjection_.fovAngleY = getRadian(10.0f);
	//アスペクト比を設定
	viewProjection_.aspectRatio = 1.0f;
	//ニアクリップ距離を設定
	viewProjection_.nearZ = 52.0f;
	//ファークリップ距離を設定
	viewProjection_.farZ = 53.0f;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1080, 720);
	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {
	//float PI = 3.141592654f;
	//デバッグカメラの更新
	debugCamera_->Update();
	////視点の移動ベクトル
	//Vector3 move = { 0,0,0 };

	////視点の移動速さ
	//const float kEyeSpeed = 0.2f;

	////押した方向で移動ベクトルを変更
	//if (input_->PushKey(DIK_W))
	//{
	//	move.z += kEyeSpeed;
	//}
	//else if (input_->PushKey(DIK_S))
	//{
	//	move.z -= kEyeSpeed;
	//}
	////視点移動(ベクトルの加算)
	//viewProjection_.eye += move;

	////行列の再計算
	//viewProjection_.UpdateMatrix();

	////デバッグ用表示
	//debugText_->SetPos(50, 50);
	//debugText_->Printf("eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	////注視点移動処理
	//{
	//	//視点の移動ベクトル
	//	Vector3 move = { 0,0,0 };

	//	//注視点の移動の速さ
	//	const float kTargetSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_LEFT))
	//	{
	//		move.x += kTargetSpeed;
	//	}
	//	else if (input_->PushKey(DIK_RIGHT))
	//	{
	//		move.x -= kTargetSpeed;
	//	}
	//	//視点移動(ベクトルの加算)
	//	viewProjection_.target += move;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバッグ用表示
	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf("target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);

	//	//上方向回転処理
	//	{
	//		//上方向に回転速さ[ラジアン/flame]
	//		const float kUpRotspeed = 0.05f;

	//		//押した方向で移動ベクトルを変更
	//		if (input_->PushKey(DIK_SPACE))
	//		{
	//			viewAngle += kUpRotspeed;
	//			//2πを超えたら0に戻す
	//			viewAngle = fmodf(viewAngle, PI * 2.0f);
	//		}
	//		//上方向ベクトルを計算(半径1の円周上の座標)
	//		viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };

	//		//行列の再計算
	//		viewProjection_.UpdateMatrix();

	//		//デバッグ用表示
	//		debugText_->SetPos(50, 90);
	//		debugText_->Printf("up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);

	//	}



	//}

	//FoV変更処理

		//上キーで視野角が広がる
	if (input_->PushKey(DIK_W))
	{
		viewProjection_.fovAngleY+=0.1;//の値を上げる
		viewProjection_.fovAngleY;//がπを上回らないようにする
		//下キーで視野角が狭まる
	}
	else if (input_->PushKey(DIK_S))
	{
		viewProjection_.fovAngleY-=0.1; //の値を下げる
		viewProjection_.fovAngleY;//が0.01fを下回らないようにする
	}
	//行列の再計算
	viewProjection_.UpdateMatrix();

	//デバッグ用表示
	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree):f",getRadian( viewProjection_.fovAngleY));


	//クリップ距離変更処理
	{
		//上下キーでニアクリップ距離を増減
		if (input_->PushKey(DIK_UP))
		{
			viewProjection_.nearZ += 0.1f;//の値を上げる
		}
		else if (input_->PushKey(DIK_DOWN))
		{
			viewProjection_.nearZ -= 0.1f;//の値を下げる
		}
		//行列の再計算
		viewProjection_.UpdateMatrix();
		//デバッグ用表示
		debugText_->SetPos(50, 130);
		debugText_->Printf("nearZ:%f", viewProjection_.nearZ); }


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
	for (WorldTransform& worldTransform : worldTransforms_)
	{
		model_->Draw(worldTransform, viewProjection_, textureHandle_);
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