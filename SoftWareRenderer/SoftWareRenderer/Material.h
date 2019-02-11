#pragma once
#include"Color.h"
struct Material
{
	/// <summary>
	/// �Է�����ɫֵ
	/// </summary>
	Color emissive;
	/// <summary>
	/// �����ⷴ��ϵ��
	/// </summary>
   float ka;
	/// <summary>
	/// ��������ɫֵ
	/// </summary>
	 Color diffuse;
	/// <summary>
	/// ���淴����ɫֵ
	/// </summary>
	 Color specular;
	/// <summary>
	/// �����
	/// </summary>
	 float shininess;

	 Material(Color emissive, float ka, Color diffuse, Color specular, float shininess) :emissive(emissive), ka(ka), diffuse(diffuse), specular(specular), shininess(shininess)
	{
	 };
};