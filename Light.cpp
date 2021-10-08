#include"Light.h"

namespace Engine
{
	Light::Light(int light_index, D3DLIGHTTYPE type, Vector3 position, Vector3 direction) :light_num(light_index), light_type(type), pos(position), dir(direction)
	{
		range = 100.0f;
		light_color = { 1.0f, 1.0f, 1.0f, 1.0f };
		this->SetUp();
	}

	void Light::SetUp()
	{
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		
		//D3DCOLORVALUE dcol = { 1.0f, 1.0f, 1.0f, 1.0f };
		light.Diffuse = light_color;
		light.Ambient = light_color;

		switch (light_type)
		{
		case D3DLIGHT_DIRECTIONAL:
			light.Type = D3DLIGHT_DIRECTIONAL;
			light.Range = range;
			D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &D3DXVECTOR3(dir.x,dir.y,dir.z));
			break;
		case D3DLIGHT_POINT:
			light.Type = D3DLIGHT_POINT;
			light.Range = range;
			light.Position = D3DXVECTOR3(pos.x,pos.y,pos.z);
			light.Direction = D3DXVECTOR3(dir.x,dir.y,dir.z);
			light.Attenuation0 = 0.1f;
			light.Range = range;
			break;
		case D3DLIGHT_SPOT:
			light.Type = D3DLIGHT_SPOT;
			light.Position = D3DXVECTOR3(pos.x, pos.y, pos.z);
			light.Direction = D3DXVECTOR3(dir.x,dir.y,dir.z);
			light.Range = range;
			light.Attenuation0 = 1.0f;
			light.Phi = 1.0f;
			light.Theta = 0.5f;
			light.Falloff = 1.0f;
			break;
		}

		gp_Engine->getDevice()->SetLight(light_num, &light);
	}

	Light::~Light()
	{
	}

	void Light::Show()
	{
		gp_Engine->getDevice()->LightEnable(light_num, true);
	}

	void Light::Hide()
	{
		gp_Engine->getDevice()->LightEnable(light_num, false);
	}


};