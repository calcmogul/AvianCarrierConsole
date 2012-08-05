//=============================================================================
//File Name: Toolbar.h
//Description: Holds declarations for Toolbar class
//Author: Tyler Veness
//=============================================================================

#ifndef GUI_TOOLBAR_H_
#define GUI_TOOLBAR_H_

#include "Base.h"

class Toolbar {
private:
	int cursorRow;
	char character;

public:
	static HANDLE hOut;
	static CONSOLE_SCREEN_BUFFER_INFO csbi;

	Toolbar( int row , char newchar );

	void redraw();
};


#endif /* GUI_TOOLBAR_H_ */
