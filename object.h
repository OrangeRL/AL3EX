#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Utill.h"
#include "ViewProjection.h"
#include "GetMatrix.h"
class object
{
public:
	object();
	~object();

	WorldTransform GetWorldTrans();
	void LoadModel(Model* model_);
	void LoadTexture(TextureHandle textureHandle_);

	void SetPos(Vector3 pos);
	void SetScale(Vector3 scale);

	Vector3 GetPos() { return worldTransform_.translation_; };
	Vector3 GetScale() { return worldTransform_.scale_; };
	Vector3 GetWorldPosition();
	void MatUpdate();

	WorldTransform worldTransform_;

	static void ScreenShake(Vector2 shake);
protected:

	Model* model_ = nullptr;
	TextureHandle textureHandle_;

	Vector3 initScale = { 0,0,0 };
	Vector3 initPos = { 0,0,0 };
	static Vector3 screenShake;

};

