//=============================================================================
//File Name: Tab.h
//Description: Holds declarations for Tab class
//Author: Tyler Veness
//Last Modified: 1/16/2012
//Version: 1.0
//=============================================================================

#ifndef TAB_H_
#define TAB_H_

#include <iostream>
#include <string>
#include <vector>

#include <ConsoleControl.h>
#include <Colors.h>

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

	Tab( std::string fileName ) {
		title = fileName;
		tabWidth = title.length() + 5; // length of title + 2 on each side for spacing and tab edge = (4) + 1 for red X
		tabStart = TAB_START_X;
	}

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
