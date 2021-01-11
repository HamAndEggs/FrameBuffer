
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <cstdarg>
#include <string.h>

#include "framebuffer.h"

bool KeepGoing = true;

void static CtrlHandler(int SigNum)
{
	static int numTimesAskedToExit = 0;
	std::cout << std::endl << "Asked to quit, please wait" << std::endl;
	if( numTimesAskedToExit > 2 )
	{
		std::cout << "Asked to quit to many times, forcing exit in bad way" << std::endl;
		exit(1);
	}
	KeepGoing = false;
}

int main(int argc, char *argv[])
{
// Say hello to the world!
    std::cout << "Hello world, a skeleton app generated by appbuild.\n";

// Display the constants defined by app build. \n";
    std::cout << "Application Version " << APP_VERSION << '\n';
    std::cout << "Build date and time " << APP_BUILD_DATE_TIME << '\n';
    std::cout << "Build date " << APP_BUILD_DATE << '\n';
    std::cout << "Build time " << APP_BUILD_TIME << '\n';

    FBIO::FrameBuffer* FB = FBIO::FrameBuffer::Open(true);
	if( !FB )
    {
		return EXIT_FAILURE;
    }

	signal (SIGINT,CtrlHandler);

	srand(time(NULL));

    const uint8_t BG_R = 255;
    const uint8_t BG_G = 0;
    const uint8_t BG_B = 0;

	FB->ClearScreen(BG_R,BG_G,BG_B);

    FBIO::FreeTypeFont FTFont(FB,"./Blenda Script.otf",80);
    FTFont.SetPenColour(0,0,0);
    FTFont.SetBackgroundColour(BG_R,BG_G,BG_B);
    FTFont.Printf(FB,0,80,"Blenda Script 0123456789 :)");

    FTFont.SetPenColour(0,255,255);
    FTFont.Print(FB,0,180,"Spacing Test iAlBjXvIoiP X l");

    FBIO::FreeTypeFont FTFont2(FB,"./MachineScript.ttf",50);
    FTFont2.SetPenColour(0,255,0);
    FTFont2.SetBackgroundColour(BG_R,BG_G,BG_B);
    FTFont2.Print(FB,10,300,"Test Number 0123456789");
    FTFont2.Print(FB,10,400,"Random Number");

    FTFont2.SetPenColour(255,255,255);
    FTFont2.SetBackgroundColour(0,0,0);
    while( KeepGoing )
    {
        FB->DrawRectangle(500,350,1000,420,0,0,0,true);
        FTFont2.Printf(FB,500,400,"%d",rand());
        sleep(1);
    }

	delete FB;

// And quit";
    return EXIT_SUCCESS;
}
