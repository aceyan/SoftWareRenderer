#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Light
{
	/// <summary>
	/// �ƹ�ʱ������
	/// </summary>
	Vector3D worldPosition;
	/// <summary>
	/// �ƹ���ɫ
	/// </summary>
	Color lightColor;
	Light(){};
	Light(Vector3D wp, Color lc)
	{
		 worldPosition = wp;
		 lightColor = lc;
	}
};