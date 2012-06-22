//=============================================================================
//File Name: Tab.cpp
//Description: Holds definitions for Tab class
//Author: Tyler Veness
//Last Modified: 1/16/2012
//Version: 1.0
//=============================================================================

#include "GUI/Tab.h"

HANDLE Tab::hOut = GetStdHandle( STD_OUTPUT_HANDLE );
CONSOLE_SCREEN_BUFFER_INFO Tab::csbi;
short Tab::tabBaseY = TAB_BASE_Y;
std::vector<Tab*> Tab::tabsOpen;
Tab* Tab::current = NULL;

short Tab::tabPos;

Tab::~Tab() {
	std::vector<Tab*>::iterator index;
	for ( index = tabsOpen.begin() ; *index != this ; index++ ) {
		if ( index >= tabsOpen.end() )
			return;
	}
	tabsOpen.erase( index );

	drawTabBase();
	draw();
}

const std::string& Tab::getTitle() {
	return title;
}

void Tab::saveLocal() {
	file.name = title; //update name of file with current tab name

	std::ofstream localFile ( file.name.c_str() );
	Window dialogWin ( 20 , 10 , "" , 20 + file.name.length() , 3 );

	if ( localFile.is_open() ) {
		for ( unsigned int index = 0 ; index < file.input.size() ; index++ )
			localFile << file.input.at( index );

		localFile.close();

		dialogWin.name = "Success:";

		color( hOut , F_BRIGHT_WHITE | B_BLUE );
		dialogWin.redraw();
		dialogWin.print( "\"" + file.name + "\"" + " saved" , 0 );
	}
	else {
		dialogWin.name = "Sorry:";

		color( hOut , F_BRIGHT_WHITE | B_RED );
		dialogWin.redraw();
		dialogWin.print( "Could not open \"" + file.name + "\"" , 0 );
	}

	Sleep( 1000 );
	dialogWin.erase();

	color( hOut , B_BRIGHT_WHITE );
}

void Tab::callSave( Tab*& current ) {
	current->saveLocal();
}

void Tab::drawTabBase() {
	GetConsoleScreenBufferInfo( hOut , &csbi );

	SetConsoleTextAttribute( hOut , F_GRAY );
	gotoxy( hOut , 0 , tabBaseY - 2 );
	for ( short index = 0 ; index < 2 * csbi.dwSize.X ; index++ )
		std::cout << static_cast<char>(0);

	gotoxy( hOut , 0 , tabBaseY );

	for ( int index = 0 ; index < csbi.dwSize.X ; index++ )
		std::cout << static_cast<char>(205); // =
	SetConsoleTextAttribute( hOut , F_BRIGHT_WHITE );
}

void Tab::newTab( std::string fileName ) {
	tabsOpen.push_back( new Tab( fileName ) );
	current = tabsOpen.at( tabsOpen.size() - 1 );
	draw();
	File::clrEditor();
}

void Tab::drawTab() {
	tabStart = tabPos;
	exitPos = tabPos + title.length() + 3;

	color( hOut , F_GRAY );

	gotoxy( hOut , tabPos , tabBaseY );
	std::cout << static_cast<char>(202); // _|_

	gotoxy( hOut , tabPos + tabWidth - 1 , tabBaseY );
	std::cout << static_cast<char>(202); // _|_

	gotoxy( hOut , tabPos , tabBaseY - 1 );
	std::cout << static_cast<char>(186); // ||

	gotoxy( hOut , tabPos + tabWidth - 1 , tabBaseY - 1 );
	std::cout << static_cast<char>(186); // ||

	gotoxy( hOut , tabPos , tabBaseY - 2 );
	std::cout << static_cast<char>(201); // |-

	gotoxy( hOut , tabPos + 1 , tabBaseY - 2 );
	for ( int index = 0 ; index < tabWidth - 2 ; index++ )
		std::cout << static_cast<char>(205); //=

	gotoxy( hOut , tabPos + tabWidth - 1 , tabBaseY - 2 );
	std::cout << static_cast<char>(187); // -|

	/* start drawing tab heading */
	gotoxy( hOut , tabPos + 1 , tabBaseY - 1 );

	if ( current == this ) //else normal color
		color( hOut , B_WHITE );
	else
		color( hOut , F_WHITE );

	std::cout << " " << title << " ";

	if ( current == this )
		color( hOut , F_LIGHT_RED | B_WHITE );
	else
		color( hOut , F_LIGHT_RED );

	std::cout << "x";

	color( hOut , F_WHITE );

	tabPos += tabWidth + 1;
}

void Tab::draw() {
	tabPos = TAB_START_X;

	drawTabBase();
	for ( unsigned int index = 0 ; index < tabsOpen.size() ; index++ )
		tabsOpen.at(index)->drawTab();
}

void Tab::checkAllXClicked() {
	bool redrawTabs = false;
	bool currentChanged = false;

	for ( unsigned int index = 0 ; index < tabsOpen.size() && !redrawTabs ; index++ ) {
		if ( keyPressed( VK_LBUTTON ) && mousePos.X == tabsOpen.at(index)->exitPos && mousePos.Y == TAB_BASE_Y - 1 ) {
			if ( current == tabsOpen.at(index) ) {
				current = tabsOpen[tabsOpen.size() - 2];
				currentChanged = true;
			}

			delete tabsOpen.at(index);
			tabsOpen.erase( tabsOpen.begin() + index );
			redrawTabs = true;
		}
	}

	if ( redrawTabs ) {
		draw();
		std::cout << "redraw worked";
		Sleep( 2000 );
	}
	if ( currentChanged ) {
		current->file.redrawAll();
		std::cout << "redraw worked";
		Sleep( 2000 );
	}
}
