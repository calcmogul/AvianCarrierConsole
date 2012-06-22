#include "GUI/Toolbar.h"

CONSOLE_SCREEN_BUFFER_INFO Toolbar::csbi;
HANDLE Toolbar::hOut = GetStdHandle(STD_OUTPUT_HANDLE);

Toolbar::Toolbar( int row , char newchar ) {
	GetConsoleScreenBufferInfo( hOut , &csbi );
	cursorRow = row;
	character = newchar;
	redraw();
}

void Toolbar::redraw(){
	for ( int i = 0 ; i < csbi.dwSize.X ; i++ ) {
		gotoxy(hOut, i, cursorRow);
		std::cout << character;
	}
}
