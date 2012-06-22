//=============================================================================
//File Name: DropDown.cpp
//Description: Holds definitions of DropDown GUI class
//Author: Tyler Veness
//Last Modified: 1/4/2012
//Version: 1.0
//=============================================================================

#include "GUI/Base.h"
#include "GUI/DropDown.h"
#include "GUI/Button.h"

HANDLE DropDown::hOut = GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE DropDown::hIn = GetStdHandle( STD_INPUT_HANDLE );
std::vector<DropDown*> DropDown::dropDowns;

DropDown::DropDown( unsigned int x , unsigned int y , std::vector<Button*> menuList ) {
	position.X = x;
	position.Y = y;
	menu = menuList;
	open = false;

	dropDowns.push_back( this );
}

DropDown::~DropDown() {
	std::vector<DropDown*>::iterator index;
	for ( index = dropDowns.begin() ; *index != this ; index++ ) {
		if ( index >= dropDowns.end() )
			return;
	}

	dropDowns.erase( index );
}

void DropDown::checkAllClicked() {
	for ( unsigned int index = 0 ; index < dropDowns.size() ; index++ )
		dropDowns[index]->checkClicked();
}

bool DropDown::isHovered() {
	if( mousePos.X >= position.X and ( mousePos.X < static_cast<short>(position.X + menu[0]->text.length() + menu[0]->front.length() + menu[0]->back.length()) and mousePos.Y == position.Y) )
		return true;
	else
		return false;
}

bool DropDown::headerClicked() {
	if( keyPressed(VK_LBUTTON) and isHovered() )
		return true;
	else
		return false;
}

void DropDown::checkClicked() {
	if ( headerClicked() ) {
		open = !open;
		draw();

		if ( !isHovered() )
			checkAllClicked();
	}
}

void DropDown::makeVisible() {
	menu[0]->redraw( position.X , position.Y );
}

void DropDown::draw() { //menu is out, so draw options and let user choose
	cursorToggle( hOut , 0 ); //turn cursor off
	menu[0]->useable = true;
	menu[0]->front = static_cast<char>(201); // ,=
	menu[0]->back = static_cast<char>(187); // =,

	std::string temp = "";

	if ( menu.size() > 0 ) {
		for ( unsigned int index = 0 ; index < menu[1]->text.length() ; index++ )
			temp += static_cast<char>(205); // =
	}

	/* === Add top and bottom of DropDown menu === */
	menu.insert( menu.begin() + 1 , new Button( "" , static_cast<char>(201) /* |- */ + temp + static_cast<char>(187) /* -| */ , "" , NULL , true ) );
	menu.push_back( new Button( "" , static_cast<char>(200) /* |_ */ + temp + static_cast<char>(188) /* _| */ , "" , NULL , true ) );
	/* =========================================== */

	for ( unsigned int index = 2 ; index < menu.size() - 1 ; index++ ) { //draws all options for user
		menu[index]->backupEdge();
		menu[index]->front = static_cast<char>(186); // ||
		menu[index]->back = static_cast<char>(186); // ||
	}
	for ( unsigned int index = 0 ; index < menu.size() ; index++ )
		menu[index]->redraw(position.X , position.Y + index);

	/* === Merge Top Button with Rest of DropDown Menu === */
	color( hOut , B_GRAY );
	gotoxy( hOut , position.X , position.Y + 1 );
	std::cout << static_cast<char>(204); // ||=
	gotoxy( hOut , position.X + menu[0]->text.length() + menu[0]->back.length() , position.Y + 1 );
	std::cout << static_cast<char>(202); // _|_
	/* =================================================== */

	unsigned int hoverCount;
	while(open) { //if open, wait for user to press menu options
		getMouse(hIn);

		hoverCount = 0;
		for ( unsigned int index = 0 ; open && index < menu.size() ; index++ ) {
			if ( menu[index]->isHovered() && index != 0 ) { //if hovering over button other than the menu's main button
				hoverCount++;

				if ( keyPressed( VK_LBUTTON ) && menu[index]->useable && menu[index]->func != NULL ) {
					menu[index]->func();
					open = false;
				}
			}
		}

		if ( ( keyPressed( VK_LBUTTON ) && hoverCount == 0 ) || keyPressed( VK_ESCAPE ) )
			open = false;
		while ( keyPressed( VK_ESCAPE ) ); //waits for enter to be released so program won't exit right away
	}

	for ( unsigned index = 2 ; index < menu.size() - 1 ; index++ ) {
		menu[index]->erase();

		menu[index]->restoreEdge();
		menu[index]->front = static_cast<char>(186);
		menu[index]->back = static_cast<char>(186);
	}

	delete menu[1];
	menu.erase( menu.begin() + 1 );
	delete menu[menu.size() - 1];
	menu.erase( menu.end() - 1 );

	menu[0]->useable = false;
	menu[0]->front = static_cast<char>(169); // ,-
	menu[0]->back = static_cast<char>(170); // -,

	menu[0]->redraw( position.X , position.Y );
	cursorToggle( hOut , 1 ); //turn cursor back on
}
