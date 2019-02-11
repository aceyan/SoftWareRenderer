#pragma once
#include"Vector3D.h"
#include"Color.h"
struct Vertex
{
	/// <summary>
	/// ����λ��
	/// </summary>
	Vector3D point;
	/// <summary>
	/// ��������
	/// </summary>
	float u;
	float v;
	/// <summary>
	/// ����ɫ
	/// </summary>
	Color vcolor;
	/// <summary>
	/// ����
	/// </summary>
	Vector3D normal;

	//----------------------------------------------
	//
	//----------------------------------------------

	/// <summary>
	/// ������ɫ
	/// </summary>
	Color lightingColor;

	/// <summary>
	/// 1/z�����ڶ�����Ϣ��͸��У��
	/// </summary>
	float onePerZ;

	Vertex()
	{
		point = Vector3D();
		u = v = 0;
		vcolor = Color();
		normal = Vector3D(1,1,1);
		lightingColor = Color(1,1,1);
	}

	Vertex(Vector3D p, Vector3D n, float u, float v, byte r, byte g, byte b) :point(p), normal(n), u(u), v(v)
	{

		point.w = 1;
		vcolor.SetR(r);
		vcolor.SetG(g);
		vcolor.SetB(b);
		onePerZ = 1;

		lightingColor.SetR(1);
		lightingColor.SetB(1);
		lightingColor.SetG(1);
	};

	//Vertex(Vertex &vertex)
	//{
	//	point = vertex.point;
	//	normal = vertex.normal;
	//	vcolor = vertex.vcolor;
	//	onePerZ = vertex.onePerZ;
	//	u = vertex.u;
	//	v = vertex.v;
	//	lightingColor = vertex.lightingColor;
	//};
};