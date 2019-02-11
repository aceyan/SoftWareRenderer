#pragma once
#include"Vector3D.h"
struct Camera
{
public:
	Vector3D pos;//�����λ��
	Vector3D lookAt;//���������
	Vector3D up;//�Ϸ���
	float fov; //�۲�ǣ�����
	float aspect;//�����
	float zn;//����ƽ��
	float zf;//Զ��ƽ��
	Camera(){};
	Camera(Vector3D pos, Vector3D lookAt, Vector3D up, float fov, float aspect, float zn, float zf) :pos(pos), lookAt(lookAt), up(up), fov(fov), aspect(aspect), zn(zn), zf(zf)
	{
	};
};