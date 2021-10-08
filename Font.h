
#include"Engine.h"
#ifndef FONT_H
#define FONT_H

#define _CRT_SECURE_NO_WARNINGS
#include<tchar.h>


namespace Engine
{
	class Font
	{
	public:
		Font();
		void displayFont(std::string msg, double variable);
		void OnResetDevice();
		void OnLostDevice();
		void setProperties(int,int,int);
		~Font();
	private:
		ID3DXFont* mFont;
		int height,width,weight;
		
	};
};

#endif