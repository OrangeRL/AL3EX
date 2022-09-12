#pragma once
#include "Model.h"

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	Model* model_ = nullptr;
	Model* skydome = nullptr;
	Model* firewisp = nullptr;
	Model* player = nullptr;
	Model* body = nullptr;
	Model* carWindow = nullptr;
	Model* car = nullptr;
	Model* brake = nullptr;
	Model* goal = nullptr;
	Model* signalLight = nullptr;
	Model* signalPole = nullptr;
	Model* signalLamp = nullptr;
	Model* pyramid = nullptr;
	Model* rakuda = nullptr;
	Model* asteroid = nullptr;
	Model* star = nullptr;
	Model* gas = nullptr;
	Model* titleStar = nullptr;
	Model* titleRakuda = nullptr;
	Model* titleOba = nullptr;
	Model* titleCar = nullptr;
};