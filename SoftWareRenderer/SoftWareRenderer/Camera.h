#pragma once
#include"Vector3D.h"
struct Camera
{
public:
	Vector3D pos;
	Vector3D lookAt;
	Vector3D up;
	/// <summary>
	/// �۲�ǣ�����
	/// </summary>
	float fov;
	/// <summary>
	/// �����
	/// </summary>
	float aspect;
	/// <summary>
	/// ����ƽ��
	/// </summary>
	float zn;
	/// <summary>
	/// Զ��ƽ��
	/// </summary>
	float zf;
	Camera(){};
	Camera(Vector3D pos, Vector3D lookAt, Vector3D up, float fov, float aspect, float zn, float zf) :pos(pos), lookAt(lookAt), up(up), fov(fov), aspect(aspect), zn(zn), zf(zf)
	{
	};
};