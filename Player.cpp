#include "Player.h"
#include "assert.h"
#include "GetMatrix.h"
#include "RailCamera.h"

Vector3 vecmat(Vector3& vec, Matrix4& mat) {

	Vector3 vecMat = {};

	vecMat.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];

	vecMat.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];

	vecMat.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];

	return vecMat;
}


void Player::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel, WorldTransform* parent, const Vector3& position)
{
	//NULLポインタチェック
	
	assert(model_);
	assert(bodyModel);
	assert(taiyaModel);
	audio_ = Audio::GetInstance();
	worldTransform_.Initialize();
	brakeFX = audio_->LoadWave("brakeFX.wav");
	fanfareFX = audio_->LoadWave("StageClear.wav");
	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;

	brakeIcon = Sprite::Create(TextureManager::Load("brick.png"), { 0,0 });
	brakeIcon->SetSize({ 80,80 });
	speedBoost = 0.0f;
	speedBoostTimer = 0;
	//引数として受け取ったデータをメンバ変数に記録する
	//model_ = model;
	//textureHandle_ = textureHandle;
	worldTransform_.parent_ = parent;
	TextureHandle white = TextureManager::Load("white.png");
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	boostUsed = false;
	//ワールド変換の初期化
	worldTransform_.Initialize();
	
	worldTransform_.translation_ = { 0.0f,0.3f,-20.5f };
	worldTransform_.scale_ = { 0.8f,0.8f,0.8f };
	worldTransform_.rotation_ = { 0.0f,1.0f,0.0f };
}
void Player::SetSpawnPos(Vector3 pos)
{
	respawnPos = pos;
}
void Player::nextStage()
{
	slow();
	NexxtStage = true;
	audio_->PlayWave(fanfareFX, false, 0.5f);
	//Reset();
	//resetStage();
}
void Player::resetStage()
{
	NexxtStage = false;
	slow();
}
Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Reset()
{
	isDead = false;
	slow();
	boostUseReset();
	speedBoost = 0.0f;
	NexxtStage = false;
	isWin_ = false;
	speed = 0.0f;
	speedBoost = 0.0f;
	speedBoostTimer = 0;
	worldTransform_.translation_ = { 0.0f,0.3f,-20.5f };
}

void Player::Move() {
	// キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };
	if (worldTransform_.translation_.z >= 2600)
	{
		nextStage();
	}
	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;
	
	const float kMoveLimitX = 6.8f;
	const float kMoveLimitY = 15.0f;
	if (isWin_ == false)
	{
		move.z = speed + speedBoost;
		worldTransform_.rotation_.y = 1.6 + turnSpeed;
		move.x += windSpeed;
		if(speed>0.03)
		{
		if (input_->PushKey(DIK_A)) 
		{
			move = { -0.08f-windSpeed,0,speed+speedBoost };
		}

		else if (input_->PushKey(DIK_D)) 
		{
			move = { 0.08f-windSpeed,0,speed + speedBoost };
		}
		}
		if(boostUsed == false)
		{
		if (input_->PushKey(DIK_E))
		{
			boostUsed = true;
			speedBoostTimer = 10;
			fast();
		}
		}
		if (speedBoostTimer > 0) {
			speedBoostTimer -= 0.1f;
			speedBoost = 3.0f;
		}
		else {
			speedBoost = 0.0f;
		}
	/*	debugText_->SetPos(50, 90);
		debugText_->Printf("timer:(%f)", speed);

		debugText_->SetPos(50, 260);
		debugText_->Printf("speedBoostTimer:(%f)", speedBoostTimer);

		debugText_->SetPos(50, 280);
		debugText_->Printf("speedBoost:(%f)", speedBoost);*/
			Vector3 approachMove = { 0,0,0 };
			Vector3 leaveMove = { 0,0,0 };
			approachMove = { 0.0f,0.0f,0.0 };
			leaveMove = { -0.0,0.0,-0.0 };
			if (speed > 2.00f) {
				speed = 2.0f;
			}
			if (speed + speedBoost > 2.5f) {
				fast();
			}
			if (speed + speedBoost < 2.1f) {
				slow();
			}
			if (worldTransform_.translation_.z >= 2500)
			{
				isGoal = true;
			}
			switch (phase_) {
			case Phase::Drive:
			default://移動（ベクトルを加算）
				if (input_->PushKey(DIK_SPACE) == 1) {
					phase_ = Phase::Brake;
					audio_->PlayWave(brakeFX, false, 0.3);
				}
				
				if (speed < 2.0) 
				{
				speed += 0.01;
				}

	
				if (input_->PushKey(DIK_D)) {
					if (turnSpeed < 0.2)
					{
						turnSpeed += 0.02;
					}
					if (turnSpeed > 0.20f) {
						turnSpeed = 0.2f;
					}
				}
				if (worldTransform_.translation_.z >= 2300) 
				{
					isGoal = true;
					speed = 5;
				}
				else {
					isGoal = false;
				}
				if (input_->PushKey(DIK_A)) {
					if (turnSpeed < 0.2)
					{
						turnSpeed -= 0.02;
					}
					if (turnSpeed < -0.20f) {
						turnSpeed = -0.2f;
					}
				}

				if (turnSpeed <= 0.00f) {
					turnSpeed += 0.01;
				}
				if (turnSpeed >= 0.00f) {
					turnSpeed -= 0.01;

				}
				
				/*if (turnSpeed < 0.00f) {
					turnSpeed = 0.0f;
				}*/
				break;

			case Phase::Brake://移動（ベクトルを加算）
				if (speed >= 0.03f) {
					speed -= 0.02;
				}
				if (speed < 0.03f) {
					speed = 0.03f;
				}

				if (turnSpeed <= 0.00f) {
					turnSpeed += 0.01;
				}
				if (turnSpeed >= 0.00f) {
					turnSpeed -= 0.01;
				}

				if (input_->PushKey(DIK_SPACE) == 0) {
					phase_ = Phase::Drive;
					
				}
				break;
			}
			worldTransform_.translation_ += move;
	}
	//worldTransform_.rotation_.y -= 0.02f;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, kMoveLimitX);
	//worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	//worldTransform_.translation_.y = min(worldTransform_.translation_.y, kMoveLimitY);
	//int timer = 10;
	//timer -= 1;
	//
	/*debugText_->SetPos(50, 70);
	debugText_->Printf("playermove.z:(%f)", move.z);*/
	
	//座標移動
	
	worldTransform_.TransferMatrix();
}

void Player::Update() {
	brakeIcon->SetSize({ 80,80 });

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	Move();
	Attack();
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//行列の再計算(更新)
	worldTransform_.TransferMatrix();
	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Update(); }

	//debugText_->SetPos(50, 50);
	//debugText_->Printf(
	//	"move:(%f,%f,%f)",
	//	worldTransform_.translation_.x,
	//	worldTransform_.translation_.y,
	//	worldTransform_.translation_.z);
	//debugText_->SetPos(50, 150);
	//debugText_->Printf(
	//	"rot:(%f,%f,%f)", worldTransform_.rotation_.x,worldTransform_.rotation_.y, worldTransform_.rotation_.z);

	//debugText_->SetPos(50, 170);
	//debugText_->Printf(
	//	"rotspeed:(%f)", turnSpeed);

	
}

void Player::Attack()
{
	if (isWin_ == false)
	{
	//worldTransform_.translation_.z += 0.05f;
	
	}
}

void Player::OnCollision()
{
	
	if (worldTransform_.translation_.z <= 2300)
	{
		isDead = true;
		isWin_ = true;
		worldTransform_.translation_.y = 550.05f;
		slow();
	}
}

void Player::WindCollision()
{
	worldTransform_.translation_.x += 0.04f;
	speed = 0.5f;
	//windSpeed += 0.2;
	//if (windSpeed >= 0.00f) {
	//	windSpeed -= 0.01;
	//}
}
//bounce
//void Player::WindCollision()
//{
//	worldTransform_.translation_.x += 0.03f;
//	speed -= 0.5f;
//	//windSpeed += 0.2;
//	//if (windSpeed >= 0.00f) {
//	//	windSpeed -= 0.01;
//	//}
//}

void Player::SpriteDraw()
{
	//brakeIcon->Draw();
}
void Player::Draw(ViewProjection& viewProjection_)
{
#pragma region 背景スプライト描画

#pragma endregion

#pragma region 3Dオブジェクト描画

	model_->Draw(worldTransform_, viewProjection_);
	bodyModel->Draw(worldTransform_, viewProjection_);
	taiyaModel->Draw(worldTransform_, viewProjection_);
	//if (speed > 1.5f) {
	//	spManager->Draw(viewProjection_);
	//}
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//弾描画
	//for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection_); }
#pragma endregion

#pragma region 前景スプライト描画

#pragma endregion
}
