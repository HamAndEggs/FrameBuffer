
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <cstdarg>
#include <string.h>

#include "Tiny2D.h"

// Very simple button rendering class example. No logic.
class Button
{
public:
	Button(int pX,int pY,int pWidth,int pHeight,const char* pText)
	{
		mRect.FromX = pX;
		mRect.FromY = pY;
		mRect.ToX = pX + pWidth;
		mRect.ToY = pY + pHeight;
		SetText(pText);
		SetColour(150,150,150);
		SetTextColour(0,0,0);
		SetTextPressedColour(200,200,200);
	}

	void Render(tiny2d::DrawBuffer& pRT,const tiny2d::PixelFont& pFont,bool pPressed)
	{
		pRT.FillRectangle(mRect.FromX,mRect.FromY,mRect.ToX,mRect.ToY,mFillColour.r,mFillColour.g,mFillColour.b);
	
		if( pPressed )
		{
			pRT.DrawLineH(mRect.FromX,mRect.FromY,mRect.ToX,mDarkColour.r,mDarkColour.g,mDarkColour.b);
			pRT.DrawLineV(mRect.FromX,mRect.FromY,mRect.ToY,mDarkColour.r,mDarkColour.g,mDarkColour.b);
	
			pRT.DrawLineH(mRect.FromX,mRect.ToY,mRect.ToX,mLightColour.r,mLightColour.g,mLightColour.b);
			pRT.DrawLineV(mRect.ToX,mRect.FromY,mRect.ToY,mLightColour.r,mLightColour.g,mLightColour.b);
		}
		else
		{
			pRT.DrawLineH(mRect.FromX,mRect.FromY,mRect.ToX,mLightColour.r,mLightColour.g,mLightColour.b);
			pRT.DrawLineV(mRect.FromX,mRect.FromY,mRect.ToY,mLightColour.r,mLightColour.g,mLightColour.b);
	
			pRT.DrawLineH(mRect.FromX,mRect.ToY,mRect.ToX,mDarkColour.r,mDarkColour.g,mDarkColour.b);
			pRT.DrawLineV(mRect.ToX,mRect.FromY,mRect.ToY,mDarkColour.r,mDarkColour.g,mDarkColour.b);
		}
	
		if(mText.size()>0)
		{
			// Need to add font hot spot thing to font, IE center at x,y rendering. But for now do here in the button code.
			int x = (mRect.FromX + mRect.ToX) / 2;
			int y = (mRect.FromY + mRect.ToY) / 2;
			
			int len = mText.size();
			x -= (len*8)/2;
			y -= 13/2;
	
			if( pPressed )
				pFont.Print(pRT,x,y,mTextPressedColour.r,mTextPressedColour.g,mTextPressedColour.b,mText);
			else
				pFont.Print(pRT,x,y,mTextColour.r,mTextColour.g,mTextColour.b,mText);
		}
	}
	
	void SetText(const std::string& pText)
	{
		mText = pText;
	}
	
	void SetTextf(const char* pFmt,...)
	{
		char buf[1024];	
		va_list args;
		va_start(args, pFmt);
		vsnprintf(buf, sizeof(buf), pFmt, args);
		va_end(args);
		SetText(buf);
	}

	void SetColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)	// Makes mLightColour a bright version of the colour, mDarkColour a darkened version and sets the mFillColour to the colour passed in. Does not change text colour.	
	{
		SetLightColour((uint8_t)std::min(255,((int)pRed<<1)),(uint8_t)std::min(255,((int)pGreen<<1)),(uint8_t)std::min(255,((int)pBlue<<1)));
		SetFillColour(pRed,pGreen,pBlue);
		SetDarkColour(pRed>>1,pGreen>>1,pBlue>>1);
	}

	void SetLightColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)
	{
		mLightColour.r = pRed;
		mLightColour.g = pGreen;
		mLightColour.b = pBlue;
	}
	
	void SetFillColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)
	{
		mFillColour.r = pRed;
		mFillColour.g = pGreen;
		mFillColour.b = pBlue;
	}
	
	void SetDarkColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)
	{
		mDarkColour.r = pRed;
		mDarkColour.g = pGreen;
		mDarkColour.b = pBlue;
	}
	
	void SetTextColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)
	{
		mTextColour.r = pRed;
		mTextColour.g = pGreen;
		mTextColour.b = pBlue;
	}
	
	void SetTextPressedColour(uint8_t pRed,uint8_t pGreen,uint8_t pBlue)
	{
		mTextPressedColour.r = pRed;
		mTextPressedColour.g = pGreen;
		mTextPressedColour.b = pBlue;
	}
		
private:
	
	struct
	{
		int FromX,FromY,ToX,ToY;
	}mRect;

	struct
	{
		uint8_t r,g,b;
	}mLightColour,mFillColour,mDarkColour,mTextColour,mTextPressedColour;

	std::string mText;
};

int main(int argc, char *argv[])
{	
    std::cout << "Application Version " << APP_VERSION << '\n';
    std::cout << "Build date and time " << APP_BUILD_DATE_TIME << '\n';
    std::cout << "Build date " << APP_BUILD_DATE << '\n';
    std::cout << "Build time " << APP_BUILD_TIME << '\n';

	tiny2d::FrameBuffer* FB = tiny2d::FrameBuffer::Open(true);
	if( !FB )
		return 1;

    tiny2d::DrawBuffer RT(FB);
	RT.Clear(150,150,150);

	srand(time(NULL));

//	uint8_t col[8][3] = {{0,0,0},{255,0,0},{0,255,0},{0,0,255},{255,255,255},{255,0,255},{255,255,0},{0,255,255}};


	tiny2d::PixelFont TheFont(3);
	Button TheButton(100,100,150,50,"This is a button");
	Button GreenButton(200,200,150,50,"A green button");
	GreenButton.SetColour(30,150,30);

	TheFont.SetPenColour(0,0,0);

	int n = 149;
	timespec SleepTime = {0,10000000};
	while(FB->GetKeepGoing())
	{
		if( ((n)>>4) != ((n-1)>>4) )
		{
			RT.FillRectangle(9*8*5,0,19*8*5,13*5,150,150,150);
			TheFont.SetPixelSize(5);
			TheFont.Printf(RT,0,0,"Counting %d",n>>4);
		}

		TheFont.SetPixelSize(1);
		if( (((n-1)%150)&128) != ((n%150)&128) )// Only draw when it changes to stop flicker. This is a simple frame buffer lib. If you want offscreen buffers and high speed, use SDL.
		{
			TheButton.Render(RT,TheFont,((n%150)&128) != 0);
			GreenButton.Render(RT,TheFont,((n%150)&128) != 0);
		}
		
		FB->Present(RT);
		n++;
		nanosleep(&SleepTime,NULL);
	};

	delete FB;
	return 0;
}
