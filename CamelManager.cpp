#include "CamelManager.h"
#include "assert.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

void CamelManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Camel> newBox = make_unique<Camel>();
	newBox->Initialize(model_, bodyModel, taiyaModel);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void CamelManager::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
{
	assert(model_);
	assert(bodyModel);
	assert(taiyaModel);
	srand(time(NULL));
	pos = rand() % 100 + 50;
	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;

	for (int i = 0; i < 100; i++)
	{	
		srand(time(NULL));
		pos = rand() % 5;
		//SetBox({ pos+20 +i * 2.0f, 0.0f, 10.0f + i * 350.0f }, { 0.5f,0.5f,0.5f });
		//SetBox({ pos - 50 + i * 2.0f, 0.0f, 10.0f + i * 350.0f }, { 0.5f,0.5f,0.5f });
	}

}

void CamelManager::Update()
{

	for (unique_ptr<Camel>& Object : Objects)
	{
		Object->Update();
		
	}
}

void CamelManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Camel>& Object : Objects)
	{
		Object->Draw(viewProjection_);

	}
}

Vector3 CamelManager::GetSpawnPos()
{
	return spawnPos;
}

void CamelManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
