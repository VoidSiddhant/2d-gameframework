#ifndef ENGINE_H
#define ENGINE_H
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<math.h>
#include<d3d9.h>
#include<iostream>
#include<d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#define Destroy(x) delete x

#include<dinput.h>
#include<string.h>
#include<sstream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include"Mathf.h"
#include"Vector.h"
#include"Timer.h"
#include"Font.h"
#include"Camera.h"
#include"Mesh.h"
#include"Input.h"
#include"Light.h"
#include"Sprite.h"
#include<fstream>

#define WIN32_LEAN_MEAN
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxerr.lib")



LRESULT CALLBACK WinProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);

extern int gamePreload(HINSTANCE);  //Linking the Game Class
extern void gameUpdate();   //Ingame Entity Updates

namespace Engine
{
	
	class Engine
	{
	public:
		Engine(LPCSTR, HINSTANCE,bool fullscreen);
		~Engine();
		void initWnd(void);
		void initD3d(void);
		int run(void);
		virtual void Start(){}			//Overriden By Game Class....To Set Up The Levels.
		virtual void update(float){}	//Overriden By Game Class....To Update Game Code Each Frame.
		virtual void renderScene(){}	//Overriden By Game Class....To Draw Game Code Each Frame.
		virtual void OnResetDevice(){}	//Overriden By Game Class....To Reset The Level.
		void drawScene(void);
		int loadGame();
		void showMessage(std::string message, std::string caption);
		HWND getMainWnd(void)	{return m_mainWnd;}
		void drawSprite(LPDIRECT3DTEXTURE9, D3DXVECTOR2, D3DXVECTOR2);
		LPDIRECT3DDEVICE9 getDevice(void) { return lp_d3ddev; }
		void SetAmbient(D3DCOLOR);
		HINSTANCE GetInstance(){ return m_hInstance; }
		void Close(){ QuitEngine = true; }
		void ClearScene(const D3DCOLOR& inCol) { clear_color = inCol; }
		LPD3DXSPRITE GetInterfaceSprite(){ return int_sprite; }
		FILE* GetDestFile(){ return this->dest_file; }
		void EnableLighting(const bool& status);
		void SetCollision(Sprite* obj);
		void RemoveCollision(Sprite* obj);
		void CheckCollisions(void);
		float GetDeltaTime(){ return dt; }
		Timer* GetTimer(){ return time; }
		Font* GetFont(){ return font; }
		void EnginePrint(void);
		bool ContainsPoint(Sprite* object,int pointX, int pointY);
		void SetFullscreen(const bool& value){ enable_fullscreen = value; }
		int ls(){ return list_size; } // REMOVE THIS...later..

	private:
		FILE* dest_file;
		LPCSTR m_title;
		HINSTANCE m_hInstance;
		HWND m_mainWnd;
		LPDIRECT3D9 lp_d3d;
		bool isPaused,enable_fullscreen;
		bool QuitEngine;
		LPDIRECT3DDEVICE9 lp_d3ddev;
		D3DCOLOR clear_color;
		LPD3DXSPRITE int_sprite;
		std::list<Sprite*> sprite_list;
		int list_size;
		float frame_limit;

		Vector2 collision_vector, col_escape;

	protected:
		float dt;
		Timer* time;
		Font* font;
		Input* input;
		Mathf* mathf;

	};
}; // End of NameSpace

extern Engine::Engine* gp_Engine;

#endif