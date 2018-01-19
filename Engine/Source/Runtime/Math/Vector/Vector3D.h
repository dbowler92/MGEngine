//Vector3D.h
//Created 15/07/17
//Created By Daniel Bowler
//
//My simple vector3D math library

#pragma once

#include <math.h> //Sqrt()

struct FVector3D
{
public:
	//Public components
	float x, y, z;

public:
	//Default constructor (returns zero vector) & destructor
	FVector3D()
	{
		x = 0.0f; y = 0.0f;  z = 0.0f;
	};

	~FVector3D() {};

	//Other constructors
	FVector3D(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	};

	FVector3D(FVector3D& other)
	{
		x = other.x; y = other.y; z = other.z;
	};

	//Assignment operator
	FVector3D& operator=(FVector3D& other)
	{
		this->x = other.x; this->y = other.y; this->z = other.z;
		return (*this);
	};

	//Overload the [] operator. Returns the ith component
	float& operator[](int i)
	{
		return ((&x)[i]);
	};

	const float& operator[](int i) const
	{
		return ((&x)[i]);
	};

	//Overloaded operators:
	FVector3D& operator*=(FVector3D& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return (*this);
	};

	FVector3D& operator*=(float s)
	{
		x *= s; y *= s; z *= s;
		return (*this);
	};

	FVector3D& operator/=(FVector3D& v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return (*this);
	};

	FVector3D& operator/=(float s)
	{
		s = 1.0f / s;
		x *= s; y *= s; z *= s;
		return (*this);
	};

	FVector3D& operator+=(FVector3D& v)
	{
		x += v.x; y += v.y; z += v.z;
		return (*this);
	};

	FVector3D& operator+=(float s)
	{
		x += s; y += s; z += s;
		return (*this);
	};

	FVector3D& operator-=(FVector3D& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return (*this);
	};

	FVector3D& operator-=(float s)
	{
		x -= s; y -= s; z -= s;
		return (*this);
	};
};

//
//Vector3 Global operators:
//
inline FVector3D operator *(const FVector3D& v, float s)
{
	return (FVector3D(v.x * s, v.y * s, v.z * s));
}

inline FVector3D operator *(const FVector3D& v, const FVector3D& v2)
{
	return (FVector3D(v.x * v2.x, v.y * v2.y, v.z * v2.z));
}

inline FVector3D operator /(const FVector3D& v, float s)
{
	s = 1.0f / s;
	return (FVector3D(v.x * s, v.y * s, v.z * s));
}

inline FVector3D operator /(const FVector3D& v, const FVector3D& v2)
{
	return (FVector3D(v.x / v2.x, v.y / v2.y, v.z / v2.z));
}

inline FVector3D operator +(const FVector3D& a, const FVector3D& b)
{
	return (FVector3D(a.x + b.x, a.y + b.y, a.z + a.z));
}

inline FVector3D operator -(const FVector3D& a, const FVector3D& b)
{
	return (FVector3D(a.x - b.x, a.y - b.y, a.z - a.z));
}

inline FVector3D operator -(const FVector3D& v)
{
	return (FVector3D(-v.x, -v.y, -v.z)); //Negates the vector
}

//Global vector functions
inline float Length(const FVector3D& v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float Magnitude(const FVector3D& v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline FVector3D Normalize(const FVector3D& v)
{
	return (v / Magnitude(v));
}