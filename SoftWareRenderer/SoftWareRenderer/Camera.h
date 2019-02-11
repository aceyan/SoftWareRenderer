#pragma once
#include"Vector3D.h"
struct Camera
{
public:
	Vector3D pos;//摄像机位置
	Vector3D lookAt;//摄像机方向
	Vector3D up;//上方向
	float fov; //观察角，弧度
	float aspect;//长宽比
	float zn;//近裁平面
	float zf;//远裁平面
	Camera(){};
	Camera(Vector3D pos, Vector3D lookAt, Vector3D up, float fov, float aspect, float zn, float zf) :pos(pos), lookAt(lookAt), up(up), fov(fov), aspect(aspect), zn(zn), zf(zf)
	{
	};
};