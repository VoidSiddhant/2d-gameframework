#include "Vector.h"
#include"Engine.h"

#ifndef INPUT_H
#define INPUT_H


#define HorizontalAxisN DIK_A
#define HorizontalAxisP DIK_D
#define VerticalAxisP DIK_W
#define VerticalAxisN DIK_S

namespace Engine
{
	class Input
	{
	public:
		Input();
		~Input();
		void Poll();
		bool GetKeyDown(char keyname);
		bool GetKey(){}
		bool GetKeyUp(){}
		bool GetMouseBtnDown(int button);
		int GetHorizontalAxis(void);
		int GetVerticalAxis(void);
		Vector2 GetMouseAxis(void);
		long GetMouseWheelAxis(void){ return mouseState.lZ; }

	private:
		IDirectInput8* di;
		IDirectInputDevice8* dev_keyboard;
		IDirectInputDevice8* dev_mouse;
		char keyState[256];
		DIMOUSESTATE2 mouseState;
		std::string currentKey;
	};
};
#endif