#pragma once
typedef struct MYVector
{
	float x;
	float y;
	float z;

	MYVector()
	{
		z = y = x = 0;
	}

	void Normalize()
	{
		float len = sqrtf(x * x + y * y + z * z);
		x /= len;
		y /= len;
		z /= len;
	}
	MYVector operator * (float _fnum)
	{
		MYVector v;
		v.x = x * _fnum;
		v.y = y * _fnum;
		v.z = z * _fnum;
		return v;
	}

	void operator += (const MYVector& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;	
	}

}MYVECTOR;
typedef struct Obj_Info
{
	MYVECTOR	vPos;

	int size;

	float r;
	float g;
	float b;
	float a;


	Obj_Info()
	{
		size = 100;
		r = g = b = a = 1;
	}
	Obj_Info(float _x , float _y , float _z , int _size , float _r , float _g, float _b, float _a)
	{
		vPos.x = _x;
		vPos.y = _y;
		vPos.z = _z;

		size = _size;
		r = _r;
		g = _g;
		b = _b;
		a = _a;

	}
}OBJ_INFO;