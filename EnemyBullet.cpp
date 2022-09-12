#include "EnemyBullet.h"
#include "Enemy.h"
#include "UpdateMatrix.h"

EnemyBullet::EnemyBullet()
{
}

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("EnemyBullet.png");
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	input_ = Input::GetInstance();
}



void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

void EnemyBullet::Update() {
	//���W���ړ�������i1�t���[�����̈ړ��ʂ𑫂����ށj
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
	/*if (input_->TriggerKey(DIK_R))
	{
		isDead_ = true;
	}*/
	//�s��v�Z
	worldTransform_.matWorld_ = Scale(worldTransform_.scale_);
	worldTransform_.matWorld_ *= Rot(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= Transform(worldTransform_.translation_);

	//�s��̍Čv�Z(�X�V)
	worldTransform_.TransferMatrix();
}

Vector3 EnemyBullet::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
void EnemyBullet::Draw(const ViewProjection& viewProjection)
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


