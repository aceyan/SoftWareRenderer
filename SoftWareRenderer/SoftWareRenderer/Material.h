#pragma once
#include"Color.h"
struct Material
{
	Color emissive;//自发光颜色值
    float ka;//环境光反射系数
	 Color diffuse;//漫反射颜色值
	 Color specular;//镜面反射颜色值
	 float shininess;//光泽度
	 Material(Color emissive, float ka, Color diffuse, Color specular, float shininess) :emissive(emissive), ka(ka), diffuse(diffuse), specular(specular), shininess(shininess)
	{
	 };
};