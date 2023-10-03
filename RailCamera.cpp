#include"RailCamera.h"
#include"UpdateMatrix.h"
#include "WinApp.h"
void RailCamera::Initialize(const Vector3& position, const Vector3& rotation)
{
	//ワールドトランスフォームの初期設定
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	speedBoost = 0.0f;
	boostUsed = false;
}
void RailCamera::OnCollision()
{
	isWin_ = true;
}
void RailCamera::Restart()
{
	boostUsed = false;
	speedBoostTimer = 0.0f;
	speedBoost = 0.0f;
	speed = 0.0f;
	worldTransform_.translation_.z = -50.0f;
	isWin_ = false;
}
void RailCamera::WindCollision()
{
	speed = 0.5f;
	//windSpeed += 0.2;
	//if (windSpeed >= 0.00f) {
	//	windSpeed -= 0.01;
	//}
}
void RailCamera::Update()
{
	if (isWin_ == false)
	{
		if (boostUsed==false)
		{
			if (input_->PushKey(DIK_E))
			{
				boostUsed = true;
				speedBoostTimer = 10;
			}
		}
		if (speedBoostTimer > 0) {
			speedBoostTimer -= 0.1f;
			speedBoost = 3.0f;
		}
		else {
			speedBoost = 0.0f;
		}
	Vector3 move = { 0,0,0.0 };
	//Vector3 speed = { 0,0,0.1f };
	
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	//移動(ベクトルを加算)
	move.z = speed+speedBoost;
	worldTransform_.translation_ += move;

	switch (phase_) {
	case Phase::Drive:
	default://移動（ベクトルを加算）
		if (input_->PushKey(DIK_SPACE) == 1) {
			phase_ = Phase::Brake;
		}
		if (speed < 2.0)
		{
			speed += 0.01;
		}
		if (speed > 2.00f) {
			speed = 2.0f;
		}
		if (worldTransform_.translation_.z >= 6000)
		{
			speed = 0;
		}
		break;

	case Phase::Brake://移動（ベクトルを加算）
		if (speed >= 0.03f) {
			speed -= 0.02;
		}
		if (speed < 0.03f) {
			speed = 0.03f;
		}

		if (input_->PushKey(DIK_SPACE) == 0) {
			phase_ = Phase::Drive;
		}
		break;
	}
	

	}
		//worldTransform_.translation_ += speed;
		worldTransform_.translation_.y = 4.05f;
		//worldTransform_.translation_.z += 0.05f;
	/*if (worldTransform_.translation_.z >= -15.0f) {
		worldTransform_.translation_.z = -50.0f;
	}*/
	//トランスフォームを更新
	worldTransform_.matWorld_ = Identity();
	worldTransform_.matWorld_ *= Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	//ワールド行列の平行移動成分を取得
	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	//ワールド前方ベクトル
	Vector3 forward(0, 0, 1);

	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_.target = forward += viewProjection_.eye;

	//ワールド上方ベクトル
	Vector3 up(0, 1, 0);

	//レールカメラの回転を反映 (レールカメラの上方ベクトル)
	viewProjection_.up = BulletRot(up, worldTransform_.matWorld_);
	
	//ビュープロジェクションを更新
	viewProjection_.UpdateMatrix();

	DebugText* debugText_ = DebugText::GetInstance();
	
	////デバッグ用表示
	//debugText_->SetPos(50, 140);
	//debugText_->Printf("RailCamera Pos(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
}