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
//自キャラ
//</summary>
class PlayerBullet
{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	PlayerBullet();

	/////<summary>
	/////初期化
	///</summary>
	///<paramname="model">モデル</param>
	///<paramname="position">初期座標</param>

	void Initialize(Model* model, const Vector3& position);
	/////<summary>
	/////更新
	/////</summary>
	void Update();
	/////<summary>
	/////描画
	/////</summary>
	void Draw(const ViewProjection& viewProjection);
	void TransferMatrix();
private:
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	Model* model_ = nullptr;
	//ワールド変換データ
	WorldTransform worldTransform_;
	
};