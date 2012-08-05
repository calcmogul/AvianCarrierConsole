//=============================================================================
//File Name: Base.cpp
//Description: Holds utility functions
//Author: Tyler Veness
//=============================================================================

#include "GUI/Base.h"

COORD mousePos;

INPUT_RECORD records[1];
DWORD eventsRead;
MOUSE_EVENT_RECORD mouse;

bool keyPressed( int key , short value ) {
	if ( value == -1 )
		return ( GetKeyState( key ) & 1 << 16 ) != 0;
	else
		return ( value & 1 << 16 ) != 0;
}

bool keyToggled( int key , short value ) {
	if ( value == -1 )
		return ( GetKeyState( key ) & 1 ) != 0;
	else
		return ( value & 1 ) != 0;
}

void getMouse( HANDLE hIn ) {
	ReadConsoleInput( hIn , records , 1 , &eventsRead );
	if (records[0].EventType == MOUSE_EVENT) {
		mouse = records[0].Event.MouseEvent;
		mousePos.X = records[0].Event.MouseEvent.dwMousePosition.X;
		mousePos.Y = records[0].Event.MouseEvent.dwMousePosition.Y;
	}
}

void drawTail( HANDLE hOut ) {
	gotoxy( hOut , 5 , 7 );
	std::cout << "|||";
}
