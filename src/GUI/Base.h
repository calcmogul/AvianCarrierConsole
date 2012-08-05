/*====================
 * Description: Header file that links all of the GUI components.
 * Author: Harrison M.
 * Edit Date: Jan 4, 2012
 * Version: 1.2
 ====================*/

#ifndef GUI_BASE_H_
#define GUI_BASE_H_

#include <windows.h>
#include <iostream>
#include <string>

#include <ConsoleControl.h>
#include <Colors.h>

extern COORD mousePos;
extern INPUT_RECORD records[];

void drawTail( HANDLE hOut );
void getMouse( HANDLE hIn );
bool keyPressed( int key , short value = -1 );
bool keyToggled( int key , short value = -1 );


#endif /* GUI_BASE_H_ */
