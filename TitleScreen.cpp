#include "TitleScreen.h"
#include <math.h>
#include "WinApp.h"
#include "MyMath.h"
#include "GetMatrix.h"
Vector2 dashSkillPos2 = {
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
	worldtransform.scale_ = { 0.8f,0.8f,0.8f };


	input = Input::GetInstance();
	input_ = Input::GetInstance();
	brakeIcon = Sprite::Create(TextureManager::Load("brake.png"), { 0,0 });
	handleIcon = Sprite::Create(TextureManager::Load("handle.png"), { 0,0 });
	timeUpIcon = Sprite::Create(TextureManager::Load("timeUp.png"), { 0,0 });
	gameOver = Sprite::Create(TextureManager::Load("GameOver.png"), { 0,0 });
	boostX0 = Sprite::Create(TextureManager::Load("boostX0.png"), { 0,0 });
	boostX1 = Sprite::Create(TextureManager::Load("boostX1.png"), { 0,0 });
	titleBack = Sprite::Create(TextureManager::Load("pastelblue.png"),
		{ 0,0 });
	titleBack->SetSize({ WinApp::kWindowWidth,WinApp::kWindowHeight });

	setsumei = Sprite::Create(TextureManager::Load("Setsumei.png"),
		{ 0,0 });
	setsumei->SetSize({ 500 * 1.3f, 500 * 1.3f });

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
	ThanksText= Sprite::Create(TextureManager::Load("thanks.png"),
		{ 0,0 });
	ThanksText->SetSize({ 220 * 1.3f, 220 * 1.3f });

	ForText = Sprite::Create(TextureManager::Load("for.png"),
		{ 0,0 });
	ForText->SetSize({ 220 * 1.3f, 220 * 1.3f });

	PlayingText = Sprite::Create(TextureManager::Load("playing.png"),
		{ 0,0 });
	PlayingText->SetSize({ 220 * 1.3f, 220 * 1.3f });

	start = Sprite::Create(TextureManager::Load("StartT.png"),
		{ 0,0 });
	start->SetSize({ 120 * 1.3f, 120 * 1.3f });

	startS = Sprite::Create(TextureManager::Load("S.png"),
		{ 0,0 });
	startS->SetSize({ 120 * 1.3f, 120 * 1.3f });

	startT = Sprite::Create(TextureManager::Load("T.png"),
		{ 0,0 });
	startT->SetSize({ 120 * 1.3f, 120 * 1.3f });

	startA = Sprite::Create(TextureManager::Load("A.png"),
		{ 0,0 });
	startA->SetSize({ 120 * 1.3f, 120 * 1.3f });

	startR = Sprite::Create(TextureManager::Load("R.png"),
		{ 0,0 });
	startR->SetSize({ 120 * 1.3f, 120 * 1.3f });

	startT2 = Sprite::Create(TextureManager::Load("T2.png"),
		{ 0,0 });
	startT2->SetSize({ 120 * 1.3f, 120 * 1.3f });

	spriteTimerText = Sprite::Create(TextureManager::Load("timeLeftText.png"),
		{ 0,0 });
	spriteTimerText->SetSize({ 100 * 1.3f, 100 * 1.3f });

	start2 = Sprite::Create(TextureManager::Load("StartT.png"),
		{ 0,0 });
	start2->SetSize({ 100 * 1.3f, 100 * 1.3f });

	startS2 = Sprite::Create(TextureManager::Load("S.png"),
		{ 0,0 });
	startS2->SetSize({ 100 * 1.3f, 100 * 1.3f });

	startT3 = Sprite::Create(TextureManager::Load("T.png"),
		{ 0,0 });
	startT3->SetSize({ 100 * 1.3f, 100 * 1.3f });

	startA2 = Sprite::Create(TextureManager::Load("A.png"),
		{ 0,0 });
	startA2->SetSize({ 100 * 1.3f, 100 * 1.3f });

	startR2 = Sprite::Create(TextureManager::Load("R.png"),
		{ 0,0 });
	startR2->SetSize({ 100 * 1.3f, 100 * 1.3f });

	startT4 = Sprite::Create(TextureManager::Load("T2.png"),
		{ 0,0 });
	startT4->SetSize({ 100 * 1.3f, 100 * 1.3f });
}

void TitleScreen::Update()
{
	brakeIcon->SetSize({ 180 + speed * 15,180 + speed * 15});
	brakeIcon->SetPosition({
		dashSkillPos2.x-30 - speed * 15,
		dashSkillPos2.y +40 + posY[1]-speed*15});

	boostX1->SetSize({ 180,180 });
	boostX1->SetPosition({
		250,
		dashSkillPos2.y - 20 });

	boostX0->SetSize({ 180,180 });
	boostX0->SetPosition({
		250,
		dashSkillPos2.y - 20 });

	handleIcon->SetSize({ 200,200 });
	handleIcon->SetPosition({
		0,
		dashSkillPos2.y -50 });
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


	switch (phase2_) {
	case Phase2::Approach:
	default://移動（ベクトルを加算）
		turning -= 0.0003f;

		//規定の位置に到達したら離脱
		if (turning < -0.03f) {
			phase2_ = Phase2::Leave;
		}
		break;
	case Phase2::Leave://移動（ベクトルを加算）

		turning += 0.0003f;
		if (turning > 0.03f) {
			phase2_ = Phase2::Approach;
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
	titleImageText->SetRotation({ turning });
	titleImageText->SetPosition({ 60,
		-20 + cosf(DegreeConversionRad(time[0])) * 15.0f
		});

	spriteTimerText->SetRotation({ turning*2 });
	spriteTimerText->SetPosition({ 10 + cosf(DegreeConversionRad(time[0])) * 5.0f,
		10 + cosf(DegreeConversionRad(time[0])) * 5.0f
		});

	setsumei->SetRotation({ turning*0.5f });
	setsumei->SetPosition({ 300,
		30 + cosf(DegreeConversionRad(time[0])) * 2.0f
		});
	//WinApp::kWindowWidth - 200,WinApp::kWindowHeight - 100
	ThanksText->SetRotation({ turning * 2 });
	ThanksText->SetPosition({ 600 - 20,
		220-15 + cosf(DegreeConversionRad(time[0])) * 12.0f
		});
	ForText->SetRotation( turning * 2.5f );
	ForText->SetPosition({ 600 - 20,
		220 + cosf(DegreeConversionRad(time[0])) * 9.0f
		});
	PlayingText->SetRotation({ turning * 1.3f });
	PlayingText->SetPosition({ 600 - 20,
		220+15 + cosf(DegreeConversionRad(time[0])) * 7.0f
		});

	start->SetRotation({ turning*2 });
	start->SetPosition({ 600-20,
		600-40 + cosf(DegreeConversionRad(time[0])) * 12.0f
		});
	startS->SetRotation({ turning*3 });
	startS->SetPosition({ 600-20,
		602-40 + cosf(DegreeConversionRad(time[0])) * 10.0f
		});
	startT->SetRotation({ turning-0.0003f *1.5f });
	startT->SetPosition({ 600-20 + cosf(DegreeConversionRad(time[0])) * 6.0f,
		600-40 + cosf(DegreeConversionRad(time[0])) * 7.0f
		});
	startA->SetRotation({ turning*3 });
	startA->SetPosition({ 600-20 + cosf(DegreeConversionRad(time[0])) * 3.0f,
		600-40 + cosf(DegreeConversionRad(time[0])) * 5.0f
		});
	startR->SetRotation({ turning*2.5f });
	startR->SetPosition({ 600-20 + cosf(DegreeConversionRad(time[0])) * 5.0f,
		604-40 + cosf(DegreeConversionRad(time[0])) * 7.0f
		});
	startT2->SetRotation({ turning*3 });
	startT2->SetPosition({ 600-20,
		602-40 + cosf(DegreeConversionRad(time[0])) * 6.0f
		});


	start2->SetRotation({ turning * 2 });
	start2->SetPosition({ 1100,
		600 - 16 + cosf(DegreeConversionRad(time[0])) * 12.0f
		});
	startS2->SetRotation({ turning * 5 });
	startS2->SetPosition({ 1100,
		602 - 16 + cosf(DegreeConversionRad(time[0])) * 6.0f
		});
	startT3->SetRotation({ turning - 0.0003f * 1.5f });
	startT3->SetPosition({ 1100 + cosf(DegreeConversionRad(time[0])) * 4.0f,
		600 - 16 + cosf(DegreeConversionRad(time[0])) * 7.0f
		});
	startA2->SetRotation({ turning * 3 });
	startA2->SetPosition({ 1100 + cosf(DegreeConversionRad(time[0])) * 3.0f,
		600 - 16 + cosf(DegreeConversionRad(time[0])) * 5.0f
		});
	startR2->SetRotation({ turning * 2.5f });
	startR2->SetPosition({ 1100 + cosf(DegreeConversionRad(time[0])) * 5.0f,
		604 - 16 + cosf(DegreeConversionRad(time[0])) * 7.0f
		});
	startT4->SetRotation({ turning * 3 });
	startT4->SetPosition({ 1100,
		602 - 16 + cosf(DegreeConversionRad(time[0])) * 6.0f
		});


	whiteLine->SetPosition({ 0 + cosf(DegreeConversionRad(time[0])) * 900.0f,
		-20 + cosf(DegreeConversionRad(time[0])) * 3.0f
		});
	whiteLine->SetRotation({ turning });
	titleImage->SetPosition({ 20,
		100 + cosf(DegreeConversionRad(time[0])) * 15.0f
		});
	titleImage->SetRotation({ -0.4f - turning});
	pedestrian->SetPosition({ 500,
		500 + cosf(DegreeConversionRad(time[0])) * 22.0f
		});

	timeUpIcon->SetSize({ 400,400 });
	timeUpIcon->SetPosition({ 400,
		200
		});
	gameOver->SetSize({ 400,400 });
	gameOver->SetPosition({ 400,
		200
		});
	//マウスでカメラを動かす処理
	Vector2 temp = { 1920 / 2, 1080 / 2 };

	worldtransform.rotation_.y = horizontalRotation + 3.1;
	worldtransform.rotation_.x += verticalRotation + 0.002f;
	worldtransform.rotation_.z += verticalRotation + 0.002f;


	worldtransform.translation_.x += 0.05f;
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

void TitleScreen::FrontSetsumeiDraw()
{
	whiteLine->Draw();
	start2->Draw();
	startT3->Draw();
	startS2->Draw();
	startA2->Draw();
	startR2->Draw();
	startT4->Draw();
	setsumei->Draw();
	

}
void TitleScreen::TitleFrontDraw()
{
	titleImage->Draw();
	titleImageText->Draw();
	start->Draw();
	startT->Draw();
	startS->Draw();
	startA->Draw();
	startR->Draw();
	startT2->Draw();
}
void TitleScreen::WinDraw()
{
	titleImage->Draw();
	titleImageText->Draw();
	ThanksText->Draw();
	ForText->Draw();
	PlayingText->Draw();

	start->Draw();
	startT->Draw();
	startS->Draw();
	startA->Draw();
	startR->Draw();
	startT2->Draw();
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
void TitleScreen::GameOverDraw()
{
	gameOver->Draw();
}
void TitleScreen::BoostX1Draw()
{
	boostX1->Draw();
}
void TitleScreen::BoostX0Draw()
{
	boostX0->Draw();
}
void TitleScreen::SpriteTimerText()
{
	spriteTimerText->Draw();
}