//#include "Collsion.h"
//#include "Utill.h"
//
////�Ȃ񂩌����ڂ�蓖���蔻�肪�L�����Ɋ�����
////�����X�P�[���𔼌a�Ƃ��Ĉ����Ă��邩��H
//bool BoxColAABB(WorldTransform worldTransformA, WorldTransform worldTransformB)
//{
//	int DistanceX = worldTransformA.translation_.x - worldTransformB.translation_.x;
//	int DistanceY = worldTransformA.translation_.y - worldTransformB.translation_.y;
//	int DistanceZ = worldTransformA.translation_.z - worldTransformB.translation_.z;
//
//	DistanceX = Abs(DistanceX);
//	DistanceY = Abs(DistanceY);
//	DistanceZ = Abs(DistanceZ);
//
//	if (DistanceX <= worldTransformA.scale_.x + worldTransformB.scale_.x &&
//		DistanceY <= worldTransformA.scale_.y + worldTransformB.scale_.y &&
//		DistanceZ <= worldTransformA.scale_.z + worldTransformB.scale_.z)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool BoxColAABB(WorldTransform worldTransformA, Vector3 pos, Vector3 scale)
//{
//	int DistanceX = worldTransformA.translation_.x - pos.x;
//	int DistanceY = worldTransformA.translation_.y - pos.y;
//	int DistanceZ = worldTransformA.translation_.z - pos.z;
//
//	DistanceX = Abs(DistanceX);
//	DistanceY = Abs(DistanceY);
//	DistanceZ = Abs(DistanceZ);
//
//	if (DistanceX <= worldTransformA.scale_.x + scale.x &&
//		DistanceY <= worldTransformA.scale_.y + scale.y &&
//		DistanceZ <= worldTransformA.scale_.z + scale.z)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool LineFloarCol(Vector3 senbunPos1, Vector3 senbunPos2, Vector3 heimenPos, Vector3 normalVec)
//{
//	//�W�����v�̕����x�N�g��
//	//Vector3 v = line.upVec;
//	Vector3 p1 = senbunPos1;
//
//	//������̓_
//	//Vector3 p1 = line.GetWorldTrans().translation_;
//	Vector3 p2 = senbunPos2;
//
//	//���ʏ�̓_
//	Vector3 p0 = heimenPos;
//
//	//���ʂ̖@���x�N�g��
//	Vector3 n = normalVec;
//
//	Vector3 v1 = p0 - p1;
//	Vector3 v2 = p0 - p2;
//
//	if ((v1.dot(n)) * (v2.dot(n)) <= 0)
//	{
//		return true;
//	}
//	return false;
//}
//
//bool SphereCol(WorldTransform worldTransformA, WorldTransform worldTransformB)
//{
//	Vector3 posA = worldTransformA.translation_;
//	Vector3 posB = worldTransformB.translation_;
//
//	//�X�P�[����X�������Ƃ��Ĉ����Ă���
//	//���������Ɣ��a���������������
//	float rA = worldTransformA.scale_.x;
//	float rB = worldTransformB.scale_.x;
//
//	if ((posB.x - posA.x) * (posB.x - posA.x) +
//		(posB.y - posA.y) * (posB.y - posA.y) +
//		(posB.z - posA.z) * (posB.z - posA.z) <=
//		(rA + rB) * (rA + rB))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool SphereCol(Vector3 posA, Vector3 posB, float rA, float rB)
//{
//	if ((posB.x - posA.x) * (posB.x - posA.x) +
//		(posB.y - posA.y) * (posB.y - posA.y) +
//		(posB.z - posA.z) * (posB.z - posA.z) <=
//		(rA + rB) * (rA + rB))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool BoxCollsion(Vector2 posA, Vector2 posB, Vector2 rA, Vector2 rB)
//{
//	int DistanceX = posA.x - posB.x;
//	int DistanceY = posA.y - posB.y;
//
//	DistanceX = Abs(DistanceX);
//	DistanceY = Abs(DistanceY);
//
//	if (DistanceX <= rA.x + rB.x and DistanceY <= rA.y + rB.y)
//	{
//		return true;
//	}
//	return false;
//}