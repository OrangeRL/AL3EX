#include "BuildingManager.h"
using namespace std;

void BuildingManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<Building> newBox = make_unique<Building>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void BuildingManager::Initialize(Model* model_)
{
	this->model_ = model_;
	//floor
	for (int i = 0; i < 95; i++) 
	{
		SetBox({ 20,19,-20 + i * 25.0f }, { 8,20,5 });
		/*SetBox({ 40,19,-20 + i * 25.0f }, { 8,20,5 });*/
		SetBox({ -20,19,-20 + i * 25.0f }, { 8,20,5 });
		/*SetBox({ -40,19,-20 + i * 25.0f }, { 8,20,5 });*/
	}


	
	/*for (int i = 0; i < 25; i++)
	{*/
		//SetBox({ 20,19,25.0f }, { 8,20,5 });
	}


void BuildingManager::Update()
{
	
	for (unique_ptr<Building>& Object : Objects)
	{
		Object->Update();
		
	}
}

void BuildingManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<Building>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

Vector3 BuildingManager::GetSpawnPos()
{
	return spawnPos;
}

void BuildingManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
