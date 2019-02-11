#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Light
{
	/// <summary>
	/// 灯光时间坐标
	/// </summary>
	Vector3D worldPosition;
	/// <summary>
	/// 灯光颜色
	/// </summary>
	Color lightColor;
	Light(){};
	Light(Vector3D wp, Color lc)
	{
		 worldPosition = wp;
		 lightColor = lc;
	}
};