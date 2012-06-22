#include "GUI/Graphics.h"

HANDLE Graphics::hOut = GetStdHandle( STD_OUTPUT_HANDLE );

Graphics::Graphics( int xPosition , int yPosition , std::string wording , int pic ) {
	xPos = xPosition;
	yPos = yPosition;
	caption = wording;
	graphic = pic;
	redraw();
}

void Graphics::redraw() {
	gotoxy( hOut , xPos , yPos );
	choose( graphic );
}

void Graphics::choose( int pic ) {
	graphic = pic;
	switch( graphic )
	{
	case 0:
		std::cout << "    .-\"- \n"
				"   / 6_6 \\ \n"
				"   \\ ""_ (__\\ " << "\n"
				"   //   \\\\ " << "\n"
				"  ((     )) \n            " << "\n" "     ||| \n"
			   "     ||| \n"
			   "     '|'";
		break;
	case 1:
		//empty
		break;

	}
}
