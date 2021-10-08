#include "Engine.h"

extern Engine::Engine* gp_Engine = nullptr;

namespace Engine
{
	Engine::Engine(LPCSTR wCaption, HINSTANCE hInstance,bool fullscreen)
	{
		enable_fullscreen = !fullscreen;
		list_size = 0;
		m_title = wCaption;
		m_hInstance = hInstance;
		frame_limit = 0;
		QuitEngine = false;
		clear_color = D3DCOLOR_XRGB(30, 144, 255);
		this->initWnd();
		this->initD3d();

		//Create Sprite Interface For Engine to use
		D3DXCreateSprite(lp_d3ddev, &int_sprite);
		
	/*	if (dest_file)
			dest_file = NULL;
		else if (!dest_file)*/
			dest_file=fopen("Exit.txt", "w");
	}

	int Engine::loadGame()
	{
		return this->run();
	}

	void Engine::SetAmbient(D3DCOLOR col)
	{
		lp_d3ddev->SetRenderState(D3DRS_AMBIENT, col);
	}
	void Engine::showMessage(std::string message, std::string caption)
	{
		MessageBox(m_mainWnd, message.c_str(), caption.c_str(), MB_OK);
	}

	void Engine::initWnd()
	{
		WNDCLASS wc;
		ZeroMemory(&wc, sizeof(WNDCLASS));
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = m_hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpfnWndProc = WinProc;
		wc.hbrBackground = HBRUSH(COLOR_WINDOW);
		wc.lpszClassName = "GameWindow1";

		RegisterClass(&wc);

		m_mainWnd = CreateWindow("GameWindow1", m_title, WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_mainWnd, NULL, m_hInstance, NULL);
		if (!m_mainWnd)
		{
			MessageBox(m_mainWnd, "Window Could Not Be Created", "Error!!!", MB_OK);
		}
		ShowWindow(m_mainWnd, SW_SHOW);
	}


	void Engine::initD3d()
	{
		D3DDISPLAYMODE dm;
		lp_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		lp_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
		//Setting DirectX configuration for Current Accquired Device
		D3DPRESENT_PARAMETERS lp_d3dpp;
		ZeroMemory(&lp_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		lp_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		lp_d3dpp.BackBufferCount = 1;
		lp_d3dpp.BackBufferFormat = dm.Format;
		lp_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
		lp_d3dpp.BackBufferWidth = SCREEN_WIDTH;
		lp_d3dpp.EnableAutoDepthStencil = true;
		lp_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		lp_d3dpp.hDeviceWindow = m_mainWnd;
		lp_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		lp_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		lp_d3dpp.Windowed = enable_fullscreen;
		lp_d3dpp.Flags = 0;
		lp_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
		lp_d3dpp.MultiSampleQuality = D3DMULTISAMPLE_7_SAMPLES;

		static std::ofstream file;

		DWORD pQuality;
		lp_d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, dm.Format, false, D3DMULTISAMPLE_NONMASKABLE, &pQuality);
		std::ostringstream os;
		os << "AA type : \n" << pQuality;
		file.open("AA CHECK.txt");
		file << os.str();
		file.close();

		if (FAILED(lp_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_mainWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &lp_d3dpp, &lp_d3ddev)))
		{
			MessageBox(m_mainWnd, "Create Device Failed!!!", "Erorr!!", MB_ABORTRETRYIGNORE);
			QuitEngine = true;
		}

		lp_d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		lp_d3ddev->SetRenderState(D3DRS_ZENABLE, true);
		lp_d3ddev->SetRenderState(D3DRS_LIGHTING, false);
		lp_d3ddev->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
		lp_d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		lp_d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		lp_d3ddev->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);
		
	}

	void Engine::EnableLighting(const bool& status)
	{

	}

	//GAME LOOP..............................................
	int Engine::run()
	{
		MSG msg;
		msg.message = NULL;
		//Create Pointer Classes
		font = new Font();
		input = new Input();
		time = new Timer();
		mathf = new Mathf();
		this->Start();
		//Game Loop
		while (!QuitEngine)
		{
			if (PeekMessage(&msg, m_mainWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				input->Poll();
				time->calculateDeltaTime();
				dt = time->deltaTime();
				time->calculateTotalTime();
				time->calculateFrameRate();
				this->CheckCollisions();
				update(dt); //Virtual Function

				gameUpdate(); //Extern function
				drawScene();		

			}
		}
		//delete gp_Engine;
		return (int)msg.wParam;
	}

	void Engine::drawScene()
	{
		lp_d3ddev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(49,77, 121), 1.0f, 0);
		
		lp_d3ddev->BeginScene();
		int_sprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_ALPHABLEND);
		renderScene();
		int_sprite->Flush();
		int_sprite->End();
		lp_d3ddev->EndScene();

		lp_d3ddev->Present(0, 0, 0, 0);
	}

	Engine::~Engine()
	{
		fputs("\nDevice Released \n D3D released",dest_file);
		
		delete font;
		delete time;
		delete input;
		lp_d3ddev->Release();
		lp_d3d->Release();	
		int_sprite->Release();

		fclose(dest_file);
	}

	//Collision Listing
	void Engine::SetCollision(Sprite* obj)
	{
		sprite_list.push_back(obj);
		
	}
	void Engine::RemoveCollision(Sprite* obj)
	{
		sprite_list.remove(obj);
	}
	//Checking Collisions
	void Engine::CheckCollisions()
	{
		// Basic Circular Collision Test......
		
		Sprite* sp1;
		Sprite* sp2;
			std::list<Sprite*>::iterator iter1;
			std::list<Sprite*>::iterator iter2;
			iter1 = sprite_list.begin();
			
			
				
				while (iter1 != sprite_list.end())
				{
					sp1 = (Sprite*)*iter1;

					sp1->ContactX() = true;
					sp1->ContactTop() = true;
					sp1->ContactBot() = true;
					if (sp1->Tag() != "Collide" && sp1 == nullptr)
					{
						iter1++;
						continue;
					}

					for (int i = 0; i < 3 && (sp1->ContactBot() || sp1->ContactTop() || sp1->ContactX()); i++)
					{
						//					MessageBox(m_mainWnd, "Hello", "Hello", MB_OK);
						float nextMoveX = sp1->GetVelocity().x;
						float nextMoveY = sp1->GetVelocity().y;
						float originalMoveX = nextMoveX;
						float originalMoveY = nextMoveY;
						sp1->ContactX() = false;
						sp1->ContactTop() = false;
						sp1->ContactBot() = false;
						iter2 = sprite_list.begin();
						while (iter2 != sprite_list.end() && !sp1->ContactX() && !sp1->ContactTop() && !sp1->ContactBot())
						{
							sp2 = (Sprite*)*iter2;
							if (sp1 == sp2 || sp2->Tag() == "Collide" || sp2 == nullptr)
							{
								iter2++;
								continue;
							}
								//dir = 0(top),dir = 1(bot),dir = 2(left),dir = 3(right)
								for (int dir = 0; dir < 4; dir++)
								{
									if (dir == 0 && nextMoveY < 0)continue;
									if (dir == 1 && nextMoveY > 0)continue;
									if (dir == 2 && nextMoveX > 0)continue;
									if (dir == 3 && nextMoveX < 0)continue;

									float projectedMoveX = (dir > 1 ? nextMoveX : 0);
									float projectedMoveY = (dir <= 1 ? nextMoveY : 0);

									while (ContainsPoint(sp2, static_cast<int>(sp1->GetCollisionPoints()[dir * 2].x + projectedMoveX), static_cast<int>(sp1->GetCollisionPoints()[dir * 2].y + projectedMoveY))
										|| ContainsPoint(sp2, static_cast<int>(sp1->GetCollisionPoints()[dir * 2 + 1].x + projectedMoveX), static_cast<int>(sp1->GetCollisionPoints()[dir * 2 + 1].y + projectedMoveY)))

									{
										if (dir == 0)projectedMoveY--;
										if (dir == 1)projectedMoveY++;
										if (dir == 2)projectedMoveX++;
										if (dir == 3)projectedMoveX--;
									}
									if (dir >= 2 && dir <= 3) nextMoveX = projectedMoveX;
									if (dir >= 0 && dir <= 1) nextMoveY = projectedMoveY;
								}
								//Find Contact Point
								if (nextMoveY < originalMoveY && originalMoveY > 0)
									sp1->ContactTop() = true;
								if (nextMoveY > originalMoveY && originalMoveY < 0)
									sp1->ContactBot() = true;
								if (abs(nextMoveX - originalMoveX) > 0.01f)
									sp1->ContactX() = true;
							
							iter2++;
						}//End of Iteration2
						//Set New Movement Vector For the Object sp1
						if (sp1->ContactTop() || sp1->ContactBot())
						{
							sp1->Velocity().y = 0;
							sp1->Translate(Vector2(0, nextMoveY));
						}
						if (sp1->ContactX())
						{
							sp1->Velocity().x = 0;
							sp1->Translate(Vector2(nextMoveX, 0));
						}
					}
					iter1++;
				}
		}

	bool Engine::ContainsPoint(Sprite* object,  int pointX, int pointY)
	{
		RECT r = { (object->GetPos().x ),
			(object->GetPos().y - 80.0f ) , 
			(object->GetPos().x + object->GetFrameWidth()*object->GetScale().x ), 
			(object->GetPos().y - object->GetFrameHeight()*object->GetScale().y)
		};
		if (pointX >= r.left && pointX <= r.right && pointY >= r.bottom && pointY <= r.top)
			return true;
		else
			return false;
	}
}; // End Namespace

LRESULT CALLBACK WinProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_QUIT:
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		gp_Engine->Close();
		break;
	}
	return DefWindowProc(wnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR CmdLine, int nCmdShow)
{
	return gamePreload(hInstance);
}
