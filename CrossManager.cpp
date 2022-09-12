#include "CrossManager.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void CrossManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Cross> newBox = make_unique<Cross>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void CrossManager::Initialize(Model* model_)
{
	srand(time(NULL));
	pos = rand() % 5;
	this->model_ = model_;
	//floor
	for (int i = 0; i < 10; i++)
	{
		SetBox({ 0,0.02f,15.0f + i * 250.0f }, { 12,0.01,12 });
	}
	//for (int i = 0; i < 25; i++)
	//{
	//	SetBox({ -15,19,4 + i * 20.0f }, { 8,20,5 });
	//}

}

void CrossManager::Update()
{

	for (unique_ptr<Cross>& Object : Objects)
	{
		Object->Update();

	}
}

void CrossManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Cross>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

Vector3 CrossManager::GetSpawnPos()
{
	return spawnPos;
}

void CrossManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
