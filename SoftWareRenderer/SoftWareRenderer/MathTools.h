#pragma once
#include"Matrix4x4.h"
#include"Point2D.h"
#include"Vector3D.h"
#include"Color.h"
#include"Vertex.h"
static class MathTools
{
public:
	static Matrix4x4 GetTranslate(float x, float y, float z);
	static Matrix4x4 GetScale(float x, float y, float z);
	static Matrix4x4 GetRotateY(float r);
	static Matrix4x4 GetRotateX(float r);
	static Matrix4x4 GetRotateZ(float r);
	static Matrix4x4 GetView(Vector3D pos, Vector3D lookAt, Vector3D up);
	static Matrix4x4 GetProjection(float fov, float aspect, float zn, float zf);
	static float Lerp(float a, float b, float t);
	static Color Lerp(Color a, Color b, float t);
	static void ScreenSpaceLerpVertex(Vertex &v, Vertex v1, Vertex v2, float t);
	static int Range(int v, int min, int max);
	static float Range(float v, float min, float max);

};
