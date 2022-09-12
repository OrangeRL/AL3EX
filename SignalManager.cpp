#include "SignalManager.h"
#include "assert.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void SignalManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Signal> newBox = make_unique<Signal>();
	newBox->Initialize(model_, bodyModel, taiyaModel);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void SignalManager::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
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
	for (int i = 0; i < 10; i++)
	{
		SetBox({ 10,0.0f,10.0f + i * 250.0f }, { 0.5,0.5,0.5 });
	}
	for (int i = 0; i < 10; i++)
	{
		SetBox({ 11,0.0f,25.0f + i * 250.0f }, { 0.5,0.5,0.5 });
	}
	//for (int i = 0; i < 25; i++)
	//{
	//	SetBox({ -15,19,4 + i * 20.0f }, { 8,20,5 });
	//}

}

void SignalManager::Update()
{

	for (unique_ptr<Signal>& Object : Objects)
	{
		Object->Update();

	}
}

void SignalManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Signal>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	
	}
}

Vector3 SignalManager::GetSpawnPos()
{
	return spawnPos;
}

void SignalManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
