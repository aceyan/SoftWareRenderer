#pragma once
#include<Windows.h>
//定义4x4矩阵
struct Matrix4x4
{
public:
	Matrix4x4(){ ZeroMemory(&m, sizeof(m)); };
	Matrix4x4(float a1, float a2, float a3, float a4,
		float b1, float b2, float b3, float b4,
		float c1, float c2, float c3, float c4,
		float d1, float d2, float d3, float d4);
	friend Matrix4x4 operator*(Matrix4x4 lhs, Matrix4x4 rhs);

	void Identity();//单位化矩阵
	void SetZero();//设置为零矩阵
	void Transpose();//转置
	float Determinate();//求行列式
	Matrix4x4 GetAdjoint();//获得伴随矩阵
	Matrix4x4 Inverse();//获得逆矩阵
	//
	float m[4][4];
private:
	float Determinate(float mat[4][4], int n);//递归算法求矩阵行列式


};

