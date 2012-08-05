//=============================================================================
//File Name: CheckBox.cpp
//Description: Holds definitions for CheckBox class
//Author: Tyler Veness
//=============================================================================

#include "GUI/CheckBox.h"

CheckBox::CheckBox( short x , short y , bool on , bool see ) {
	pos.X = x;
	pos.Y = y;
	isChecked = on;
	visible = see;
}
