#pragma once
#include"Vertex.h"
#include"Material.h"
#include"Point2D.h"
#include"Vector3D.h"
#include<vector>
using namespace std;
struct CubeMeshData
{
public:

	 CubeMeshData()
	 {
		 //顶点坐标
		 Vector3D pointList[8] = {
			 Vector3D(-1, 1, -1),
			 Vector3D(-1, -1, -1),
			 Vector3D(1, -1, -1),
			 Vector3D(1, 1, -1),

			 Vector3D(-1, 1, 1),
			 Vector3D(-1, -1, 1),
			 Vector3D(1, -1, 1),
			 Vector3D(1, 1, 1)
		 };
		 //三角形顶点索引 12个面
		 int indexs[36] = { 0, 1, 2,
			 0, 2, 3,
			 //
			 7, 6, 5,
			 7, 5, 4,
			 //
			 0, 4, 5,
			 0, 5, 1,
			 //
			 1, 5, 6,
			 1, 6, 2,
			 //
			 2, 6, 7,
			 2, 7, 3,
			 //
			 3, 7, 4,
			 3, 4, 0
		 };

		 //uv坐标
		 Point2D uvs[36] = {
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0),
			 //
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0),
			 //
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0),
			 //
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0),
			 //
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0),
			 ///
			 Point2D(0, 0), Point2D(0, 1), Point2D(1, 1),
			 Point2D(0, 0), Point2D(1, 1), Point2D(1, 0)
		 };
		 //顶点色
		 Vector3D vertColors[36] = {
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255),
			 //
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255),
			 //
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255),
			 //
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255),
			 //
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255),
			 //
			 Vector3D(0, 255, 0), Vector3D(0, 0, 255), Vector3D(255, 0, 0),
			 Vector3D(0, 255, 0), Vector3D(255, 0, 0), Vector3D(0, 0, 255)
		 };
		 //法线
		 Vector3D normals[36] = {
			 Vector3D(0, 0, -1), Vector3D(0, 0, -1), Vector3D(0, 0, -1),
			 Vector3D(0, 0, -1), Vector3D(0, 0, -1), Vector3D(0, 0, -1),
			 //
			 Vector3D(0, 0, 1), Vector3D(0, 0, 1), Vector3D(0, 0, 1),
			 Vector3D(0, 0, 1), Vector3D(0, 0, 1), Vector3D(0, 0, 1),
			 //
			 Vector3D(-1, 0, 0), Vector3D(-1, 0, 0), Vector3D(-1, 0, 0),
			 Vector3D(-1, 0, 0), Vector3D(-1, 0, 0), Vector3D(-1, 0, 0),
			 //
			 Vector3D(0, -1, 0), Vector3D(0, -1, 0), Vector3D(0, -1, 0),
			 Vector3D(0, -1, 0), Vector3D(0, -1, 0), Vector3D(0, -1, 0),
			 //
			 Vector3D(1, 0, 0), Vector3D(1, 0, 0), Vector3D(1, 0, 0),
			 Vector3D(1, 0, 0), Vector3D(1, 0, 0), Vector3D(1, 0, 0),
			 //
			 Vector3D(0, 1, 0), Vector3D(0, 1, 0), Vector3D(0, 1, 0),
			 Vector3D(0, 1, 0), Vector3D(0, 1, 0), Vector3D(0, 1, 0)
		 };




		 //生成顶点列表
		 for (int i = 0; i < 36; i++)
		 {
			 int pointIndex = indexs[i];
			 Vector3D point = pointList[pointIndex];
			 verts.push_back(Vertex(point, normals[i], uvs[i].x, uvs[i].y, vertColors[i].x, vertColors[i].y, vertColors[i].z));
		 }
	 };

	 vector<Vertex> verts;
	 Material material = Material(Color(10, 10, 10), 0.1f, Color(150, 150, 150), Color(255, 255, 255), 20);

	
};