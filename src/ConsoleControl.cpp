//=============================================================================
//File Name: ConsoleControl.cpp
//Description: Holds definitions for ConsoleControl functions
//Author: Tyler Veness
//=============================================================================

#include "ConsoleControl.h"

void gotoxy( HANDLE hOut , short x , short y ) {
	SetConsoleCursorPosition( hOut , { x , y } );
}

void resizeBuffer( HANDLE hOut , short winX , short winY ) {
	SMALL_RECT buffer_disp = { 0 , 0 , static_cast<short>( winX - 1 ) , static_cast<short>( winY - 1 ) };

	SetConsoleWindowInfo( hOut , TRUE, &buffer_disp ); //resizes window to meet requested buffer size
	SetConsoleScreenBufferSize( hOut , { winX , winY } ); //resizes console screen buffer so scroll bars disappear
}

void maximizeBuffer( HANDLE hOut ) {
	COORD maxSize = GetLargestConsoleWindowSize( hOut );
	resizeBuffer( hOut , maxSize.X , maxSize.Y - 1 );
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE );
}

void cursorToggle( HANDLE hOut , short state ) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo( hOut , &cursorInfo );

	if ( state == -1 )
		cursorInfo.bVisible = !cursorInfo.bVisible;
	if ( state == 0 )
		cursorInfo.bVisible = false;
	if ( state == 1 )
		cursorInfo.bVisible = true;

	SetConsoleCursorInfo( hOut , &cursorInfo );
}

void clrScreen( HANDLE hOut , CONSOLE_SCREEN_BUFFER_INFO* Pcsbi , unsigned int color ) {
	gotoxy( hOut , 0 , 0 );
	GetConsoleScreenBufferInfo( hOut , Pcsbi );
	SetConsoleTextAttribute( hOut , color );

	for ( int row = 0 ; row < Pcsbi->dwSize.Y ; row++ ) {
		for ( int collumn = 0 ; collumn < Pcsbi->dwSize.X ; collumn++ )
			printf( "%c" , 0 );
	}
}
