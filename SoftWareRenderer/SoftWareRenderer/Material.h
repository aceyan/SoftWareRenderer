#pragma once
#include"Color.h"
struct Material
{
	Color emissive;//�Է�����ɫֵ
    float ka;//�����ⷴ��ϵ��
	 Color diffuse;//��������ɫֵ
	 Color specular;//���淴����ɫֵ
	 float shininess;//�����
	 Material(Color emissive, float ka, Color diffuse, Color specular, float shininess) :emissive(emissive), ka(ka), diffuse(diffuse), specular(specular), shininess(shininess)
	{
	 };
};