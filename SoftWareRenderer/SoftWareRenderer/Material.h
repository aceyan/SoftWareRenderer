#pragma once
#include"Color.h"
struct Material
{
	/// <summary>
	/// 自发光颜色值
	/// </summary>
	Color emissive;
	/// <summary>
	/// 环境光反射系数
	/// </summary>
   float ka;
	/// <summary>
	/// 漫反射颜色值
	/// </summary>
	 Color diffuse;
	/// <summary>
	/// 镜面反射颜色值
	/// </summary>
	 Color specular;
	/// <summary>
	/// 光泽度
	/// </summary>
	 float shininess;

	 Material(Color emissive, float ka, Color diffuse, Color specular, float shininess) :emissive(emissive), ka(ka), diffuse(diffuse), specular(specular), shininess(shininess)
	{
	 };
};