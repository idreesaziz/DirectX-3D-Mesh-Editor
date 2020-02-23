#pragma once
#pragma once
#define ELOG(x) MessageBox(nullptr, x, "Error", 0);
#define OUT
#include <DirectXMath.h>

typedef unsigned int	SUINT;
typedef int				SINT;
typedef float			SFLOAT32;
typedef double			SFLOAT64;

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

struct vec4 {
	float x, y, z, w;
	vec4(float X, float Y, float Z, float W)
		:
		x(X),
		y(Y),
		z(Z),
		w(W)
	{
	}
};
struct float2
{
	float x, y;
	float2(float X, float Y)
		: x(X), y(Y)
	{
	}

	float2 operator+(float2& other)
	{
		return float2(this->x + other.x, this->y + other.y);
	}
	float2 operator-(float2& other)
	{
		return float2(this->x - other.x, this->y - other.y);
	}
	float length()
	{
		return sqrt(x * x + y * y);
	}
	float slope()
	{
		return y/x;
	}
};
struct Vertex {
	float x, y, z, NormalX, NormalY, NormalZ, u, v, w;
	Vertex() {}
	Vertex(float X, float Y, float Z, float nX, float nY, float nZ, float U, float V, float W) :
		x(X),
		y(Y),
		z(Z),
		NormalX(nX),
		NormalY(nY),
		NormalZ(nZ),
		u(U),
		v(V),
		w(W)
	{
	}
	Vertex(float X, float Y, float Z, float nX, float nY, float nZ) :
		x(X),
		y(Y),
		z(Z),
		NormalX(nX),
		NormalY(nY),
		NormalZ(nZ)
	{
	}
	Vertex(float X, float Y, float Z) :
		x(X),
		y(Y),
		z(Z)
	{
	}

	Vertex operator-(Vertex& other)
	{
		return Vertex(this->x - other.x,
			this->y - other.y,
			this->z - other.z,
			this->NormalX - other.NormalX,
			this->NormalY - other.NormalY,
			this->NormalZ - other.NormalZ);
	}
	Vertex operator+(Vertex& other)
	{
		return Vertex(this->x + other.x,
			this->y + other.y,
			this->z + other.z,
			this->NormalX + other.NormalX,
			this->NormalY + other.NormalY,
			this->NormalZ + other.NormalZ);
	}
	Vertex operator*(Vertex& other)
	{
		return Vertex(this->x * other.x,
			this->y * other.y,
			this->z * other.z,
			this->NormalX * other.NormalX,
			this->NormalY * other.NormalY,
			this->NormalZ * other.NormalZ);
	}
	bool operator==(Vertex& other)
	{
		if (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z &&
			this->NormalX == other.NormalX &&
			this->NormalY == other.NormalY &&
			this->NormalZ == other.NormalZ)
			return true;
		return false;
	}
	bool equal_pos(Vertex other)
	{
		if (this->x == other.x &&
			this->y == other.y &&
			this->z == other.z) 
			return true;
		return false;
	}
	void Transform(DirectX::XMMATRIX m)
	{
		this->x = (m.r[0].m128_f32[0] * this->x) + (m.r[1].m128_f32[0] * this->y) + (m.r[2].m128_f32[0] * this->z) + (m.r[3].m128_f32[0] * 1);
		this->y = (m.r[0].m128_f32[1] * this->x) + (m.r[1].m128_f32[1] * this->y) + (m.r[2].m128_f32[1] * this->z) + (m.r[3].m128_f32[1] * 1);
		this->z = (m.r[0].m128_f32[2] * this->x) + (m.r[1].m128_f32[2] * this->y) + (m.r[2].m128_f32[2] * this->z) + (m.r[3].m128_f32[2] * 1);
	}
};

namespace math
{
	static double ToRadians(float Deg)
	{
		return Deg * 0.01745329251994329576923690768489;
	}

}

template <typename t>
bool between(t a, t b, t bw)
{
	return (bw < std::max(a, b) && bw > std::min(a, b)) ? true : false;
}

template <typename t>
bool nearlyEqual(t a, t b, t err)
{
	return (abs(a - b) < err) ? true : false;
}

template <typename t>
bool UniqueiItem(t* pT, size_t size, t item)
{
	for (int i = 0; i < size / sizeof(t); i++)
		if (pT[i] == item) return false;
	return true;
}

static float2 MouseInCartisian(HWND hwnd, int width, int height)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	float x = ((float)p.x * 2) / (float)width;
	float y = ((float)p.y * 2) / (float)height;

	x -= 1;
	y = 2 - y;
	y -= 1;
	float2 a{ x, y };
	return a;
}

static bool operator==(DirectX::XMMATRIX m1, DirectX::XMMATRIX m2)
{
	return (m1.r[0].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[0].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[0].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[0].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[1].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[1].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[1].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[1].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[2].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[2].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[2].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[2].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[3].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[3].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[3].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[3].m128_f32[3] == m2.r[0].m128_f32[3]) ? true : false;
}

static bool operator!=(DirectX::XMMATRIX m1, DirectX::XMMATRIX m2)
{
	return (m1.r[0].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[0].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[0].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[0].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[1].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[1].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[1].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[1].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[2].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[2].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[2].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[2].m128_f32[3] == m2.r[0].m128_f32[3] &&
		m1.r[3].m128_f32[0] == m2.r[0].m128_f32[0] &&
		m1.r[3].m128_f32[1] == m2.r[0].m128_f32[1] &&
		m1.r[3].m128_f32[2] == m2.r[0].m128_f32[2] &&
		m1.r[3].m128_f32[3] == m2.r[0].m128_f32[3]) ? false : true;
}