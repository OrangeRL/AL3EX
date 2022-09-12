#include "TitleScreen.h"
#include <math.h>
#include "WinApp.h"
#include "MyMath.h"
#include "GetMatrix.h"
Vector2 dashSkillPos = {
		WinApp::kWindowWidth - 160,
		WinApp::kWindowHeight - 160
};
void TitleScreen::Initialize(Model* model, Model* model2, Model* model3, ViewProjection view)
{
	playerModel = model;
	playerModel2 = model2;
	playerModel3 = model3;

	worldtransform.Initialize();
	worldtransform.translation_ = { view.eye.x-2,view.eye.y - 2.5f,view.eye.z + 20 };
	worldtransform.rotation_ = { 0,1,0 };

	input = Input::GetInstance();
	input_ = Input::GetInstance();
	brakeIcon = Sprite::Create(TextureManager::Load("brake.png"), { 0,0 });
	handleIcon = Sprite::Create(TextureManager::Load("handle.png"), { 0,0 });
	timeUpIcon = Sprite::Create(TextureManager::Load("timeUp.png"), { 0,0 });
	boostX0 = Sprite::Create(TextureManager::Load("boostX0.png"), { 0,0 });
	boostX1 = Sprite::Create(TextureManager::Load("boostX1.png"), { 0,0 });
	titleBack = Sprite::Create(TextureManager::Load("pastelblue.png"),
		{ 0,0 });
	titleBack->SetSize({ WinApp::kWindowWidth,WinApp::kWindowHeight });

	titleImageText = Sprite::Create(TextureManager::Load("titleImage.png"),
		{ 0,0 });
	titleImageText->SetSize({ 300 * 1.3f, 300 * 1.3f });

	whiteLine = Sprite::Create(TextureManager::Load("whiteLine.png"),
		{ 0,0 });
	whiteLine->SetSize({ 1000 * 1.3f, 1000 * 1.3f });

	pedestrian = Sprite::Create(TextureManager::Load("obasil.png"),
		{ 0,0 });
	pedestrian->SetSize({ 80 * 1.3f, 80 * 1.3f });

	titleImage = Sprite::Create(TextureManager::Load("handle2.png"),
		{ 0,0 });
	titleImage->SetSize({ 200 * 1.3f, 200 * 1.3f });
}

void TitleScreen::Update()
{
	brakeIcon->SetSize({ 180 + speed * 15,180 + speed * 15});
	brakeIcon->SetPosition({
		dashSkillPos.x-30 - speed * 15,
		dashSkillPos.y +40 + posY[1]-speed*15});

	boostX1->SetSize({ 180,180 });
	boostX1->SetPosition({
		250,
		dashSkillPos.y - 20 });

	boostX0->SetSize({ 180,180 });
	boostX0->SetPosition({
		250,
		dashSkillPos.y - 20 });

	handleIcon->SetSize({ 200,200 });
	handleIcon->SetPosition({
		0,
		dashSkillPos.y -50 });
	handleIcon->SetRotation({turnSpeed});

	Vector3 approachMove = { 0,0,0 };
	Vector3 leaveMove = { 0,0,0 };
	approachMove = { 0.0f,0.0f,0.0 };
	leaveMove = { -0.0,0.0,-0.0 };
	Vector3 move = { 0,0,0 };
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

		if (input_->PushKey(DIK_D)) {
			if (turnSpeed < 0.2)
			{
				turnSpeed += 0.02;
			}
			if (turnSpeed > 0.20f) {
				turnSpeed = 0.2f;
			}
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
			speed -= 0.03;
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

	static int time[4] = { 150,100,50,0 };
	static int timespd[4] = { 1,1,1,1 };

	for (int i = 0; i < 4; i++)
	{
		time[i] += timespd[i];
		if (time[i] >= 360 || time[i] <= 0)
		{
			timespd[i] = -timespd[i];
		}
	}

	titleImageText->SetPosition({ 50,
		-20 + cosf(DegreeConversionRad(time[0])) * 22.0f
		});

	whiteLine->SetPosition({ 0 + cosf(DegreeConversionRad(time[0])) * 900.0f,
		-20 + cosf(DegreeConversionRad(time[0])) * 20.0f
		});
	
	titleImage->SetPosition({ 20,
		100 + cosf(DegreeConversionRad(time[0])) * 22.0f
		});
	titleImage->SetRotation({ -0.4 });
	pedestrian->SetPosition({ 500,
		500 + cosf(DegreeConversionRad(time[0])) * 22.0f
		});

	timeUpIcon->SetSize({ 400,400 });
	timeUpIcon->SetPosition({ 400,
		200
		});
	//マウスでカメラを動かす処理
	Vector2 temp = { 1920 / 2, 1080 / 2 };

	worldtransform.rotation_.y = horizontalRotation + 3.1;
	worldtransform.rotation_.x = verticalRotation;

	worldtransform.translation_.x += 0.1f;
	worldtransform.translation_.y = cosf(DegreeConversionRad(time[0])) * 1.5f;
	if (worldtransform.translation_.x > 25.0f) {
		worldtransform.translation_.x = -25.0f;
	}

	//行列計算
	worldtransform.matWorld_ = Scale(worldtransform.scale_);
	worldtransform.matWorld_ *= Rot(worldtransform.rotation_);
	worldtransform.matWorld_ *= Transform(worldtransform.translation_);
	worldtransform.TransferMatrix();

}
void TitleScreen::ModelDraw(ViewProjection view)
{
	playerModel->Draw(worldtransform, view);
	playerModel2->Draw(worldtransform, view);
	playerModel3->Draw(worldtransform, view);
}
void TitleScreen::BackDraw()
{
	titleBack->Draw();
	whiteLine->Draw();
}
void TitleScreen::TitleFrontDraw()
{
	titleImage->Draw();
	titleImageText->Draw();
	
}
void TitleScreen::FrontDraw()
{
	brakeIcon->Draw();
	handleIcon->Draw();
	//timeUpIcon->Draw();
}
void TitleScreen::TimeUpDraw()
{
	timeUpIcon->Draw();
}
void TitleScreen::BoostX1Draw()
{
	boostX1->Draw();
}
void TitleScreen::BoostX0Draw()
{
	boostX0->Draw();
}