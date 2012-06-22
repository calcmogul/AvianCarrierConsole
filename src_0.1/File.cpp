//=============================================================================
//File Name: File.cpp
//Description: Holds definitions for File class
//Author: Tyler Veness
//Last Modified: 1/16/2012
//Version: 1.0
//=============================================================================

#include "File.h"

HANDLE File::hOut = GetStdHandle( STD_OUTPUT_HANDLE );
CONSOLE_SCREEN_BUFFER_INFO File::csbi;
std::string File::winTitle = "Avian Carrier v1.0 - Spartatroniks Programming Team";

std::vector<File*> File::filesOpen;
sf::Packet File::fileTransport;
sf::IpAddress File::serverIP( "12.34.56.789" );

File::File() {
	input.push_back( "\n" );
	cursorPos = { 0 , 0 };
	allSelected = false;
	filesOpen.push_back( this );
	tabCount = 0;
	bracketCount = 0;
}

File::~File() {
	std::vector<File*>::iterator index;
	for ( index = filesOpen.begin() ; *index != this ; index++ ) {
		if ( index >= filesOpen.end() )
			return;
	}
	//TELL SERVER TO STOP SENDING UPDATED FILE
	filesOpen.erase( index );
}

/*File& File::operator= ( const File& param ) {
	if ( this != &param ) {
		name = param.name;
		input = param.input;
		cursorCoord = param.cursorCoord;
		allSelected = param.allSelected;
		tabCount = param.tabCount;
		//copies all other objects except: ios_base mode
	}
	return *this;
}*/

/*bool File::open( std::string fileName ) {
	open( fileName.c_str() );

	if ( !file.is_open() ) {
		std::cout << "FAILED...";
		return false;
	}
	else
		return true;
}*/

sf::Packet& operator<<( sf::Packet& fileTransport , const File& sendMe ) {
	for ( unsigned int index = 0 ; index < sendMe.input.size() ; index++ ) {
		std::cout << "Adding '" << sendMe.input[index] << "'\n";
		fileTransport << sendMe.input[index];
	}

	return fileTransport;
}

sf::Packet& operator>>( sf::Packet& fileTransport , File& receiveMe ) {
	for ( unsigned int index = 0 ; !fileTransport.endOfPacket() ; index++ ) {
		std::cout << "Receiving '" << fileTransport << "'\n";
		fileTransport >> receiveMe.input[index];
	}

	return fileTransport;
}

void File::clrLine( short cursorRow ) {
	GetConsoleScreenBufferInfo( hOut , &csbi );
	color( hOut , B_BRIGHT_WHITE );

	gotoxy( hOut , PAGE_START_X , EDITOR_START_Y + cursorRow );
	for ( long long collumn = PAGE_START_X ; collumn < csbi.dwSize.X - PAGE_START_X ; collumn++ )
		std::cout << " ";
}

void File::clrEditor() {
	GetConsoleScreenBufferInfo( hOut , &csbi );
	color( hOut , B_BRIGHT_WHITE );

	for ( long long row = PAGE_START_Y ; row < csbi.dwSize.Y ; row++ ) {
		gotoxy( hOut , PAGE_START_X , row );
		for ( long long collumn = PAGE_START_X ; collumn < csbi.dwSize.X - PAGE_START_X ; collumn++ )
			std::cout << " ";
	}

	gotoxy( hOut , EDITOR_START_X , EDITOR_START_Y );
}

void File::extendEditor() {

}

void File::addTabSpace( unsigned int tabNum ) {
	for ( unsigned int index = 0 ; index < tabNum ; index++ )
		insert( "    " );
}

void File::redraw( short drawRow ) {
	color( hOut , B_BRIGHT_WHITE );
	gotoxy( hOut , EDITOR_START_X , static_cast<short>(EDITOR_START_Y + drawRow) );
	std::cout << input.at(drawRow);

	gotoxy( hOut , EDITOR_START_X + cursorPos.X , static_cast<short>(EDITOR_START_Y + cursorPos.Y) );
}

void File::redrawAll() {
	for ( unsigned int index = 0 ; index < input.size() ; index++ )
		redraw( index );
}
