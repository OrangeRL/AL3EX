#include "EnemyBullet.h"
#include "Enemy.h"
#include "UpdateMatrix.h"

EnemyBullet::EnemyBullet()
{
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULLポインタチェック
	assert(model);
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("EnemyBullet.png");
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	input_ = Input::GetInstance();
}



void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

void EnemyBullet::Update() {
	//座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;
	//時間経過でデス
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
	/*if (input_->TriggerKey(DIK_R))
	{
		isDead_ = true;
	}*/
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//行列の再計算(更新)
	worldTransform_.TransferMatrix();
}

Vector3 EnemyBullet::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
#pragma region 背景スプライト描画

#pragma endregion

#pragma region 3Dオブジェクト描画
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
#pragma endregion

#pragma region 前景スプライト描画

#pragma endregion
}


