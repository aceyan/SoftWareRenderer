
#include<Windows.h>
#include"Matrix4x4.h"
#include"Vector3D.h"
#include"CubeMeshData.h"
#include"MathTools.h"
#include"Light.h"
#include"Camera.h"
#include"Enum.h"

#include<gdiplus.h>
#pragma comment(lib, "gdiplus.lib")  

#define WINDOW_TITLE   L"MyRaster"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define PI 3.1415926
//绘制所需要的系统组件
static HDC screen_hdc;
static HDC hCompatibleDC; 
static HBITMAP hCompatibleBitmap;
static HBITMAP hOldBitmap;	  
static BITMAPINFO binfo;

Gdiplus::Bitmap* texture;//贴图纹理
int textureWidth;
int textureHeight;

float zBuff[SCREEN_HEIGHT][SCREEN_WIDTH];//保存像素的z信息，用于深度测试
CubeMeshData mesh;//cube的数据
Light light;
Camera camera;
Color ambient;//全局环境光颜色 
float rot = 0;//cube旋转弧度
float rotationSpeed = 0.03;//cube旋转速度
//
RenderMode currentMode;//渲染模式
LightMode lightMode;//光照模式
TextureFilterMode textureFilterMode;//纹理采样模式
BYTE *textureBuffer;//保存纹理rgb数据
BYTE *backBuffer;  //每三个byte为一个像素


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void Init(HWND hwnd);//初始化组件
void LoadTexture(wstring TexureFilename);//从文件中加载texture

void SetMVTransform(Matrix4x4 m, Matrix4x4 v, Vertex &vertex);//从模型空间转换到view space
void SetProjectionTransform(Matrix4x4 p, Vertex &vertex);//进行投影变换
bool Clip(Vertex v);//裁剪
void TransformToScreen(Vertex &v);//转换到屏幕空间
bool BackFaceCulling(Vertex p1, Vertex p2, Vertex p3);//背面消隐
void Draw(Matrix4x4 m, Matrix4x4 v, Matrix4x4 p);//绘制场景到backbuff
void DrawTriangle(Vertex p1, Vertex p2, Vertex p3, Matrix4x4 m, Matrix4x4 v, Matrix4x4 p);//绘制三角形
void TriangleRasterization(Vertex p1, Vertex p2, Vertex p3);//光栅化三角形
void DrawTriangleTop(Vertex p1, Vertex p2, Vertex p3);//绘制平顶三角形
void DrawTriangleBottom(Vertex p1, Vertex p2, Vertex p3);//绘制平底三角形
void ScanlineFill(Vertex left, Vertex right, int yIndex);//扫描线填充算法
Gdiplus::Color TransFormToGdiColor(Color color);//将我们自定义的color转换成GDI绘制使用的color
void BresenhamDrawLine(Vertex p1, Vertex p2);//使用breasenham算法画线
void Lighting(Matrix4x4 m, Vector3D worldEyePositon, Vertex &v);//顶点光照处理
Color ReadTexture(int uIndex, int vIndex, Gdiplus::Color *color);//读取纹理颜色
void ClearBackBuffer(byte r, byte g, byte b);//清理backbuff
void SetBackBuff(int uIndex, int vIndex, Gdiplus::Color color);//设置backbuff颜色


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{

	WNDCLASSEX wndclass = { 0 };
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = L"SoftWareRenderer";
	if (!RegisterClassEx(&wndclass))
		return -1;
	HWND hwnd;

	hwnd = CreateWindow(L"SoftWareRenderer", WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	Init(hwnd);

	MoveWindow(hwnd, 250, 80, SCREEN_WIDTH, SCREEN_HEIGHT, true);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);



	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			//清理zbuff和backbuff
			ZeroMemory(&zBuff, sizeof(zBuff));
			ClearBackBuffer(100, 100, 100);

			//生成m，v，p矩阵
			rot += rotationSpeed;
			Matrix4x4 m = MathTools::GetRotateX(rot) * MathTools::GetRotateY(rot) * MathTools::GetTranslate(0, 0, 10);
			Matrix4x4 v = MathTools::GetView(camera.pos, camera.lookAt, camera.up);
			Matrix4x4 p = MathTools::GetProjection(camera.fov, camera.aspect, camera.zn, camera.zf);
			//
			Draw(m, v, p);//使用m，v，p矩阵，将cube绘制到backbuff
			//
			SetDIBits(screen_hdc, hCompatibleBitmap, 0, SCREEN_HEIGHT, backBuffer, (BITMAPINFO*)&binfo, DIB_RGB_COLORS);
			BitBlt(screen_hdc, -1, -1, SCREEN_WIDTH, SCREEN_HEIGHT, hCompatibleDC, 0, 0, SRCCOPY);
		}
	}
	UnregisterClass(L"SoftWareRenderer", wndclass.hInstance);
	return 0;
}

//清除背后缓存为某一种颜色
void ClearBackBuffer(byte r, byte g, byte b)
{
	for (int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; ++i)
	{

		backBuffer[i * 3 + 0] = r;
		backBuffer[i * 3 + 1] = g;
		backBuffer[i * 3 + 2] = b;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:

		ValidateRect(hwnd, NULL);
		break;

	case WM_KEYDOWN:
		if (unsigned int(wParam) == 'Q')
		{
			if (currentMode == RenderMode::Textured)
			{
				currentMode = RenderMode::VertexColor;
			}
			else if (currentMode == RenderMode::VertexColor)
			{
				currentMode = RenderMode::Wireframe;
			}
			else
			{
				currentMode = RenderMode::Textured;
			}
		}

		if (unsigned int(wParam) == 'W')
		{
			if (lightMode == LightMode::On)
			{
				lightMode = LightMode::Off;
			}
			else
			{
				lightMode = LightMode::On;
			}
		}

		if (unsigned int(wParam) == 'E')
		{
			if (textureFilterMode == TextureFilterMode::Bilinear)
			{
				textureFilterMode = TextureFilterMode::point;
			}
			else
			{
				textureFilterMode = TextureFilterMode::Bilinear;
			}
		}


		if (wParam == VK_UP)
		{
			rotationSpeed += 0.005;
		}
		else if (wParam == VK_DOWN)
		{
			rotationSpeed -= 0.005;
			if (rotationSpeed < 0)
			{
				rotationSpeed = 0;
			}
		}

		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	

	case WM_KEYUP:
		
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

void Init(HWND hwnd)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), 0);

	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = 24;      //设置像素为24位
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -SCREEN_HEIGHT;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = SCREEN_WIDTH;

	//获取屏幕HDC
	screen_hdc = GetDC(hwnd);

	hCompatibleDC = CreateCompatibleDC(screen_hdc);
	hCompatibleBitmap = CreateCompatibleBitmap(screen_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	hOldBitmap = (HBITMAP)SelectObject(hCompatibleDC, hCompatibleBitmap);

	//从Texture文件夹加载纹理数据
	LoadTexture(wstring(L"Texture/MyTexture.jpg"));
	backBuffer = new byte[SCREEN_WIDTH*SCREEN_HEIGHT* 24 / 8];

	currentMode = RenderMode::Textured;
	lightMode = LightMode::On;
	textureFilterMode = TextureFilterMode::Bilinear;
	//定义环境光
	ambient = Color(255, 255, 255);
	//定义光照
	light = Light(Vector3D(0, 0, 0), Color(255, 255, 255));
	//定义相机
	camera = Camera(Vector3D(0, 0, 0, 1), Vector3D(0, 0, 1, 1), Vector3D(0, 1, 0, 0), (float)PI / 4, SCREEN_WIDTH / SCREEN_HEIGHT, 1, 500);

	
}

void LoadTexture(wstring TexureFilename)
{
	Gdiplus::GdiplusStartupInput gdiplusstartupinput;
	Gdiplus::Color color;
	ULONG_PTR gdiplustoken;

	Gdiplus::GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

	//读取纹理
	texture = new Gdiplus::Bitmap(TexureFilename.c_str());
	//texture->GetPixel(1,1,&color);
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
	

	//创建纹理缓存,screen_h*screen_w * 3个字节大
	textureBuffer = new BYTE[textureWidth*textureHeight * 3];

	for (int i = 0; i < textureHeight; ++i)
	{
		for (int j = 0; j <textureWidth; ++j)
		{
			texture->GetPixel(j, i, &color);
			//将像素的颜色写入纹理缓存,注意颜色的顺序应该是rgb
			textureBuffer[i * textureWidth * 3 + (j + 1) * 3 - 1] = color.GetR();
			textureBuffer[i * textureWidth * 3 + (j + 1) * 3 - 2] = color.GetG();
			textureBuffer[i * textureWidth * 3 + (j + 1) * 3 - 3] = color.GetB();
		}
	}

	Gdiplus::GdiplusShutdown(gdiplustoken);

}



void SetMVTransform(Matrix4x4 m, Matrix4x4 v, Vertex &vertex)
{
	vertex.point = vertex.point * m * v;
}


void SetProjectionTransform(Matrix4x4 p, Vertex &vertex)
{
	vertex.point = vertex.point * p;
	//得到齐次裁剪空间的点 v.point.w 中保存着原来的z(具体是z还是-z要看使用的投影矩阵,我们使用投影矩阵是让w中保存着z)


	//onePerZ 保存1/z，方便之后对1/z关于x’、y’插值得到1/z’ 
	vertex.onePerZ = 1 / vertex.point.w;
	//校正的推论： s/z、t/z和x’、y’也是线性关系。而我们之前知道1/z和x’、y’是线性关系。则我们得出新的思路：对1/z关于x’、y’插值得到1/z’，然后对s/z、t/z关于x’、y’进行插值得到s’/z’、t’/z’，然后用s’/z’和t’/z’分别除以1/z’，就得到了插值s’和t’
	//这里将需要插值的信息都乘以1/z 得到 s/z和t/z等，方便光栅化阶段进行插值
	vertex.u *= vertex.onePerZ;
	vertex.v *= vertex.onePerZ;
	//
	vertex.vcolor = vertex.vcolor * vertex.onePerZ;
	//
	vertex.lightingColor = vertex.lightingColor * vertex.onePerZ;
}

bool Clip(Vertex v)
{
	//cvv为 x-1,1  y-1,1  z0,1
	if (v.point.x >= -v.point.w && v.point.x <= v.point.w &&
		v.point.y >= -v.point.w && v.point.y <= v.point.w &&
		v.point.z >= 0 && v.point.z <= v.point.w)
	{
		return true;
	}
	return false;
}
void TransformToScreen(Vertex &v)
{
	if (v.point.w != 0)
	{
		//先进行透视除法，转到cvv
		v.point.x *= 1 / v.point.w;
		v.point.y *= 1 / v.point.w;
		v.point.z *= 1 / v.point.w;
		v.point.w = 1;
		//cvv到屏幕坐标
		v.point.x = (v.point.x + 1) * 0.5f * SCREEN_WIDTH;
		v.point.y = (1 - v.point.y) * 0.5f * SCREEN_HEIGHT;
	}
}
bool BackFaceCulling(Vertex p1, Vertex p2, Vertex p3)
{
	if (currentMode == RenderMode::Wireframe)
	{//线框模式不进行背面消隐
		return true;
	}
	else
	{
		Vector3D v1 = p2.point - p1.point;
		Vector3D v2 = p3.point - p2.point;
		Vector3D normal = Vector3D::Cross(v1, v2);
		//由于在视空间中，所以相机点就是（0,0,0）
		Vector3D viewDir = p1.point -  Vector3D(0, 0, 0);
		if (Vector3D::Dot(normal, viewDir) > 0)
		{
			return true;
		}
		return false;
	}
}
void Draw(Matrix4x4 m, Matrix4x4 v, Matrix4x4 p)
{
	for (int i = 0; i + 2 < mesh.verts.size(); i += 3)
	{
		DrawTriangle(mesh.verts[i], mesh.verts[i + 1], mesh.verts[i + 2], m, v, p);
	}
}
void DrawTriangle(Vertex p1, Vertex p2, Vertex p3, Matrix4x4 m, Matrix4x4 v, Matrix4x4 p)
{
	//--------------------几何阶段---------------------------
	if (lightMode == LightMode::On)
	{//进行顶点光照
		Lighting(m, camera.pos,  p1);
		Lighting(m, camera.pos,  p2);
		Lighting(m, camera.pos,  p3);
	}

	//变换到相机空间
	SetMVTransform(m, v,  p1);
	SetMVTransform(m, v,  p2);
	SetMVTransform(m, v,  p3);

	//在相机空间进行背面消隐
	if (BackFaceCulling(p1, p2, p3) == false)
	{
		return;
	}

	//变换到齐次剪裁空间
	SetProjectionTransform(p,  p1);
	SetProjectionTransform(p,  p2);
	SetProjectionTransform(p,  p3);

	//裁剪
	if (Clip(p1) == false || Clip(p2) == false || Clip(p3) == false)
	{
		return;
	}

	//变换到屏幕坐标
	TransformToScreen( p1);
	TransformToScreen( p2);
	TransformToScreen( p3);

	//--------------------光栅化阶段---------------------------

	if (currentMode == RenderMode::Wireframe)
	{//线框模式
		BresenhamDrawLine(p1, p2);
		BresenhamDrawLine(p2, p3);
		BresenhamDrawLine(p3, p1);
	}
	else
	{
		TriangleRasterization(p1, p2, p3);
	}
}
void TriangleRasterization(Vertex p1, Vertex p2, Vertex p3)
{
	if (p1.point.y == p2.point.y)
	{
		if (p1.point.y < p3.point.y)
		{//平顶
			DrawTriangleTop(p1, p2, p3);
		}
		else
		{//平底
			DrawTriangleBottom(p3, p1, p2);
		}
	}
	else if (p1.point.y == p3.point.y)
	{
		if (p1.point.y < p2.point.y)
		{//平顶
			DrawTriangleTop(p1, p3, p2);
		}
		else
		{//平底
			DrawTriangleBottom(p2, p1, p3);
		}
	}
	else if (p2.point.y == p3.point.y)
	{
		if (p2.point.y < p1.point.y)
		{//平顶
			DrawTriangleTop(p2, p3, p1);
		}
		else
		{//平底
			DrawTriangleBottom(p1, p2, p3);
		}
	}
	else
	{//分割三角形
		Vertex top;

		Vertex bottom;
		Vertex middle;
		if (p1.point.y > p2.point.y && p2.point.y > p3.point.y)
		{
			top = p3;
			middle = p2;
			bottom = p1;
		}
		else if (p3.point.y > p2.point.y && p2.point.y > p1.point.y)
		{
			top = p1;
			middle = p2;
			bottom = p3;
		}
		else if (p2.point.y > p1.point.y && p1.point.y > p3.point.y)
		{
			top = p3;
			middle = p1;
			bottom = p2;
		}
		else if (p3.point.y > p1.point.y && p1.point.y > p2.point.y)
		{
			top = p2;
			middle = p1;
			bottom = p3;
		}
		else if (p1.point.y > p3.point.y && p3.point.y > p2.point.y)
		{
			top = p2;
			middle = p3;
			bottom = p1;
		}
		else if (p2.point.y > p3.point.y && p3.point.y > p1.point.y)
		{
			top = p1;
			middle = p3;
			bottom = p2;
		}
		else
		{
			//三点共线
			return;
		}
		//插值求中间点x
		float middlex = (middle.point.y - top.point.y) * (bottom.point.x - top.point.x) / (bottom.point.y - top.point.y) + top.point.x;
		float dy = middle.point.y - top.point.y;
		float t = dy / (bottom.point.y - top.point.y);
		//插值生成左右顶点
		Vertex newMiddle;
		newMiddle.point.x = middlex;
		newMiddle.point.y = middle.point.y;
		MathTools::ScreenSpaceLerpVertex(newMiddle, top, bottom, t);

		//平底
		DrawTriangleBottom(top, newMiddle, middle);
		//平顶
		DrawTriangleTop(newMiddle, middle, bottom);
	}
}
void DrawTriangleTop(Vertex p1, Vertex p2, Vertex p3)
{
	for (float y = p1.point.y; y <= p3.point.y; y += 0.5)
	{
		int yIndex = (int)(round(y));
		if (yIndex >= 0 && yIndex < SCREEN_HEIGHT)
		{
			float xl = (y - p1.point.y) * (p3.point.x - p1.point.x) / (p3.point.y - p1.point.y) + p1.point.x;
			float xr = (y - p2.point.y) * (p3.point.x - p2.point.x) / (p3.point.y - p2.point.y) + p2.point.x;

			float dy = y - p1.point.y;
			float t = dy / (p3.point.y - p1.point.y);
			//插值生成左右顶点
			Vertex new1;
			new1.point.x = xl;
			new1.point.y = y;
			MathTools::ScreenSpaceLerpVertex(new1, p1, p3, t);
			//
			Vertex new2;
			new2.point.x = xr;
			new2.point.y = y;
			MathTools::ScreenSpaceLerpVertex(new2, p2, p3, t);
			//扫描线填充
			if (new1.point.x < new2.point.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
	}
}
void DrawTriangleBottom(Vertex p1, Vertex p2, Vertex p3)
{
	for (float y = p1.point.y; y <= p2.point.y; y += 0.5)
	{
		int yIndex = (int)round(y);
		if (yIndex >= 0 && yIndex < SCREEN_HEIGHT)
		{
			float xl = (y - p1.point.y) * (p2.point.x - p1.point.x) / (p2.point.y - p1.point.y) + p1.point.x;
			float xr = (y - p1.point.y) * (p3.point.x - p1.point.x) / (p3.point.y - p1.point.y) + p1.point.x;

			float dy = y - p1.point.y;
			float t = dy / (p2.point.y - p1.point.y);
			//插值生成左右顶点
			Vertex new1;
			new1.point.x = xl;
			new1.point.y = y;
			MathTools::ScreenSpaceLerpVertex(new1, p1, p2, t);
			//
			Vertex new2;
			new2.point.x = xr;
			new2.point.y = y;
			MathTools::ScreenSpaceLerpVertex(new2, p1, p3, t);
			//扫描线填充
			if (new1.point.x < new2.point.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
	}
}
void ScanlineFill(Vertex left, Vertex right, int yIndex)
{
	float dx = right.point.x - left.point.x;
	for (float x = left.point.x; x <= right.point.x; x += 0.5)
	{   
		int xIndex = (int)(x);
		if (xIndex >= 0 && xIndex < SCREEN_WIDTH)
		{
			float lerpFactor = 0;
			if (dx != 0)
			{
				lerpFactor = (x - left.point.x) / dx;
			}
			//1/z’与x’和y'是线性关系的
			float onePreZ = MathTools::Lerp(left.onePerZ, right.onePerZ, lerpFactor);
			if (onePreZ >= zBuff[yIndex][xIndex])//使用1/z进行深度测试
			{//通过测试
				
				zBuff[yIndex][xIndex] = onePreZ;

				float w = 1 / onePreZ;

				//uv 插值，求纹理颜色
				float u = MathTools::Lerp(left.u, right.u, lerpFactor) * w * (textureWidth - 1);
				float v = MathTools::Lerp(left.v, right.v, lerpFactor) * w * (textureHeight - 1);
				//纹理采样
				Color texColor;
				Gdiplus::Color textureColor;
				Color finalColor;

				if (RenderMode::Textured == currentMode)
				{
					if (textureFilterMode == TextureFilterMode::point)
					{//点采样

						int uIndex = (int)round(u + 0.5);
						int vIndex = (int)round(v + 0.5);
						uIndex = MathTools::Range(uIndex, 0, textureWidth - 1);
						vIndex = MathTools::Range(vIndex, 0, textureHeight - 1);
						//uv坐标系采用dx风格
						texColor = ReadTexture(uIndex, vIndex, &textureColor);//转到我们自定义的color进行计算

					}
					else if (textureFilterMode == TextureFilterMode::Bilinear)
					{//双线性采样
						float uIndex = (float)floor(u);
						float vIndex = (float)floor(v);
						float du = u - uIndex;
						float dv = v - vIndex;

						Color texcolor1 = ReadTexture((int)uIndex, (int)vIndex, &textureColor) * (1 - du) * (1 - dv);
						Color texcolor2 = ReadTexture((int)uIndex + 1, (int)vIndex, &textureColor) * du * (1 - dv);
						Color texcolor3 = ReadTexture((int)uIndex, (int)vIndex + 1, &textureColor) * (1 - du) * dv;
						Color texcolor4 = ReadTexture((int)uIndex + 1, (int)vIndex + 1, &textureColor) * du * dv;
						texColor = texcolor1 + texcolor2 + texcolor3 + texcolor4;
					}
					if (lightMode == LightMode::On)
					{
						//插值光照颜色
						Color lightColor = MathTools::Lerp(left.lightingColor, right.lightingColor, lerpFactor) * w;
						finalColor = texColor * lightColor;
					}
					else
					{
						finalColor = texColor;
					}
				}
				else if (RenderMode::VertexColor == currentMode)
				{
					//插值顶点颜色
					Color vertColor = MathTools::Lerp(left.vcolor, right.vcolor, lerpFactor) * w;
					if (lightMode == LightMode::On)
					{
						//插值光照颜色
						Color lightColor = MathTools::Lerp(left.lightingColor, right.lightingColor, lerpFactor) * w;
						finalColor = vertColor * lightColor;
					}
					else
					{
						finalColor = vertColor;
					}
					
				}
				
				SetBackBuff(xIndex, yIndex, TransFormToGdiColor(finalColor));
				
			}
		}
	}
}


void BresenhamDrawLine(Vertex p1, Vertex p2)
{
	int x = (int)round(p1.point.x);
	int y = (int)round(p1.point.y);
	int dx = (int)round(p2.point.x - p1.point.x);
	int dy = (int)round(p2.point.y - p1.point.y);
	int stepx = 1;
	int stepy = 1;

	if (dx >= 0)
	{
		stepx = 1;
	}
	else
	{
		stepx = -1;
		dx = abs(dx);
	}

	if (dy >= 0)
	{
		stepy = 1;
	}
	else
	{
		stepy = -1;
		dy = abs(dy);
	}

	int dx2 = 2 * dx;
	int dy2 = 2 * dy;

	if (dx > dy)
	{
		int error = dy2 - dx;
		for (int i = 0; i <= dx; i++)
		{
			SetBackBuff(x, y, Gdiplus::Color::White);
			if (error >= 0)
			{
				error -= dx2;
				y += stepy;
			}
			error += dy2;
			x += stepx;

		}
	}
	else
	{
		int error = dx2 - dy;
		for (int i = 0; i <= dy; i++)
		{
			SetBackBuff(x, y, Gdiplus::Color::White);
			if (error >= 0)
			{
				error -= dy2;
				x += stepx;
			}
			error += dx2;
			y += stepy;

		}
	}
}
void Lighting(Matrix4x4 m, Vector3D worldEyePositon, Vertex &v)
{
	Vector3D worldPoint = v.point * m;//世界空间顶点位置
	Matrix4x4 it = m.Inverse();
	it.Transpose();
	Vector3D normal = v.normal * it;//模型空间法线乘以世界矩阵的逆转置得到世界空间法线
	normal.Normalize();
	Color emissiveColor = mesh.material.emissive;//自发光
	Color ambientColor = ambient * mesh.material.ka;//环境光 

	Vector3D inLightDir = light.worldPosition - worldPoint;
	inLightDir.Normalize();
	float diffuse = Vector3D::Dot(normal, inLightDir);
	if (diffuse < 0)
	{
		v.lightingColor = emissiveColor + ambientColor;
	}
	else
	{
		Color diffuseColor = mesh.material.diffuse * diffuse * light.lightColor;//漫反射
		//
		Vector3D inViewDir = worldEyePositon - worldPoint;
		inViewDir.Normalize();
		Vector3D h = inViewDir + inLightDir;
		h.Normalize();
		float specular = 0;
		if (diffuse != 0)
		{//防止出现光源在物体背面产生高光的情况
			specular = pow(MathTools::Range(Vector3D::Dot(h, normal), (float)0, (float)1), mesh.material.shininess);
		}
		Color specularColor = mesh.material.specular * specular * light.lightColor;//镜面高光
		v.lightingColor = emissiveColor + ambientColor + diffuseColor + specularColor;
	}
		

	//
	
}
Color ReadTexture(int uIndex, int vIndex, Gdiplus::Color *color)
{
	int u = MathTools::Range(uIndex, 0, textureWidth - 1);
	int v = MathTools::Range(vIndex, 0, textureHeight- 1);

	byte r = textureBuffer[v* textureWidth * 3 + (u + 1) * 3 - 3];
	byte g = textureBuffer[v* textureWidth * 3 + (u + 1) * 3 - 2];
	byte b = textureBuffer[v * textureWidth * 3 + (u + 1) * 3 - 1];

	return Color(r , g , b );

}


Gdiplus::Color TransFormToGdiColor(Color color)
{
	float r = color.GetR();
	float g = color.GetG();
	float b = color.GetB();
	return Gdiplus::Color(r, g, b);
};

void SetBackBuff(int uIndex, int vIndex, Gdiplus::Color color)
{
	backBuffer[vIndex * SCREEN_WIDTH * 3 + (uIndex + 1) * 3 - 3] = color.GetR();
	backBuffer[vIndex *  SCREEN_WIDTH * 3 + (uIndex + 1) * 3 - 2] = color.GetG();
	backBuffer[vIndex *  SCREEN_WIDTH * 3 + (uIndex + 1) * 3 - 1] = color.GetB();
}


