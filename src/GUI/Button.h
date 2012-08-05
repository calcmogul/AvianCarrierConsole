/*====================
 * Description: The GUI Button Component.
 * Author: Harrison M.
 * Edit Date: Jan 4, 2012
 * Version: 1.3
 ====================*/

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include "Base.h"
#include <cstdlib>

class Button {
private:
	COORD position;
	bool visible;

	CHAR_INFO* buffer;
	SMALL_RECT restoreRegion;

	static HANDLE hOut;

public:
	std::string front;
	std::string text;
	std::string back;

	std::string front_b;
	std::string back_b;

	bool useable;
	void (*func)();

	template<class T>
	Button( T lEdge , std::string message , T rEdge , void (*operation)() = NULL , bool use = false ) {
		front = lEdge;
		text = message;
		back = rEdge;

		front_b = "";
		back_b = "";

		useable = use;
		visible = false;

		func = operation;
		buffer = static_cast<CHAR_INFO*>( calloc( front.length() + text.length() + back.length() , sizeof(CHAR_INFO) ) );
	}

	virtual ~Button();

	void redraw( short x , short y );
	bool isHovered();
	void erase();

	void backupEdge();
	void restoreEdge();
};


#endif /* GUI_BUTTON_H_ */
