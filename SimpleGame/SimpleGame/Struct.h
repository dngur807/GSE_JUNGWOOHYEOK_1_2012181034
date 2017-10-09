#pragma once

typedef struct Obj_Info
{
	float x;
	float y;
	float z;

	int size;

	float r;
	float g;
	float b;
	float a;


	Obj_Info()
	{
		size = 100;
		r = g = b = a = 1;
		y = z = x  = 0;
	}
	Obj_Info(float _x , float _y , float _z , int _size , float _r , float _g, float _b, float _a)
	{
		x = _x;
		y = _y;
		z = _z;

		size = _size;
		r = _r;
		g = _g;
		b = _b;
		a = _a;

	}
}OBJ_INFO;