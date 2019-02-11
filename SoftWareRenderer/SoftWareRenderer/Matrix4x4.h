#pragma once
#include<Windows.h>
//����4x4����
struct Matrix4x4
{
public:
	Matrix4x4(){ ZeroMemory(&m, sizeof(m)); };
	Matrix4x4(float a1, float a2, float a3, float a4,
		float b1, float b2, float b3, float b4,
		float c1, float c2, float c3, float c4,
		float d1, float d2, float d3, float d4);
	friend Matrix4x4 operator*(Matrix4x4 lhs, Matrix4x4 rhs);

	void Identity();//��λ������
	void SetZero();//����Ϊ�����
	void Transpose();//ת��
	float Determinate();//������ʽ
	Matrix4x4 GetAdjoint();//��ð������
	Matrix4x4 Inverse();//��������
	//
	float m[4][4];
private:
	float Determinate(float mat[4][4], int n);//�ݹ��㷨���������ʽ


};

