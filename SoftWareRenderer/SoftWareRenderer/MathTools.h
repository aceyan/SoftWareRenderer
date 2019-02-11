#pragma once
#include"Matrix4x4.h"
#include"Point2D.h"
#include"Vector3D.h"
#include"Color.h"
#include"Vertex.h"
//渲染过程中用到的数学工具
static class MathTools
{
public:
	static Matrix4x4 GetTranslate(float x, float y, float z);//获得平移矩阵
	static Matrix4x4 GetScale(float x, float y, float z);//获得缩放矩阵
	static Matrix4x4 GetRotateY(float r);//获得Y轴上的旋转矩阵
	static Matrix4x4 GetRotateX(float r);//获得X轴上的旋转矩阵
	static Matrix4x4 GetRotateZ(float r);//获得Z轴上的旋转矩阵
	static Matrix4x4 GetView(Vector3D pos, Vector3D lookAt, Vector3D up);//获得view矩阵
	static Matrix4x4 GetProjection(float fov, float aspect, float zn, float zf);//获得投影矩阵
	static float Lerp(float a, float b, float t);//线性插值
	static Color Lerp(Color a, Color b, float t);//对颜色进行线性插值
	static void ScreenSpaceLerpVertex(Vertex &v, Vertex v1, Vertex v2, float t);//在屏幕空间对顶点v进行线性插值
	static int Range(int v, int min, int max);//控制v值的范围
	static float Range(float v, float min, float max);//控制v值的范围

};
