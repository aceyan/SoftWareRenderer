#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Vertex
{
	Vector3D point;//����λ��
	float u;//��������
	float v;//��������
	Color vcolor; //����ɫ
	Vector3D normal;//����
	Color lightingColor;//������ɫ
	//
	float onePerZ;//1/z�����ڶ�����Ϣ��͸��У��

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