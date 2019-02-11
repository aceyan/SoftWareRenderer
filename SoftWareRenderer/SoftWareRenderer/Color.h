#pragma once
struct  Color
{
public:
	Color(){ _r = _b = _g = 0; };
	Color(byte r, byte g, byte b) :_r(r), _g(g), _b(b){};
	friend Color operator * (Color a, Color b)
	{//ÑÕÉ«µ÷ºÍ
		byte R = (a.GetR() / 255) * (b.GetR() / 255) * 255;
		byte G = (a.GetG() / 255) * (b.GetG() / 255) * 255;
		byte B = (a.GetB() / 255) * (b.GetB() / 255) * 255;
		return Color(R, G, B);
	};
	friend Color operator * (float a, Color b)
	{
		float R = a * b.GetR();
		float G = a * b.GetG();
		float B = a * b.GetB();
		return Color(Color::LimitRange(R), Color::LimitRange(G), Color::LimitRange(B));
	};
	friend Color operator * (Color a, float b)
	{
		float R = b * a.GetR();
		float G = b * a.GetG();
		float B = b * a.GetB();
		return Color(Color::LimitRange(R), Color::LimitRange(G), Color::LimitRange(B));
	};
	friend Color operator + (Color a, Color b)
	{
		int R = a.GetR() + b.GetR();
		int G = a.GetG() + b.GetG();
		int B = a.GetB() + b.GetB();
		return Color(Color::LimitRange(R), Color::LimitRange(G), Color::LimitRange(B));
	};

	float GetR(){ return _r; };
	float GetB(){ return _b; };
	float GetG(){ return _g; };

	void SetR(byte r){ _r = Color::LimitRange(r); };
	void SetB(byte b){ _b = Color::LimitRange(b); };
	void SetG(byte g){ _g = Color::LimitRange(g); };

	static byte LimitRange(int v)
	{
		if (v <= 0)
		{
			return 0;
		}
		if (v >= 255)
		{
			return 255;
		}
		return v;
	};

	static byte LimitRange(float v)
	{
		if (v <= 0)
		{
			return 0;
		}
		if (v >= 255)
		{
			return 255;
		}
		return v;
	}

private:
	 byte _r;
	 byte _b;
	 byte _g;
};