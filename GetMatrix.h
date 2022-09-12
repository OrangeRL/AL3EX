#pragma once
#include "WorldTransform.h"
#include "DirectXCommon.h"

//�P�ʍs��֐�
Matrix4 Identity();
float DegreeConversionRad(float frequencymethod);
//��]�s��
Matrix4 Rot(Vector3 worldTransform_);

//�X�P�[���s��
Matrix4 Scale(Vector3 worldTransform_);

//�e�̉�]�p�v�Z
Vector3 BulletRot(Vector3 velocity, Matrix4 transform);
//���s�ړ��s��
Matrix4 Transform(Vector3 worldTransform_);
//����
Matrix4 Mat(Vector3 worldTransform_);

Vector3 Vector3Transform(Vector3 velocity, Matrix4 amount);

