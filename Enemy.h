#pragma once
#include "assert.h"
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
//<summary>
//敵
//</summary>
class Enemy
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Enemy();

	///<summary>///初期化///</summary>///<paramname="model">モデル</param>///<paramname="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, const Vector3& position,uint32_t textureHandle);
	///<summary>
	///更新
	///</summary>
	void Update();
	///<summary>
	///描画
	///</summary>
	void Draw(ViewProjection& viewProjection);

	void TransferMatrix();
	void Move();
	//行動フェーズ
	enum class Phase {
		Approach,   //接近する
		Leave,      //離脱する
	};
	//フェーズ
	Phase phase_ = Phase::Approach;
private:
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//3Dモデル
	Model* model_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	//速度
	Vector3 velocity_;
};