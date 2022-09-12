#include "Title.h"
#include "GetMatrix.h"

Title::Title() {

}

void Title::Initialize(Model* model, uint32_t textureHandle)
{
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = TextureManager::Load("Start.png");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット

	worldTransform_.translation_ = { 0.0f,0.0f,-47.0f };
	worldTransform_.TransferMatrix();

}
void Title::OnCollision()
{
	worldTransform_.translation_.z -= 0.02f;
}

void Title::Restart()
{
	worldTransform_.translation_ = { 0.0f,0.0f,-47.0f };
}

void Title::Update() {
	//行列計算
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//行列の再計算(更新)
	worldTransform_.TransferMatrix();
	//worldTransform_.translation_.z += 0.05f;

	//if (worldTransform_.translation_.z >= -12.0f) {
	//	worldTransform_.translation_.z = -47.0f;
	//}

	/*debugText_->SetPos(50, 170);
	debugText_->Printf(
		"winmove:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);*/
}


void Title::Draw(ViewProjection& viewProjection)
{
#pragma region 背景スプライト描画

#pragma endregion

#pragma region 3Dオブジェクト描画
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


#pragma endregion

#pragma region 前景スプライト描画

#pragma endregion
}