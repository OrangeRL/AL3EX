#include "PyramidManager.h"
#include "assert.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void PyramidManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Pyramid> newBox = make_unique<Pyramid>();
	newBox->Initialize(model_, bodyModel, taiyaModel);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void PyramidManager::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
{
	assert(model_);
	assert(bodyModel);
	assert(taiyaModel);
	srand(time(NULL));
	pos = rand() % 5;
	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;
	//floor
	for (int i = 0; i < 6; i++)
	{
		SetBox({ 80 + i * 10.0f,0.0f,10.0f + i * 250.0f },   { 10.5,10.5,10.5 });
		SetBox({-80 - i * 10.0f,0.0f,10.0f + i * 250.0f }, { 10.5,10.5,10.5 });
	}
	//for (int i = 0; i < 10; i++)
	//{
	//	SetBox({ 11,0.0f,25.0f + i * 250.0f }, { 0.5,0.5,0.5 });
	//}
	//for (int i = 0; i < 25; i++)
	//{
	//	SetBox({ -15,19,4 + i * 20.0f }, { 8,20,5 });
	//}

}

void PyramidManager::Update()
{

	for (unique_ptr<Pyramid>& Object : Objects)
	{
		Object->Update();

	}
}

void PyramidManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Pyramid>& Object : Objects)
	{
		Object->Draw(viewProjection_);

	}
}

Vector3 PyramidManager::GetSpawnPos()
{
	return spawnPos;
}

void PyramidManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
