#ifndef CAMERA_H
#define CAMERA_H

#include "Engine.h"

namespace Engine
{
	class Camera
	{
	public:
		Camera(float fov, Vector3 position, Vector3 target);
		void setPosition(Vector3);
		void RotateAbout(const float& radius, const Vector3& speed);
		Vector3 getPos(){ return pos; }
		void SetPositionX(const float& X){ pos.x = X; }
		void SetPositionY(const float& Y){ pos.y = Y; }
		void SetPositionZ(const float& Z){ pos.z = Z; }
		void setProperty(float fov, Vector3 target);
		void Set();

	private:
		float fov;
		Vector3 pos,target;
	};
};

#endif