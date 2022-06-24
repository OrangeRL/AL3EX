#include"Enemy.h"

Enemy::Enemy() {

}

void Enemy::Initialize(Model* model, const Vector3& position,uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("monster.jpg");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	
}

void Enemy::TransferMatrix() {
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

void Enemy::Move() {

	Vector3 move = { 0,0,0 };

	// キャラクターの移動速さ
	const float moveSpeed = 0.2f;

	move = { 0.0f,0.01f,-moveSpeed};
	

	worldTransform_.translation_ += move;
TransferMatrix();
//ワールドトランスフォームの更新
	worldTransform_.TransferMatrix();
}

void Enemy::Update() {
	Move();
	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	float moveSpeed = 0.2f;
	approachMove = { 0.0f,0.0f,-moveSpeed };
	leaveMove = { -0.1,0.1,-moveSpeed };
	switch (phase_)
	{
	case Enemy::Phase::Approach:
	default:
		//移動(ベクトルを加算)
		worldTransform_.translation_ += approachMove;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.z<0.0f)
		{
			phase_ = Phase::Leave;
		}
		break;
	case Enemy::Phase::Leave:
		//移動(ベクトルを加算)
		worldTransform_.translation_ += leaveMove;
		break;
		
	}
	
}

void Enemy::Draw(ViewProjection& viewProjection) {

#pragma region 背景スプライト描画

#pragma endregion

#pragma region 3Dオブジェクト描画
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
#pragma endregion

#pragma region 前景スプライト描画

#pragma endregion
}