#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Light
{
	
	Vector3D worldPosition;//�ƹ���������
	Color lightColor;//�ƹ���ɫ
	Light(){};
	Light(Vector3D wp, Color lc)
	{
		 worldPosition = wp;
		 lightColor = lc;
	}
};