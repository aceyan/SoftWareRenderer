#pragma once
#include"Matrix4x4.h"
#include"Point2D.h"
#include"Vector3D.h"
#include"Color.h"
#include"Vertex.h"
//��Ⱦ�������õ�����ѧ����
static class MathTools
{
public:
	static Matrix4x4 GetTranslate(float x, float y, float z);//���ƽ�ƾ���
	static Matrix4x4 GetScale(float x, float y, float z);//������ž���
	static Matrix4x4 GetRotateY(float r);//���Y���ϵ���ת����
	static Matrix4x4 GetRotateX(float r);//���X���ϵ���ת����
	static Matrix4x4 GetRotateZ(float r);//���Z���ϵ���ת����
	static Matrix4x4 GetView(Vector3D pos, Vector3D lookAt, Vector3D up);//���view����
	static Matrix4x4 GetProjection(float fov, float aspect, float zn, float zf);//���ͶӰ����
	static float Lerp(float a, float b, float t);//���Բ�ֵ
	static Color Lerp(Color a, Color b, float t);//����ɫ�������Բ�ֵ
	static void ScreenSpaceLerpVertex(Vertex &v, Vertex v1, Vertex v2, float t);//����Ļ�ռ�Զ���v�������Բ�ֵ
	static int Range(int v, int min, int max);//����vֵ�ķ�Χ
	static float Range(float v, float min, float max);//����vֵ�ķ�Χ

};
