#pragma once
#include "object.h"
class Camel : public object
{
public:
	void Initialize(Model* model_, Model* bodyModel, Model* taiyaModel);
	void Update();
	void Draw(ViewProjection viewProjection);

	bool GetCheckUpdate();

	void LoadTexture(TextureHandle tex);
	void OnCollision();
	void Reset();
	void Randomize();
	bool IsDead() { return isDead; }
	void revival() { isDead = false; };
private:
	Model* bodyModel = nullptr;
	Model* taiyaModel = nullptr;
	Model* model_ = nullptr;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	bool isCheckPointUpdate = false;
	bool isDead = false;
	float pos;
	//�s���t�F�[�Y
	enum class Phase {
		Approach,//�ڋ߂���
		Leave,//���E����
	};
	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
};

