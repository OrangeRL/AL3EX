#include "PedestrianManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void PedestrianManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Pedestrian> newBox = make_unique<Pedestrian>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void PedestrianManager::Initialize(Model* model_)
{
	srand(time(NULL));
	pos = rand() % 5;

	this->model_ = model_;
	//floor
	for (int i = 0; i < 10; i++)
	{
		srand(time(NULL));
		pos = rand() % 5;
		//SetBox({ pos + i * 2.0f, 0.0f, 10.0f + i * 250.0f }, { 30.0f,20.0f,20.01f });
		//SetBox({ pos + i * 2.0f-10,1.4f,10.0f + i * 80.0f-10 }, { 5.0f,1.0f,0.01f });
	}

}

void PedestrianManager::Update()
{
	for (unique_ptr<Pedestrian>& Object : Objects)
	{
		Object->Update();
	}
}

void PedestrianManager::Update2()
{
	
	for (unique_ptr<Pedestrian>& Object : Objects)
	{
		Object->Update2();
	}
}

void PedestrianManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Pedestrian>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

Vector3 PedestrianManager::GetSpawnPos()
{
	return spawnPos;
}

void PedestrianManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
