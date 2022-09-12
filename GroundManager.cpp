#include "GroundManager.h"
using namespace std;

void GroundManager::SetBox(Vector3 pos, Vector3 scale)
{
	unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
	newBox->Initialize(model_);
	newBox->SetPos({ pos.x, pos.y, pos.z });
	newBox->SetScale({ scale.x, scale.y, scale.z });
	Objects.push_back(std::move(newBox));
}


void GroundManager::Initialize(Model* model_)
{
	this->model_ = model_;
	//floor
	//SetBox({ 10,20,20 }, { 5,20,5 });
	//SetBox({ 0,0,10 }, { 5,0.04,5 });
	SetBox({ 62,0,0 }, { 50,0.01,810 });
	SetBox({ -62,0,10 }, { 50,0.01,810 });
	//ŠK’i
	//SetBox({ 0,0,0 }, { 5,2,2 });
	//SetBox({ 0,0,2 }, { 5,4,2 });
	//SetBox({ 0,0,4 }, { 5,6,2 });
	//SetBox({ 0,0,6 }, { 5,8,2 });
	
	//ŠK’iloop
	 	for (int i = 0; i < 100; i++)
	{
		SetBox(
			{ 
			0, 
			0,
			-50 + i * 24.0f
			}, 
			{ 12,0.01,12 });

		/*SetBox({ 20,0,-50 + i * 24.0f }, { 12,0.01,12 });
		SetBox({ -20,0,-50 + i * 24.0f }, { 12,0.01,12 });*/
	}
	//for (int i = 0; i < 50; i++)
	//{
	//	SetBox(
	//		{ 
	//		0, 
	//		0 + i * 2.0f,
	//		2 + i * 2.0f
	//		}, 
	//		{ 5,1,2 });
	//}
		for (int i = 0; i < 5; i++)
		{
			unique_ptr<BoxObj> newBox = make_unique<BoxObj>();
			newBox->Initialize(model_);
			newBox->LoadTexture(TextureManager::Load("old.png"));
			newBox->SetPos({ 0,5 + i * 10.0f,0 });
			newBox->SetScale({ 100,100,100 });
			enforceObjects.push_back(std::move(newBox));
		}

		SetSpawnPos({ 0,0,50 }, 10);
}

void GroundManager::Update()
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Update();
	}
}

void GroundManager::Update2()
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Update2();
	}
}

void GroundManager::Update3()
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Update3();
	}
}

void GroundManager::Draw(ViewProjection viewProjection_)
{
	for (unique_ptr<BoxObj>& Object : Objects)
	{
		Object->Draw(viewProjection_);
	}
}

Vector3 GroundManager::GetSpawnPos()
{
	return spawnPos;
}

void GroundManager::SetSpawnPos(Vector3 pos, float yScale)
{
	spawnPos = pos;
	spawnPos.y += yScale * 2;
}
