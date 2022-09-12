#include"skydome.h"
#include"UpdateMatrix.h"

void skydome::Initialize(Model* model) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	/*worldTransform_.scale_ = { 50,50,5000 };
	worldTransform_.translation_ = { 0,0,500 };
	worldTransform_.rotation_ = { 0,0,300 };*/

	worldTransform_.translation_ = { 0,0,500 };
	worldTransform_.rotation_ = { 0,0,0 };
	//ワールド変換の初期化
	worldTransform_.Initialize();

	/*TransferMatrix();
	worldTransform_.TransferMatrix();*/
}
void skydome::Move() {
	//// キャラクターの移動ベクトル
	//Vector3 move = { 0,0,0 };

	////座標移動
	//worldTransform_.translation_ += move;
	//worldTransform_.TransferMatrix();
}
void skydome::Update() {
	worldTransform_.scale_ = { 500,500,5000 };
	worldTransform_.matWorld_ = Identity();
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	Move();

	worldTransform_.TransferMatrix();
}
void skydome::Update2() {
	worldTransform_.scale_ = { 800,800,1900 };
	worldTransform_.matWorld_ = Identity();
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);
	Move();

	worldTransform_.TransferMatrix();
}
void skydome::Draw(ViewProjection& viewProjection_) {
	//3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection_);
}
