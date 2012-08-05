//=============================================================================
//File Name: MainEditor.cpp
//Description: Handles main editor and window
//Author: Tyler Veness
//=============================================================================

//TODO: IMPORTANT Fix right arrow key not moving to next line down occasionally

//TODO: Fix Ctrl + A flag
//TODO: Hotkey for "Pull" ; Ctrl + P
//TODO: Implement saving to file with Ctrl + S
//TODO: Implement copying and pasting to clipboard
//TODO: Implement text selection with highlighting

//TODO: Text Fields

//TODO: Make auto-tabbing work correctly when brackets are erased

#include <iostream>

#include "ConsoleControl.h"
#include "Colors.h"
#include "File.h"
#include "GUI/Tab.h"
#include "GUI/Base.h"
#include "GUI/Button.h"
#include "GUI/DropDown.h"
#include "GUI/Graphics.h"
#include "GUI/Toolbar.h"
#include "GUI/Window.h"

/*template <class T>
void debug( const char* message , T& num ) {
	gotoxy( GetStdHandle( STD_OUTPUT_HANDLE ) , 0 , 20 );
	std::cout << message << "=" << num;
}*/

/*void dispLine( std::string line ) { //TEST FUNCTION
	for ( unsigned int index = 0 ; index < line.length() ; index++ ) {
		if ( line.substr( index , 1 ) != "\n" )
			std::cout << line.substr( index , 1 );
		else
			std::cout << "\\n";
	}
	Sleep( 2000 ); //TEST
}*/

HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE hIn = GetStdHandle( STD_INPUT_HANDLE );
CONSOLE_SCREEN_BUFFER_INFO csbi;

int main() {
	char currentDirectory[GetCurrentDirectoryA( 0 , NULL )];
	GetCurrentDirectoryA( sizeof(currentDirectory) , currentDirectory );
	SetCurrentDirectoryA( strcat( currentDirectory , "\\Resource" ) );

	//sf::Console debug( 80 , 25 , "Debug Output" , "lucon.ttf" );
	//sf::Event event;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hOut , &csbi );

	maximizeBuffer( hOut );

	SetConsoleTitle( "Avian Carrier - Spartatroniks Software Team" );
	SetConsoleTextAttribute( hOut , F_BRIGHT_WHITE );

	SetConsoleCtrlHandler( NULL , TRUE ); //stops Ctrl + C from closing program

	INPUT_RECORD records[1];
	DWORD eventsRead;
	MOUSE_EVENT_RECORD mouse;
	KEY_EVENT_RECORD key;

	/* === GUI Components === */
	Toolbar upperBranch ( 5 , static_cast<char>(205) );
	Toolbar lowerBranch ( 7 , static_cast<char>(205) );
	Graphics bird ( 0 , 0 , "" , 0 );

	Button file( static_cast<char>(169) /* ,- */ , "File" , static_cast<char>(170) /* -, */ );
	Button newFile( "(|" , " New      Ctrl + N " , "|)" , []{ Tab::newTab(); } , true );
	Button open( "(|" , " Open     Ctrl + O " , "|)" );
	Button save( "(|" , " Save     Ctrl + S " , "|)" , []{ Tab::callSave( Tab::current ); } , false );
	Button pull( "(|" , " Pull     Ctrl + P " , "|)" );

	Button edit( static_cast<char>(169) /* ,- */ , "Edit" , static_cast<char>(170) /* -, */ );
	Button undo( "(|" , " Undo     Ctrl + Z " , "|)" );
	Button redo( "(|" , " Redo     Ctrl + Y " , "|)" );
	Button cut( "(|" , " Cut      Ctrl + X " , "|)" );
	Button copy( "(|" , " Copy     Ctrl + C " , "|)" );
	Button paste( "(|" , " Paste    Ctrl + V " , "|)" );

	Button options( "(|" , "Options" , "|)" , []{ Tab::newTab(); } , true );

	DropDown fileMenu ( 18 , 6 , { &file , &newFile , &open , &save , &pull } );
	DropDown editMenu ( 26 , 6 , { &edit , &undo , &redo , &cut , &copy , &paste } );

	fileMenu.makeVisible();
	editMenu.makeVisible();

	bird.redraw();
	upperBranch.redraw();
	lowerBranch.redraw();
	drawTail(hOut);

	/*window welcome(20, 10, "Welcome:", 31, 6);
	welcome.redrawWindow();

	welcome.printToWindow("Welcome to Avian Carrier!", 0);
	welcome.printToWindow("AC v1.5 alpha", 1);

	waitForExit(welcome);*/
	/* ====================== */

	Tab::draw();

	do {
		/*while ( debug.IsOpened() ) {
			while ( debug.GetEvent( event ) ) {
				if ( event.Type == sf::Event::Closed )
					debug.Close();
			}
		}*/

		ReadConsoleInput( hIn , records , 1 , &eventsRead );

		if ( records[0].EventType == MOUSE_EVENT ) {
			mousePos = records[0].Event.MouseEvent.dwMousePosition;
			mouse = records[0].Event.MouseEvent;
		}

		if ( records[0].EventType == MOUSE_EVENT ) {
			/*if ( ( mouse.dwButtonState & 1 ) != 0 ) { //if left click
				if ( File::filesOpen.size() > 0 ) {
					if ( mouse.dwMousePosition.Y >= EDITOR_START_Y ) { //if user won't destroy UI by clicking there
						myfile.file.cursorCoord.X = static_cast<unsigned int>(mouse.dwMousePosition.X) > myfile.file.input.at(mouse.dwMousePosition.Y - 5).length() ? mouse.dwMousePosition.X : myfile.file.input.at(mouse.dwMousePosition.Y - 5).length(); //if cursor is
						myfile.file.cursorCoord.Y = static_cast<unsigned int>(mouse.dwMousePosition.Y) > myfile.file.input.size() + 5 ? mouse.dwMousePosition.Y : myfile.file.input.size() + 5;
						SetConsoleCursorPosition( hOut , myfile.file.cursorCoord );
					}
				}
			}*/
		}

		DropDown::checkAllClicked();
		Tab::checkAllXClicked();

		if ( File::filesOpen.size() > 0 )
			gotoxy( hOut , EDITOR_START_X + Tab::current->file.cursorPos.X , EDITOR_START_Y + Tab::current->file.cursorPos.Y );
		else
			cursorToggle( hOut , 0 );

		if ( records[0].EventType == KEY_EVENT && records[0].Event.KeyEvent.bKeyDown ) { //if user pressed (not released) key
			key = records[0].Event.KeyEvent;

			if ( File::filesOpen.size() > 0 ) {
				save.useable = true;

				if ( keyPressed( VK_BACK ) ) { //pressed Backspace
					if ( Tab::current->file.cursorPos.Y > 0 || Tab::current->file.cursorPos.X > 0 ) { //and cursor isn't at beginning of doc

						if ( Tab::current->file.cursorPos.X == 0 ) { //if a newline will be erased
							Tab::current->file.cursorPos.X = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - 1; //move cursor to where it would be after line merging is done
							Tab::current->file.input.at(Tab::current->file.cursorPos.Y - 1) += Tab::current->file.input.at(Tab::current->file.cursorPos.Y); //since newline was eliminated, move contents of that line to line before it

							Tab::current->file.input.erase( Tab::current->file.input.begin() + Tab::current->file.cursorPos.Y ); //erase the line now that the content is moved

							for ( short index = Tab::current->file.cursorPos.Y ; static_cast<unsigned int>(index) < Tab::current->file.input.size() ; index++ ) { //redraw all lines below line currently erased
								File::clrLine( index );
								Tab::current->file.redraw( index );
							}
							File::clrLine( Tab::current->file.input.size() ); //erase leftover line of garbage after last line in file

							Tab::current->file.cursorPos.Y--;
							Tab::current->file.cursorPos.X = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - 1;
						}
						else { //otherwise do normal character deletion
							if ( Tab::current->file.cursorPos.X >= 4 ) {
								if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 4 , 4 ) == "    " ) { //if there is a tab to the right
									Tab::current->file.input.at(Tab::current->file.cursorPos.Y) = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( 0 , Tab::current->file.cursorPos.X - 4 ) + Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - Tab::current->file.cursorPos.X );
									Tab::current->file.cursorPos.X -= 4;
								}
								else {
									if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 1 , 1 ) == "{" )
										Tab::current->file.bracketCount--;
									if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 1 , 1 ) == "}" )
										Tab::current->file.bracketCount++;

									Tab::current->file.input.at(Tab::current->file.cursorPos.Y) = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( 0 , Tab::current->file.cursorPos.X - 1 ) + Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - Tab::current->file.cursorPos.X );
									Tab::current->file.cursorPos.X--;
								}
							}
							else {
								if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 1 , 1 ) == "{" )
									Tab::current->file.bracketCount--;
								if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 1 , 1 ) == "}" )
									Tab::current->file.bracketCount++;

								Tab::current->file.input.at(Tab::current->file.cursorPos.Y) = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( 0 , Tab::current->file.cursorPos.X - 1 ) + Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - Tab::current->file.cursorPos.X );
								Tab::current->file.cursorPos.X--;
							}

							File::clrLine( Tab::current->file.cursorPos.Y );
						}
					}
				}

				else if ( keyPressed( VK_RETURN ) ) { //pressed Enter
					Tab::current->file.input.insert( Tab::current->file.input.begin() + Tab::current->file.cursorPos.Y + 1 , "\n" ); //add new line to file
					Tab::current->file.input.at(Tab::current->file.cursorPos.Y + 1) += Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - Tab::current->file.cursorPos.X - 2 ); //add segment to next line
					Tab::current->file.input.at(Tab::current->file.cursorPos.Y) = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( 0 , Tab::current->file.cursorPos.X ); //delete leftovers from old line

					Tab::current->file.cursorPos.X = 0; //move cursor to beginning of next row
					Tab::current->file.cursorPos.Y++; //move cursor to next line

					Tab::current->file.addTabSpace( Tab::current->file.tabCount );

					/* === Add Closing Brace if Needed === */
					COORD tempPos = Tab::current->file.cursorPos;

					if ( Tab::current->file.tabCount > 0 && Tab::current->file.bracketCount > 0 ) {
						Tab::current->file.tabCount--;
						Tab::current->file.input.insert( Tab::current->file.input.begin() + Tab::current->file.cursorPos.Y + 1 , "\n" ); //add new line to file
						Tab::current->file.addTabSpace( Tab::current->file.tabCount );

						Tab::current->file.cursorPos.X = 0;
						Tab::current->file.cursorPos.Y++;

						Tab::current->file.insert( "}" );
						Tab::current->file.tabCount++;
						Tab::current->file.bracketCount--;
					}

					Tab::current->file.cursorPos = tempPos;
					/* =================================== */

					for ( unsigned int row = Tab::current->file.cursorPos.Y ; row < Tab::current->file.input.size() ; row++ )
						Tab::current->file.redraw( row );

					File::clrLine( Tab::current->file.cursorPos.Y - 1 ); //clears line for redrawing in case some of the text was moved to line below
					Tab::current->file.redraw( Tab::current->file.cursorPos.Y - 1 ); //redraw line erased
				}

				else if ( keyPressed( VK_TAB ) ) {
					Tab::current->file.insert( "    " );
				}

				else if ( keyPressed( VK_HOME ) )
					Tab::current->file.cursorPos.X = 0;

				else if ( keyPressed( VK_END ) )
					Tab::current->file.cursorPos.X = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - 2;

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x41 ) ) { //pressed Ctrl + A
					Tab::current->file.allSelected = true;
				}

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x53 ) ) { //pressed Ctrl + S
					Tab::current->saveLocal();
				}

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x4E ) ) { //pressed Ctrl + N
					Tab::newTab();
				}

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x4F ) ) { //pressed Ctrl + O
					//SELECTION WINDOW GUI CALL - NAME GOES DOWN THERE v
					Tab::newTab( "Newer File.txt" );
				}

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x43 ) ) { //pressed Ctrl + C

				}

				else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x56 ) ) { //pressed Ctrl + V

				}

				else if ( keyPressed( VK_RIGHT ) ) {
					if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , 4 ) == "    " ) //if there is a tab to the right
						Tab::current->file.cursorPos.X += 4;

					else if ( Tab::current->file.cursorPos.X < static_cast<short>(Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - 1) ) //if cursor isn't at end of row, move it normally
						Tab::current->file.cursorPos.X++;

					else if ( Tab::current->file.cursorPos.Y < static_cast<short>(Tab::current->file.input.size() - 1) && Tab::current->file.cursorPos.X == static_cast<short>(Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - 1) ) { //if there is another row beneath and the cursor is at end or row, move cursor to beginning of next row
						Tab::current->file.cursorPos.X = 0;
						Tab::current->file.cursorPos.Y++;
					}
				}

				else if ( keyPressed( VK_LEFT ) ) {
					if ( Tab::current->file.cursorPos.X >= 4 ) {
						if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 4 , 4 ) == "    " ) //if there is a tab to the right
							Tab::current->file.cursorPos.X -= 4;
						else
							Tab::current->file.cursorPos.X--;
					}

					else if ( Tab::current->file.cursorPos.X > 0 )
						Tab::current->file.cursorPos.X--;

					else if ( Tab::current->file.cursorPos.Y > 0 && Tab::current->file.cursorPos.X == 0 ) { //if there is a row above and cursor is at beginning of row, move cursor to end of previous row
						Tab::current->file.cursorPos.Y--;
						Tab::current->file.cursorPos.X = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length();
					}
				}

				else if ( keyPressed( VK_DOWN ) || keyPressed( VK_UP ) ) {
					//gotoxy( hOut , 0 , 20 );std::cout << "went up or down";Sleep(1000); //TEST
					Tab::current->file.cursorPos.Y = Tab::current->file.cursorPos.Y + keyPressed( VK_DOWN ) - keyPressed( VK_UP );
					Tab::current->file.cursorPos.Y = Tab::current->file.cursorPos.Y - ( static_cast<unsigned int>(Tab::current->file.cursorPos.Y) >=Tab::current->file.input.size() ) + ( Tab::current->file.cursorPos.Y < 0 );

					if ( static_cast<unsigned int>(Tab::current->file.cursorPos.X) > Tab::current->file.input[Tab::current->file.cursorPos.Y].length() )
						Tab::current->file.cursorPos.X = Tab::current->file.input[Tab::current->file.cursorPos.Y].length();
				}

				else if ( static_cast<int>(key.uChar.AsciiChar) == 0 ) {}

				else if ( static_cast<int>(key.uChar.AsciiChar) == 27 ) {} //pressed Escape

				else if ( keyPressed( VK_CONTROL ) ) {} //prevents other control signals from being printed into document

				else if ( keyPressed( VK_MENU ) ) {} //prevents alt signals from being printed into document


				else if ( static_cast<int>(key.uChar.AsciiChar) == 123 ) { //pressed {
					Tab::current->file.tabCount++;
					Tab::current->file.bracketCount++;
					Tab::current->file.insert( key.uChar.AsciiChar );
				}

				else if ( static_cast<int>(key.uChar.AsciiChar) == 125 ) { //pressed }
					if ( Tab::current->file.tabCount > 0 ) {
						Tab::current->file.tabCount--;
						Tab::current->file.bracketCount--;

						if ( Tab::current->file.cursorPos.X >= 4 ) {
							if ( Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X - 4 , 4 ) == "    " ) {
								Tab::current->file.input.at(Tab::current->file.cursorPos.Y) = Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( 0 , Tab::current->file.cursorPos.X - 4 ) + Tab::current->file.input.at(Tab::current->file.cursorPos.Y).substr( Tab::current->file.cursorPos.X , Tab::current->file.input.at(Tab::current->file.cursorPos.Y).length() - Tab::current->file.cursorPos.X );
								Tab::current->file.cursorPos.X -= 4;
							}

						}
					}
					Tab::current->file.insert( key.uChar.AsciiChar );
				}

				else {
					Tab::current->file.insert( key.uChar.AsciiChar );
				}

				Tab::current->file.redraw( Tab::current->file.cursorPos.Y );
			}
			else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x4E ) ) { //pressed Ctrl + N
				Tab::newTab();

				cursorToggle( hOut , 1 );
			}

			else if ( keyPressed( VK_CONTROL ) && keyPressed( 0x4F ) ) { //pressed Ctrl + O
				//SELECTION WINDOW GUI CALL - NAME GOES DOWN THERE v
				Tab::newTab( "Newer File.txt" );

				cursorToggle( hOut , 1 );
			}
			else
				save.useable = false;
		}
	} while ( !keyPressed( VK_ESCAPE ) );

	return 0;
}
