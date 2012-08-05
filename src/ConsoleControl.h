//=============================================================================
//File Name: ConsoleControl.h
//Description: Holds declarations for ConsoleControl functions
//Author: Tyler Veness
//=============================================================================

#ifndef CONSOLECONTROL_H_
#define CONSOLECONTROL_H_

#include <cstdio>

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void gotoxy( HANDLE hOut , short x , short y );

void resizeBuffer( HANDLE hOut , short winX , short winY );

void maximizeBuffer( HANDLE hOut );

void cursorToggle( HANDLE hOut , short state = -1 ); //-1 is toggle ; 0 is off ; 1 is on

void clrScreen( HANDLE hOut , CONSOLE_SCREEN_BUFFER_INFO* Pcsbi , unsigned int color = 0x07 );

#endif /* CONSOLECONTROL_H_ */
