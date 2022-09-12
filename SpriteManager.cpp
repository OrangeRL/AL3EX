#include "SpriteManager.h"
#include "MyMath.h"
#include "Collsion.h"
#include <cassert>
#include "WinApp.h"

using namespace std;

Vector2 dashSkillPos = {
		WinApp::kWindowWidth - 160,
		WinApp::kWindowHeight - 160
};

void  SpriteManager::End()
{
	for (int i = 0; i < MAX_STACK; i++)
	{
		delete newstocks[i];
	}
	delete skillIconSp;
	delete shotIconSp;
	delete skillCoolAlpha;
	delete backWhite;
	delete backWhite2;
	delete backWhite3;
	delete lShift;
	delete hpRed;
	delete mouseIcon;
	delete jumpIcon;
	delete spaceIcon;
}

void SpriteManager::HealEffect(int heal)
{
	scrennAlpha = { 0,1,0,1 };
	hp += heal;
	if (hp > stock * 10)
	{
		hp = stock * 10;
	}
}

void SpriteManager::DeadInit()
{
	worldTransform_.translation_ = respawnPos;
	stock = 3;
	hp = 30;
	jumpSpd = 0;
	getHeartCount = 0;
	nohitFlag = true;

	isDead = false;
}

void SpriteManager::Initialize(Model* model_, Model* bodyModel, Model* taiyaModel)
{
	assert(model_);
	assert(bodyModel);
	assert(taiyaModel);

	worldTransform_.Initialize();
	worldTransform_.translation_ = respawnPos;

	this->model_ = model_;
	this->bodyModel = bodyModel;
	this->taiyaModel = taiyaModel;


	skillIconSp = Sprite::Create(TextureManager::Load("brake.png"), { 0,0 });
	/*shotIconSp = Sprite::Create(TextureManager::Load("shot_skill_icon.png"), { 0,0 });
	skillCoolAlpha = Sprite::Create(TextureManager::Load("alpha.png"), { 0,0 }, { 1,1,1,0.9f });

	backWhite = Sprite::Create(TextureManager::Load("white.png"), { 0,0 }, { 1,1,1,1 });
	backWhite2 = Sprite::Create(TextureManager::Load("white.png"), { 0,0 }, { 1,1,1,1 });
	backWhite3 = Sprite::Create(TextureManager::Load("white.png"), { 0,0 }, { 1,1,1,1 });

	lShift = Sprite::Create(TextureManager::Load("Lshift.png"), { 0,0 });
	mouseIcon = Sprite::Create(TextureManager::Load("MouseClick.png"), { 0,0 });
	jumpIcon = Sprite::Create(TextureManager::Load("jump_skill_icon.png"), { 0,0 });
	spaceIcon = Sprite::Create(TextureManager::Load("space.png"), { 0,0 });*/

	/*shotIconSp->SetSize({ 80,80 });
	shotIconSp->SetPosition({ dashSkillPos.x - 120 ,dashSkillPos.y });*/

	skillIconSp->SetSize({ 80,80 });
	skillIconSp->SetPosition(dashSkillPos);

	/*jumpIcon->SetSize({ 80,80 });
	jumpIcon->SetPosition({ dashSkillPos.x - 240, dashSkillPos.y });

	skillCoolAlpha->SetSize({ 80,80 });
	skillCoolAlpha->SetPosition(dashSkillPos);

	backWhite->SetSize({ 90,90 });
	backWhite->SetPosition({ dashSkillPos.x - 5,dashSkillPos.y - 5 });

	backWhite2->SetSize({ 90,90 });
	backWhite2->SetPosition({ dashSkillPos.x - 125,dashSkillPos.y - 5 });

	backWhite3->SetSize({ 90,90 });
	backWhite3->SetPosition({ dashSkillPos.x - 245,dashSkillPos.y - 5 });

	lShift->SetSize({ 120,30 });
	lShift->SetPosition({ dashSkillPos.x - 15,dashSkillPos.y + 75 });

	mouseIcon->SetSize({ 120,60 });
	mouseIcon->SetPosition({ dashSkillPos.x - 120 - 15,dashSkillPos.y + 75 });

	spaceIcon->SetSize({ 120,30 });
	spaceIcon->SetPosition({ dashSkillPos.x - 240 - 15,dashSkillPos.y + 75 });*/
}

void SpriteManager::SetSpawnPos(Vector3 pos)
{
	respawnPos = pos;
}

void SpriteManager::Update()
{
	for (int i = 0; i < 3; i++)
	{
		if (posY[i] < 0)
		{
			posY[i] += 1.5f;
		}
		if (posY[i] > 0)
		{
			posY[i] = 0;
		}
	}

	
	skillIconSp->SetSize({ 80,80 });
	skillIconSp->SetPosition({
		dashSkillPos.x,
		dashSkillPos.y + posY[1] });

}



void SpriteManager::Draw(ViewProjection viewProjection_)
{
	if (false)
	{
		debugText->SetPos(50, 50);
		debugText->Printf("move %f %f %f", move.x, move.y, move.z);
		debugText->SetPos(50, 70);
		debugText->Printf("translation_ %f %f %f",
			worldTransform_.translation_.x,
			worldTransform_.translation_.y,
			worldTransform_.translation_.z
		);
		debugText->SetPos(50, 90);
		debugText->Printf("left %d", stock);

		debugText->SetPos(50, 110);
		debugText->Printf("horizontalRotation %f",
			horizontalRotation);
		debugText->SetPos(50, 130);
		debugText->Printf("verticalRotation %f",
			verticalRotation
		);
		debugText->SetPos(50, 150);
		debugText->Printf("sideVec %f %f %f",
			sideVec.x, sideVec.y, sideVec.z
		);
		debugText->SetPos(50, 170);
		debugText->Printf("tempMoveVec %f %f %f",
			tempMoveVec.x, tempMoveVec.y, tempMoveVec.z
		);
		debugText->SetPos(50, 190);
		debugText->Printf("tempSideVec %f %f %f",
			tempSideVec.x, tempSideVec.y, tempSideVec.z
		);


	}

	if (mutekiTimer % 6 == 0)
	{
		model_->Draw(worldTransform_, viewProjection_);
		bodyModel->Draw(worldTransform_, viewProjection_);
		taiyaModel->Draw(worldTransform_, viewProjection_);
	}

}

void SpriteManager::SpriteDraw()
{
	//skillIconSp->Draw();
}

