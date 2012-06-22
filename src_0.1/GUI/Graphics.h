/*====================
 * Description: The GUI graphics component
 * Author: Harrison M.
 * Edit Date: Jan 4, 2012
 * Version: 
 ====================*/

#ifndef GUI_GRAPHICS_H_
#define GUI_GRAPHICS_H_

#include "Base.h"

class Graphics {
private:
	int xPos;
	int yPos;
	std::string caption;
	int graphic;

	static HANDLE hOut;

public:
	Graphics( int xPosition , int yPosition , std::string wording , int pic );

	void redraw();
	void choose( int pic );
};


#endif /* GUI_GRAPHICS_H_ */
