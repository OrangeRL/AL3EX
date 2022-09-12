#pragma once
#include "Input.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Utill.h"
#include "Model.h"
//#include "SoundDataManager.h"

enum TitleMenu
{
	start,
	end,
};

class TitleScreen
{
public:
	void Initialize(Model* model, Model* model2, Model* model3, ViewProjection view);
	void Update();
	void Draw();

	void End();

	void BackDraw();
	void TitleFrontDraw();
	void FrontDraw();
	void TimeUpDraw();
	void BoostX1Draw();
	void BoostX0Draw();
	void ModelDraw(ViewProjection view);

	bool IsTitle() { return isTitle; };

	//void NotTitle() { isTitle = false; };
	void TitleBack() { isTitle = true; };

	bool isTitle = true;

	bool endflag = false;

private:
	Input* input = nullptr;
	Input* input_ = nullptr;
private:
	float posY[3] = { 0,0,0 };
	Sprite* titleBack = nullptr;
	Sprite* titleImageText = nullptr;
	Sprite* titleImage = nullptr;
	Sprite* brakeIcon = nullptr;
	Sprite* handleIcon = nullptr;
	Sprite* timeUpIcon = nullptr;
	Sprite* boostX1 = nullptr;
	Sprite* boostX0 = nullptr;
	Sprite* whiteLine = nullptr;

	Sprite* pedestrian = nullptr;

	Model* playerModel = nullptr;
	Model* playerModel2 = nullptr;
	Model* playerModel3 = nullptr;
	WorldTransform worldtransform;

	Vector2 uiPos[2];

	float oldHori = 0;
	float horizontalRotation = 0;

	float oldVer = 0;
	float verticalRotation = 0;

	int titleMenu = TitleMenu::start;

	int mouseAnimeNum = 0;
	int mouseAnimeTime = 0;
	float turnSpeed = 0.0;
	float speed = 0.4;
	enum class Phase {
		Drive,//接近する
		Brake,//離脱する

	};
	//フェーズ
	Phase phase_ = Phase::Drive;
};