#include"Font.h"

namespace Engine
{
	Font::Font()
	{
		mFont = 0;
		height = 20;
		width = 15;
		weight = 10;
		D3DXFONT_DESC mFontDesc;
		mFontDesc.Height = height;
		mFontDesc.Width = width;
		mFontDesc.Weight = weight;
		mFontDesc.MipLevels = 1;
		mFontDesc.Italic = false;
		mFontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		mFontDesc.Quality = DEFAULT_QUALITY;
		mFontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		mFontDesc.CharSet = DEFAULT_CHARSET;
		strcpy_s(mFontDesc.FaceName, _T("Times New Roman"));

		HRESULT hr = D3DXCreateFontIndirect(gp_Engine->getDevice(), &mFontDesc, &mFont);
		
		if (hr == E_OUTOFMEMORY)
			MessageBox(gp_Engine->getMainWnd(), "OUT OF MEM", "LEAK", MB_OK);
		else if (hr == D3DERR_INVALIDCALL)
			MessageBox(gp_Engine->getMainWnd(), "ALL NOT OK", "NOT FINE", MB_OK);

	}

	void Font::setProperties(int ht, int wt, int wg)
	{
		height = ht; width = wt; weight = wg;
	}
	

	void Font::displayFont(std::string message, double variable)
	{
		static float rnd = 2.0f;
		static char buffer[256];
		std::ostringstream out;
		out << message << variable;
		message = out.str();
		sprintf(buffer, message.c_str());
		RECT R = {0,0,50,50};
		int result = mFont->DrawText(NULL, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
		if (result == 0)
		{
			MessageBox(gp_Engine->getMainWnd(), "draw text failed", "Text Failure", MB_OK);
			
		}
	}

	void Font::OnResetDevice()
	{
		mFont->OnResetDevice();
	}
	
	void Font::OnLostDevice()
	{
		mFont->OnLostDevice();
	}

	Font::~Font()
	{
		//fopen("Exit.txt", "a");
		fputs("\n Font Released",gp_Engine->GetDestFile());
		//fclose(gp_Engine->GetDestFile());
		mFont->Release();
	}
};