#include "GUI/Window.h"

HANDLE Window::hOut = GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE Window::hIn = GetStdHandle( STD_INPUT_HANDLE );

Window::Window( int xPos , int yPos , std::string title , int xlength , int ylength ) {
	if(ylength < 5)
		ylength = 5;
	if(static_cast<unsigned int>(xlength) < title.length() + 13)
		xlength = title.length() + 13;
	tlCorner.X = xPos;
	tlCorner.Y = yPos;
	name = title;
	width = xlength;
	height = ylength;

	for ( short row = 0 ; row < height ; row++ ) {
		buffer.push_back( static_cast<CHAR_INFO*>( calloc( width , sizeof(CHAR_INFO) ) ) );
	}
}

Window::~Window() {
	if ( visible )
		erase();

	for ( unsigned int row = 0 ; row < buffer.size() ; row++ )
		free( buffer[row] );
}

bool Window::setTitle( std::string newName ) {
	if ( static_cast<short>( newName.length() ) < width - 2 ) {
		name = newName;
		return true;
	}

	return false;
}

void Window::redraw() {
	cursorToggle( hOut , 0 ); //turn cursor off
	visible = true;

	/* === reallocate right amount of memory ===
	short row;
	for ( row = 0 ; row < height ; row++ ) {
		if ( static_cast<unsigned int>(row) < buffer.size() )
			buffer[row] = static_cast<CHAR_INFO*>( realloc( buffer[row] , sizeof(CHAR_INFO) ) );
		else if ( static_cast<unsigned int>(row) == buffer.size() )
			buffer.push_back( static_cast<CHAR_INFO*>( calloc( width , sizeof(CHAR_INFO) ) ) );
	}
	while ( static_cast<unsigned int>(row) < buffer.size() ) {
		free( buffer[row] );
		buffer.erase( buffer.begin() + row );

		row++;
	}
	 ========================================= */

	for ( short row = 0 ; row < height ; row++ ) {
		restoreRegion.Left = tlCorner.X;
		restoreRegion.Top = tlCorner.Y + row;
		restoreRegion.Right = tlCorner.X + width - 1;
		restoreRegion.Bottom = tlCorner.Y + row;

		ReadConsoleOutput( hOut , buffer[row] , { width , 1 } , { 0 , 0 } , &restoreRegion );
	}

	short y = tlCorner.Y;

	SetConsoleCursorPosition( hOut , tlCorner );
	std::cout << static_cast<char>(201); //top-left corner

	for ( short x = 1 ; x < width - 2 ; x++ )
		std::cout << static_cast<char>(205); // =

	std::cout << static_cast<char>(187); //top-right corner

	y++;

	gotoxy( hOut , tlCorner.X , y );
	std::cout << static_cast<char>(186) << " " << name;
	for ( short x = name.length() + 1 ; x < width - 8 ; x++ )
		std::cout << " ";

	std::cout << "(|x|)" << static_cast<char>(186);

	y++;

	gotoxy( hOut , tlCorner.X , y );
	std::cout << static_cast<char>(204); // |-
	for ( short x = 2 ; x < width - 1 ; x++ )
		std::cout << static_cast<char>(205); // =

	std::cout << static_cast<char>(185); // -|

	y++;

	for ( ; y < tlCorner.Y + height - 1 ; y++ ) {
		gotoxy( hOut , tlCorner.X , y );
		std::cout << static_cast<char>(186); //draws left side ; ||

		for(int x = 2 ; x < width - 1 ; x++ ) {
			std::cout << " ";
		}

		std::cout << static_cast<char>(186); //draws right side ; ||
	}

	gotoxy( hOut , tlCorner.X , y );
	std::cout << static_cast<char>(200); //lower-left corner

	for ( short x = 2 ; x < width - 1 ; x++)
		std::cout << static_cast<char>(205); // =

	std::cout << static_cast<char>(188); // lower-right corner
}

void Window::erase() {
	for ( unsigned int row = 0 ; row < buffer.size() ; row++ ) {
		restoreRegion.Left = tlCorner.X;
		restoreRegion.Top = tlCorner.Y + row;
		restoreRegion.Right = tlCorner.X + width - 1;
		restoreRegion.Bottom = tlCorner.Y + row;

		WriteConsoleOutput( hOut , buffer[row] , { width , 1 } , { 0 , 0 } , &restoreRegion );
	}

	visible = false;
	cursorToggle( hOut , 1 ); //turn cursor back on
}

bool Window::xClicked() {
	if(keyPressed(VK_LBUTTON)&&(mousePos.X <= tlCorner.X + width - 3 and mousePos.X >= tlCorner.X + width - 7 and (mousePos.Y == tlCorner.Y + 1))){
		erase();
		return true;
	}else return false;

	return false;
}

void Window::waitForExit() {
	getMouse(hIn);
	while( !( xClicked() || keyPressed( VK_ESCAPE ) ) ) {
		getMouse(hIn);
	}

	while ( keyPressed( VK_ESCAPE ) ); //waits for user to stop pressing Escape

	erase();
}

void Window::print( std::string message , short line ) {
	if ( line >= 0 && line + 3 < height ) {
		gotoxy( hOut , tlCorner.X + ( width - message.substr( 0 , width - 2 ).length() ) / 2 , tlCorner.Y + line + 3 );
		std::cout << message.substr( 0 , width - 2 );
	}
}

