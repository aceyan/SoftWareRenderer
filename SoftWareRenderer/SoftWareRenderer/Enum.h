#pragma once
enum RenderMode
{
	/// <summary>
	/// �߿�ģʽ
	/// </summary>
	Wireframe,
	/// <summary>
	/// ����
	/// </summary>
	Textured,
	/// <summary>
	/// ����ɫ
	/// </summary>
	VertexColor
};

enum LightMode
{
	On,
	Off
};

enum TextureFilterMode
{
	/// <summary>
	/// �����
	/// </summary>
	point,
	/// <summary>
	/// ˫���Բ���
	/// </summary>
	Bilinear
};