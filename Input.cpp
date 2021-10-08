#include"Input.h"

namespace Engine
{
	Input::Input()
	{
		ZeroMemory(keyState, sizeof(keyState));
		ZeroMemory(&mouseState, sizeof(mouseState));
		DirectInput8Create(gp_Engine->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
		
		//Create Keyboard Device
		di->CreateDevice(GUID_SysKeyboard, &dev_keyboard,NULL);
		dev_keyboard->SetDataFormat(&c_dfDIKeyboard);
		dev_keyboard->SetCooperativeLevel(gp_Engine->getMainWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		dev_keyboard->Acquire();

		//Create Mouse Device
		di->CreateDevice(GUID_SysMouse, &dev_mouse,NULL);
		dev_mouse->SetDataFormat(&c_dfDIMouse2);
		dev_mouse->SetCooperativeLevel(gp_Engine->getMainWnd(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		dev_mouse->Acquire();
	}

	Input::~Input()
	{
		//fopen("Exit.txt", "a");
		fputs("\n Input Released", gp_Engine->GetDestFile());
		//fclose(gp_Engine->GetDestFile());

		dev_keyboard->Unacquire();
		dev_mouse->Unacquire();
		dev_keyboard->Release();
		dev_mouse->Release();
		di->Release();
		
	}

	void Input::Poll()
	{
		//Poll Keyboard
		HRESULT hr = dev_keyboard->GetDeviceState(sizeof(keyState), (void**)&keyState);
		if (FAILED(hr))
		{
			ZeroMemory(keyState, sizeof(keyState));
			hr = dev_keyboard->Acquire();
		}

		//Poll Mouse
		hr = dev_mouse->GetDeviceState(sizeof(mouseState), (void**)&mouseState);
		if (FAILED(hr))
		{
			ZeroMemory(&mouseState, sizeof(mouseState));
			hr = dev_mouse->Acquire();

		}
	}

	bool Input::GetKeyDown(char key)
	{
		return (keyState[key] & 0x80) !=0;
	}

	bool Input::GetMouseBtnDown(int button)
	{
		return (mouseState.rgbButtons[button] & 0x80) !=0;
	}
	
	Vector2 Input::GetMouseAxis()
	{
		Vector2 pos;
		pos.x = (float)mouseState.lX;
		pos.y = (float)mouseState.lY;
		return pos;
	}

	int Input::GetHorizontalAxis()
	{

		if (this->GetKeyDown(HorizontalAxisP))
			return 1;
		else if (this->GetKeyDown(HorizontalAxisN))
			return -1;
		else
			return 0;
	}

	int Input::GetVerticalAxis()
	{
		if (this->GetKeyDown(VerticalAxisP))
			return 1;
		else if (this->GetKeyDown(VerticalAxisN))
			return -1;
		else
			return 0;
	}
	
};