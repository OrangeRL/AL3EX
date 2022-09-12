#pragma once
#include "WorldTransform.h"
#include "DirectXCommon.h"

//単位行列関数
Matrix4 Identity();
float DegreeConversionRad(float frequencymethod);
//回転行列
Matrix4 Rot(Vector3 worldTransform_);

//スケール行列
Matrix4 Scale(Vector3 worldTransform_);

//弾の回転用計算
Vector3 BulletRot(Vector3 velocity, Matrix4 transform);
//平行移動行列
Matrix4 Transform(Vector3 worldTransform_);
//合成
Matrix4 Mat(Vector3 worldTransform_);

Vector3 Vector3Transform(Vector3 velocity, Matrix4 amount);

