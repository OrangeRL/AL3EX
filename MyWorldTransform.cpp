//#include "WorldTransform.h"
//#include <math.h>
//#include "MathUtility.h"
//
//void WorldTransform::CreateScale()
//{
//	//�X�P�[����ݒ肷����
//	matScale.m[0][0] = scale_.x;
//	matScale.m[1][1] = scale_.y;
//	matScale.m[2][2] = scale_.z;
//	matScale.m[3][3] = 1;
//
//	matWorld_.MatrixUint();
//	matWorld_ *= matScale;
//}
//
//void WorldTransform::CreateRot()
//{
//
//	matRot.MatrixUint();
//	matRotX.MatrixUint();
//	matRotY.MatrixUint();
//	matRotZ.MatrixUint();
//
//	matRotZ.m[0][0] = cos(rotation_.z);
//	matRotZ.m[0][1] = sin(rotation_.z);
//	matRotZ.m[1][0] = -sin(rotation_.z);
//	matRotZ.m[1][1] = cos(rotation_.z);
//
//	matRotX.m[1][1] = cos(rotation_.x);
//	matRotX.m[1][2] = sin(rotation_.x);
//	matRotX.m[2][1] = -sin(rotation_.x);
//	matRotX.m[2][2] = cos(rotation_.x);
//
//	matRotY.m[0][0] = cos(rotation_.y);
//	matRotY.m[0][2] = -sin(rotation_.y);
//	matRotY.m[2][0] = sin(rotation_.y);
//	matRotY.m[2][2] = cos(rotation_.y);
//
//	matRot *= matRotZ;
//	matRot *= matRotX;
//	matRot *= matRotY;
//
//	matWorld_.MatrixUint();
//	matWorld_ *= matRot;
//}
//
//void WorldTransform::CreateTrans()
//{
//	matTrans = MathUtility::Matrix4Identity();
//
//	matTrans.m[3][0] = translation_.x;
//	matTrans.m[3][1] = translation_.y;
//	matTrans.m[3][2] = translation_.z;
//
//	matWorld_.MatrixUint();
//	matWorld_ *= matTrans;
//}
//
//void WorldTransform::MatrixCmp()
//{
//	matWorld_.MatrixUint();
//	//�X�P�[�����O�s��
//	matWorld_ *= matScale;
//	//��]�s��
//	matWorld_ *= matRot;
//	//���s�ړ��s��
//	matWorld_ *= matTrans;
//}
//
//void WorldTransform::UpdateMatrix()
//{
//	CreateScale();
//	CreateRot();
//	CreateTrans();
//	MatrixCmp();
//}