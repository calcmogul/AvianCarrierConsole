//=============================================================================
//File Name: CheckBox.h
//Description: Holds declarations for CheckBox class
//Author: Tyler Veness
//=============================================================================

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
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
