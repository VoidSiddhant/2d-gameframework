#include"Camera.h"

namespace Engine
{
	Camera::Camera(float fo, Vector3 position, Vector3 tar) : fov(fo), pos(position), target(tar)
	{
		D3DXMATRIX P;
		RECT R;
		GetClientRect(gp_Engine->getMainWnd(), &R);
		D3DXMatrixPerspectiveFovLH(&P, fov, (float)R.right / (float)R.bottom, 0.5f, 2000.0f);
		gp_Engine->getDevice()->SetTransform(D3DTS_PROJECTION, &P);
		this->Set();
	}

	void Camera::setPosition(Vector3 p)
	{
		pos = p;
	}

	void Camera::setProperty(float fo, Vector3 tar)
	{
		fov = fo;
		target = tar;
	}

	void Camera::Set()
	{
		D3DXMATRIX C;
		D3DXVECTOR3 upDir = { 0, 1, 0 };
		target.x = pos.x;
		target.y = pos.y;
		D3DXMatrixLookAtLH(&C, &D3DXVECTOR3(pos.x,pos.y,pos.z), &D3DXVECTOR3(target.x,target.y,target.z), &upDir);
		gp_Engine->getDevice()->SetTransform(D3DTS_VIEW, &C);
	}

	//Not Working Properly...Need to learn More Maths
	void Camera::RotateAbout(const float& radius, const Vector3& speed)
	{
		pos.x  = radius*sinf(speed.x);
		pos.z = radius*cosf(speed.z);
		pos.y = pos.y;
		//target = { 0, 0, 0 };
		D3DXMATRIX C;
		D3DXVECTOR3 upDir = { 0, 1, 0 };
		D3DXMatrixLookAtLH(&C, &D3DXVECTOR3(pos.x,pos.y,pos.z), &D3DXVECTOR3(target.x,target.y,target.z), &upDir);
		gp_Engine->getDevice()->SetTransform(D3DTS_VIEW, &C);
	}

}