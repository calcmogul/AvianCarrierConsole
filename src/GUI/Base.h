//=============================================================================
//File Name: Base.h
//Description: Contains utility functions
//Author: Tyler Veness
//=============================================================================

#ifndef GUI_BASE_H_
#define GUI_BASE_H_

#include <iostream>
#include <string>

#include "ConsoleControl.h"

extern COORD mousePos;
extern INPUT_RECORD records[];

void drawTail( HANDLE hOut );
void getMouse( HANDLE hIn );
bool keyPressed( int key , short value = -1 );
bool keyToggled( int key , short value = -1 );


#endif /* GUI_BASE_H_ */
