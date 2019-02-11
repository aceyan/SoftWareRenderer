#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Vertex
{
	Vector3D point;//顶点位置
	float u;//纹理坐标
	float v;//纹理坐标
	Color vcolor; //顶点色
	Vector3D normal;//法线
	Color lightingColor;//光照颜色
	//
	float onePerZ;//1/z，用于顶点信息的透视校正

	Vertex()
	{
		point = Vector3D();
		u = v = 0;
		onePerZ = 1;
		vcolor = Color();
		normal = Vector3D(1,1,1);
		lightingColor = Color(0, 0, 0);
	}

	Vertex(Vector3D p, Vector3D n, float u, float v, byte r, byte g, byte b) :point(p), normal(n), u(u), v(v)
	{

		point.w = 1;
		vcolor.SetR(r);
		vcolor.SetG(g);
		vcolor.SetB(b);
		onePerZ = 1;

		lightingColor.SetR(0);
		lightingColor.SetB(0);
		lightingColor.SetG(0);
	};
};