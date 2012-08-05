//=============================================================================
//File Name: Window.h
//Description: Holds declarations for Window class
//Author: Tyler Veness
//=============================================================================

#ifndef acguiwindow
#define acguiwindow

#include "Base.h"
#include <vector>

class Window {
private:
	COORD tlCorner;
	std::string name;
	short width;
	short height;

	bool visible;

	std::vector<CHAR_INFO*> buffer;
	SMALL_RECT restoreRegion;

	static HANDLE hOut;
	static HANDLE hIn;

	friend class Tab;

public:
	Window( int xPos , int yPos , std::string title , int xlength , int ylength );
	~Window();

	bool setTitle( std::string );
	void redraw();
	void erase();
	bool xClicked();
	void waitForExit();
	void print( std::string message , short line );
};


#endif //acguiwindow
