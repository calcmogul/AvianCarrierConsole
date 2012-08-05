//=============================================================================
//File Name: Tab.h
//Description: Holds declarations for Tab class
//Author: Tyler Veness
//=============================================================================

#ifndef TAB_H_
#define TAB_H_

#include <iostream>
#include <string>
#include <vector>

#include "ConsoleControl.h"

#include "Settings.h"
#include "Base.h"
#include "../File.h"

class Tab {
private:
	std::string title;
	short tabStart;
	short tabWidth;
	short exitPos;

	static HANDLE hOut;
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	static short tabBaseY;

	static short tabPos;

	Tab( std::string fileName );

	static void drawTabBase();
	void drawTab();

public:
	File file;
	static std::vector<Tab*> tabsOpen;
	static Tab* current;

	virtual ~Tab();

	const std::string& getTitle();

	void saveLocal();

	static void callSave( Tab*& current );

	static void newTab( std::string fileName = "New File.txt" );

	static void draw();

	static void checkAllXClicked();
};

#endif /* TAB_H_ */
