#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
///<summary>
///敵
///</summary>
class Enemy{
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Enemy();

	///<summary>///初期化///</summary>///<paramname="model">モデル</param>///<paramname="textureHandle">テクスチャハンドル</param>
	void Initialize();
	///<summary>
	///更新
	///</summary>
	void Update();
	///<summary>
	///描画
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};