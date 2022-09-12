#include "Title.h"
#include "GetMatrix.h"

Title::Title() {

}

void Title::Initialize(Model* model, uint32_t textureHandle)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = TextureManager::Load("Start.png");
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g

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
	//�s��v�Z
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//�s��̍Čv�Z(�X�V)
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
#pragma region �w�i�X�v���C�g�`��

#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


#pragma endregion

#pragma region �O�i�X�v���C�g�`��

#pragma endregion
}