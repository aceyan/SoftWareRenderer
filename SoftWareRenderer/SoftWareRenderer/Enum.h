#pragma once
enum RenderMode
{
	/// <summary>
	/// 线框模式
	/// </summary>
	Wireframe,
	/// <summary>
	/// 纹理
	/// </summary>
	Textured,
	/// <summary>
	/// 顶点色
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
	/// 点采样
	/// </summary>
	point,
	/// <summary>
	/// 双线性采样
	/// </summary>
	Bilinear
};