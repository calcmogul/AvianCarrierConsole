//=============================================================================
//File Name: Button.cpp
//Description: Holds definitions for Button class
//Author: Tyler Veness
//=============================================================================

#include "GUI/Button.h"
#include "Colors.h"

HANDLE Button::hOut = GetStdHandle( STD_OUTPUT_HANDLE );

Button::~Button() {
	if ( visible )
		erase();
	free( buffer );
}

void Button::redraw( short x , short y ) {
	position.X = x;
	position.Y = y;

	restoreRegion.Left = position.X;
	restoreRegion.Top = position.Y;
	restoreRegion.Right = position.X + text.length() + front.length() + back.length() - 1;
	restoreRegion.Bottom = position.Y;

	ReadConsoleOutput( hOut , buffer , { static_cast<short>(text.length() + front.length() + back.length()) , 1 } , { 0 , 0 } , &restoreRegion );

	SetConsoleTextAttribute( hOut , B_GRAY );
	SetConsoleCursorPosition( hOut , { x , y } );
	std::cout << front;
	if ( !useable )
		SetConsoleTextAttribute( hOut , F_WHITE | B_GRAY );
	std::cout << text;
	SetConsoleTextAttribute( hOut , B_GRAY );
	std::cout << back;
	visible = true;

	SetConsoleTextAttribute( hOut , F_BRIGHT_WHITE );
}

bool Button::isHovered() {
	if(visible and mousePos.X >= position.X and ( mousePos.X < static_cast<short>(position.X + text.length() + front.length() + back.length()) and mousePos.Y == position.Y) )
		return true;
	else
		return false;
}

void Button::erase() {
	restoreRegion.Left = position.X;
	restoreRegion.Top = position.Y;
	restoreRegion.Right = position.X + text.length() + front.length() + back.length() - 1;
	restoreRegion.Bottom = position.Y;

	SetConsoleCursorPosition( hOut , position );
	WriteConsoleOutput( hOut , buffer , { static_cast<short>(text.length() + front.length() + back.length()) , 1 } , { 0 , 0 } , &restoreRegion );

	visible = false;
}

void Button::backupEdge() {
	front_b = front;
	back_b = back;
}

void Button::restoreEdge() {
	front = front_b;
	back = back_b;
}
