//=============================================================================
//File Name: CheckBox.h
//Description: Holds declarations for CheckBox class
//Author: Tyler Veness
//Last Modified: 1/24/2012
//Version: 1.0
//=============================================================================

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <windows.h>

class CheckBox {
private:
	COORD pos;

public:
	bool isChecked;
	bool visible;

	CheckBox( short x , short y , bool on = false , bool see = false );
};

#endif /* CHECKBOX_H_ */
