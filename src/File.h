//=============================================================================
//File Name: File.h
//Description: Holds declarations for File class
//Author: Tyler Veness
//=============================================================================

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

#include <SFML/Network.hpp>

#include "ConsoleControl.h"
#include "GUI/Settings.h"
#include "GUI/Window.h"

class File : public sf::Packet {
private:
	static void extendEditor();

public:
	std::string name;
	std::vector<std::string> input;
	COORD cursorPos;
	bool allSelected;
	unsigned int tabCount;
	unsigned int bracketCount;

	static HANDLE hOut;
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	static std::string winTitle;

	static std::vector<File*> filesOpen;
	static sf::Packet fileTransport;
	static sf::IpAddress serverIP;

	File();

	virtual ~File();

	//File& operator= ( const File& );


	//bool open( std::string fileName );

	static void clrLine( short cursorRow );

	template <class T>
	void insert( T newchar ) {
		std::string temp = "";
		temp += newchar;

		if ( allSelected ) {
			input = { temp };
			cursorPos = { static_cast<short>(EDITOR_START_X + 1) , EDITOR_START_Y };

			clrEditor();

			allSelected = false;
		}
		else {
			input.at(cursorPos.Y) = input.at(cursorPos.Y).substr( 0 , cursorPos.X ) + temp + input.at(cursorPos.Y).substr( cursorPos.X , input.at(cursorPos.Y).length() - cursorPos.X );
			cursorPos.X += temp.length();
		}
	}

	friend sf::Packet& operator<<( sf::Packet& fileTransport , const File& sendMe );
	friend sf::Packet& operator>>( sf::Packet& fileTransport , File& receiveMe );

	void addTabSpace( unsigned int tabNum );

	static void clrEditor();

	void redraw( short drawRow );

	void redrawAll();

	void saveLocal();
};

#endif /* FILE_H_ */
