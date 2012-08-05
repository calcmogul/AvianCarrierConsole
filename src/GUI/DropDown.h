//=============================================================================
//File Name: DropDown.h
//Description: Holds declarations of DropDown GUI class
//Author: Tyler Veness
//=============================================================================

#ifndef GUI_DROPDOWN_H_
#define GUI_DROPDOWN_H_

#include <vector>

#include "Base.h"
#include "Button.h"

class DropDown {
private:
	COORD position;
	std::vector<Button*> menu;
	bool open;

	static HANDLE hOut;
	static HANDLE hIn;

	void checkClicked();
	bool headerClicked();
	void draw();

public:
	static std::vector<DropDown*> dropDowns;

	DropDown( unsigned int x , unsigned int y , std::vector<Button*> );
	~DropDown();

	void makeVisible();

	bool isHovered();
	static void checkAllClicked();
};

#endif /* GUI_DROPDOWN_H_ */
