#include "Player.h"
#include"PlayerBullet.h"

Player::Player() {

}

void Player::Initialize(Model* model, uint32_t textureHandle)
{
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Move() {
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	const float kMoveLimitX = 36.0f;
	const float kMoveLimitY = 20.0f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		move = { -kCharacterSpeed,0,0 };
	}
	else if (input_->PushKey(DIK_D)) {
		move = { kCharacterSpeed,0,0 };
	}
	else if (input_->PushKey(DIK_W)) {
		move = { 0,kCharacterSpeed,0 };
	}
	else if (input_->PushKey(DIK_S)) {
		move = { 0,-kCharacterSpeed,0 };
	}
	worldTransform_.rotation_.y -= 0.02f;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, kMoveLimitY);

	//座標移動
	worldTransform_.translation_ += move;
	worldTransform_.TransferMatrix();
}

void Player::Update() {
	Move();
	TransferMatrix();
	debugText_->SetPos(50, 50);
	debugText_->Printf(
		"move:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
	//キャラクター攻撃処理
	Attack();
	//弾更新
	for (std::unique_ptr<PlayerBullet>&bullet:bullets_)
	{
		bullet->Update();
	}
}

void Player::TransferMatrix() {
	Matrix4 matIdentity;
	matIdentity.m[0][0] = 1.0f;
	matIdentity.m[1][1] = 1.0f;
	matIdentity.m[2][2] = 1.0f;
	matIdentity.m[3][3] = 1.0f;


	Matrix4 matScale;
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;
	matScale.m[3][3] = 1.0f;

	Matrix4 matRotZ;
	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	matRotZ.m[2][2] = 1.0f;
	matRotZ.m[3][3] = 1.0f;

	Matrix4 matRotY;

	//Y軸回転行列の各要素を設定する
	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	matRotY.m[1][1] = 1.0f;
	matRotY.m[3][3] = 1.0f;

	Matrix4 matRotX;

	//X軸回転行列の各要素を設定する
	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	matRotX.m[0][0] = 1.0f;
	matRotX.m[3][3] = 1.0f;

	Matrix4 matRot = matIdentity;
	//各軸の回転行列を合成
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	Matrix4 matTrans = MathUtility::Matrix4Identity();
	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;
	matTrans.m[3][3] = 1;

	//のスケーリング・回転・平行移動を合成した行列を計算する
	worldTransform_.matWorld_ = matIdentity;
	worldTransform_.matWorld_ *= matScale;
	worldTransform_.matWorld_ *= matRot;
	worldTransform_.matWorld_ *= matTrans;
}
void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE))
	{
		
		//弾を生成し、初期化
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Draw(ViewProjection& viewProjection)
{
#pragma region 背景スプライト描画

#pragma endregion

#pragma region 3Dオブジェクト描画
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//弾の描画
	for (std::unique_ptr<PlayerBullet>&bullet:bullets_)
	{
		bullet->Draw(viewProjection);
	}
#pragma endregion

#pragma region 前景スプライト描画

#pragma endregion
}