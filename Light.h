
#include "Vector.h"
#include"Engine.h"
#ifndef _LIGHT_H
#define _LIGHT_H


namespace Engine
{
	class Light
	{
	public:
		Light(int light_index,D3DLIGHTTYPE type,Vector3 position,Vector3 direction);
		void SetUp();
		void SetRange(float value){ range = value; }
		void SetPos(Vector3 value){ pos = value;}
		void SetDir(Vector3 value){ dir = value; }
		void SetColor(D3DCOLORVALUE value){ light_color = value; }
		void Show();
		void Hide();
		~Light();
	private:
		D3DCOLORVALUE light_color;
		D3DLIGHTTYPE light_type;
		D3DLIGHT9 light;
		float range;
		Vector3 pos, dir;
		int light_num;
	};
};

#endif