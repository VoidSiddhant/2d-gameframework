#include"Engine.h"
#ifndef VECTOR_H
#define VECTOR_H

namespace Engine
{
	struct Vector3
	{
		Vector3();
		Vector3(const float& v1, const float& v2, const float& v3);
		void operator= (const Vector3& v);
		//void operator= (const D3DXVECTOR3& v);
		Vector3 operator+ (const Vector3& v2);
		void operator+= (const Vector3& v2);
		Vector3 operator* (const Vector3& v2);
		Vector3 operator* (const float& value);
		double Distance(const Vector3& v2);
		void dot(const Vector3& v2);
		float x, y, z;
	};

	struct Vector2
	{
		Vector2();
		Vector2(const float& v1, const float& v2);
		Vector2(const Vector2& v);
		void operator= (const Vector2& v);
		//void operator= (const D3DXVECTOR2& v);
		void operator+= (const Vector2& v2);
		bool operator== (const Vector2& v2);
		bool operator!= (const Vector2& v2);
		Vector2 operator+ (const Vector2& v2);
		Vector2 operator* (const Vector2& v2);
		Vector2 operator* (const float& value);
		Vector2& operator/ (const float& value);
		Vector2 operator- (const Vector2& v2);
		double Magnitude();
		double Distance(const Vector2& v2);
		double Angle_R(Vector2& v2);
		double Angle_D(Vector2& v2);
		double dot(const Vector2& v2);
		//Linearly Interpolate To in Fraction t (t = 0 to t = 1)
		Vector2 Lerp(const Vector2& destination, const double& t);
		float x, y;
	};
};
#endif
