#pragma once
#include"Vector3D.h"
struct Camera
{
public:
	Vector3D pos;
	Vector3D lookAt;
	Vector3D up;
	/// <summary>
	/// 观察角，弧度
	/// </summary>
	float fov;
	/// <summary>
	/// 长宽比
	/// </summary>
	float aspect;
	/// <summary>
	/// 近裁平面
	/// </summary>
	float zn;
	/// <summary>
	/// 远裁平面
	/// </summary>
	float zf;
	Camera(){};
	Camera(Vector3D pos, Vector3D lookAt, Vector3D up, float fov, float aspect, float zn, float zf) :pos(pos), lookAt(lookAt), up(up), fov(fov), aspect(aspect), zn(zn), zf(zf)
	{
	};
};