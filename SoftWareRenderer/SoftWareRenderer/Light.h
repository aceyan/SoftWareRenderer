#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Light
{
	
	Vector3D worldPosition;//灯光世界坐标
	Color lightColor;//灯光颜色
	Light(){};
	Light(Vector3D wp, Color lc)
	{
		 worldPosition = wp;
		 lightColor = lc;
	}
};