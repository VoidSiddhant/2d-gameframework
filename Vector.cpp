#include "Vector.h"

namespace Engine
{
		Vector3::Vector3(){ x = 0; y = 0; z = 0; }

		Vector3::Vector3(const float& v1, const float& v2, const float& v3)
		{
			x = v1; y = v2; z = v3;
		}

		void Vector3:: operator= (const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		/*void Vector3::operator= (const D3DXVECTOR3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}*/

		Vector3 Vector3::operator+ (const Vector3& v2)
		{
			Vector3 vOut;
			vOut.x = x+v2.x;
			vOut.y = y+v2.y;
			vOut.z = z+v2.z;
			return vOut;
		}

		void Vector3::operator+= (const Vector3& v2)
		{
			x += v2.x;
			y += v2.y;
			z += v2.z;
			
		}

		Vector3 Vector3::operator* (const Vector3& v2)
		{
			Vector3 vOut;
			vOut.x = x*v2.x;
			vOut.y = y*v2.y;
			vOut.z = z*v2.z;
			return vOut;
		}

		Vector3 Vector3::operator* (const float& value)
		{
			Vector3 vOut;
			vOut.x = x*value;
			vOut.y = y*value;
			vOut.z = z*value;
			return vOut;
		}

		double Vector3::Distance(const Vector3& v2)
		{
			return sqrt((powf((this->x - v2.x), 2)) + (powf((this->y - v2.y), 2)) + (powf(this->z - v2.z, 2)) + (powf(this->z - v2.z, 2)));
		}

		void Vector3::dot(const Vector3& v2)
		{
			x *= v2.x;
			y *= v2.y;
			z *= v2.z;
		}

		Vector2::Vector2() { x = 0.0f; y = 0.0f; }

		Vector2::Vector2(const float& v1, const float& v2)
		{
			x = v1;
			y = v2;
		}

		Vector2::Vector2(const Vector2& v)
		{
			x = v.x;
			y = v.y;
		}

		void Vector2::operator= (const Vector2& v)
		{
			x = v.x;
			y = v.y;
		}

		/*void Vector2::operator= (const D3DXVECTOR2& v)
		{
			x = v.x;
			y = v.y;
		}*/

		Vector2 Vector2::operator+ (const Vector2& v2)
		{
			Vector2 vOut;
			vOut.x = x + v2.x;
			vOut.y = y + v2.y;
			return vOut;
		}

		Vector2 Vector2::operator- (const Vector2& v2)
		{
			return Vector2(x - v2.x, y - v2.y);
		}

		void Vector2::operator+= (const Vector2& v2)
		{
			x += v2.x;
			y += v2.y;
		}

		Vector2 Vector2::operator* (const Vector2& v2)
		{
			Vector2 vOut;
			vOut.x = x * v2.x;
			vOut.y = y*v2.y;
			return vOut;
		}

		Vector2 Vector2::operator* (const float& value)
		{
			Vector2 vOut;
			vOut.x = x * value;
			vOut.y = y * value;
			return vOut;
		}

		Vector2& Vector2::operator/ (const float& value)
		{
			x /= value;
			y /= value;
			return *this;
		}

		double Vector2::Magnitude()
		{
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
		}

		double Vector2::Distance(const Vector2& v2)
		{
			return sqrt((powf((this->x - v2.x), 2)) + (powf((this->y - v2.y), 2)));
		}

		double Vector2::Angle_R(Vector2& v2)
		{
			return (acos(this->dot(v2) / (this->Magnitude()*v2.Magnitude())));
		}

		double Vector2::Angle_D(Vector2& v2)
		{
			return (180.0f/D3DX_PI)*this->Angle_R(v2);
			//double vector = (y - v2.y) / (x - v2.x);
			//return ((180 / D3DX_PI) * this->Angle_R(v2));
			//return ((180 / D3DX_PI) * atan(vector));
		}

		double Vector2::dot(const Vector2& v2)
		{
			return (x*v2.x + y*v2.y);
		}

		bool Vector2::operator== (const Vector2& v2)
		{
			if (this->x == v2.x && this->y == v2.y)
				return true;
			else
				return false;
		}

		bool Vector2::operator!= (const Vector2& v2)
		{
			if (this->x != v2.x && this->y != v2.y)
				return true;
			else
				return false;
		}

		Vector2 Vector2::Lerp(const Vector2& Destination,const double& t)
		{
			Vector2 lerp_move ;
			lerp_move = Vector2((1 - t)*this->x + (t*Destination.x), ((1 - t)*this->y + (t*Destination.y)));
			return lerp_move;
			
		}
};