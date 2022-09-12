#include "WindManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void WindManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<WindObj> newBox = make_unique<WindObj>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void WindManager::Initialize(Model* model_)
{
	srand(time(NULL));
	pos = rand() % 5;

	this->model_ = model_;
	//floor
	for (int i = 0; i < 6; i++)
	{
		srand(time(NULL));
		pos = rand() % 5;
		SetBox({ 0, 0.0f, 10.0f + i * 400.0f }, { 50.0f,20.0f,20.0f });
		//SetBox({ pos + i * 2.0f-10,1.4f,10.0f + i * 80.0f-10 }, { 5.0f,1.0f,0.01f });
	}

}

void WindManager::Update()
{
	for (unique_ptr<WindObj>& Object : Objects)
	{
		Object->Update();
	}
}

void WindManager::Update2()
{

	for (unique_ptr<WindObj>& Object : Objects)
	{
		Object->Update2();
	}
}

void WindManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<WindObj>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

Vector3 WindManager::GetSpawnPos()
{
	return spawnPos;
}

void WindManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
