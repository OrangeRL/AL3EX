#include "ModelManager.h"

ModelManager::ModelManager()
{
	model_ = Model::Create();
	skydome = Model::CreateFromOBJ("skydome");
	firewisp = Model::CreateFromOBJ("firewisp");
	player = Model::CreateFromOBJ("car2");
	body = Model::CreateFromOBJ("carBlack");
	carWindow = Model::CreateFromOBJ("carWindow");
	car = Model::CreateFromOBJ("car");
	brake = Model::CreateFromOBJ("goalWhite");
	goal = Model::CreateFromOBJ("goalPost");

	signalPole = Model::CreateFromOBJ("signalPole");
	signalLamp = Model::CreateFromOBJ("signalLamp");
	signalLight = Model::CreateFromOBJ("signalLight");

	pyramid = Model::CreateFromOBJ("pyramid");
	rakuda = Model::CreateFromOBJ("rakuda");
	asteroid = Model::CreateFromOBJ("asteroid");
	star = Model::CreateFromOBJ("star");
	titleStar = Model::CreateFromOBJ("titlestar");
	titleRakuda = Model::CreateFromOBJ("rakudatitle");
	titleOba = Model::CreateFromOBJ("titleoba");
	titleCar = Model::CreateFromOBJ("cartitle");
	gas = Model::CreateFromOBJ("gas");
}

ModelManager::~ModelManager()
{
	delete model_;
	delete skydome;
	delete firewisp;
	delete player;
	delete body;
	delete carWindow;
	delete car;
	delete brake;
	delete goal;
	delete signalPole;
	delete signalLamp;
	delete signalLight;
	delete pyramid;
	delete star;
	delete gas;
}