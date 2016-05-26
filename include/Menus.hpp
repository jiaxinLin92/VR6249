#pragma once

#include "SceneObject.hpp"

class GameManager;


class Menus : public SceneObject {
public:

	// code found at: https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html#6
	struct Mouse
	{
		int x;		/*	the x coordinate of the mouse cursor	*/
		int y;		/*	the y coordinate of the mouse cursor	*/
		int lmb;	/*	is the left button pressed?		*/
		int mmb;	/*	is the middle button pressed?	*/
		int rmb;	/*	is the right button pressed?	*/

					/*
					*	These two variables are a bit odd. Basically I have added these to help replicate
					*	the way that most user interface systems work. When a button press occurs, if no
					*	other button is held down then the co-ordinates of where that click occured are stored.
					*	If other buttons are pressed when another button is pressed it will not update these
					*	values.
					*
					*	This allows us to "Set the Focus" to a specific portion of the screen. For example,
					*	in maya, clicking the Alt+LMB in a view allows you to move the mouse about and alter
					*	just that view. Essentually that viewport takes control of the mouse, therefore it is
					*	useful to know where the first click occured....
					*/
		int xpress; /*	stores the x-coord of when the first button press occurred	*/
		int ypress; /*	stores the y-coord of when the first button press occurred	*/
	};

	//rename the structure from "struct Mouse" to just "Mouse"
	typedef struct Mouse Mouse;


	//Create a global mouse structure to hold the mouse information.
	Mouse TheMouse = { 0,0,0,0,0 };


	//Variables to hold the current size of the window.
	int winW;
	int winH;

	//This is a simple structure that holds a button.
	struct Button
	{
		int   x;							/* top left x coord of the button */
		int   y;							/* top left y coord of the button */
		int   w;							/* the width of the button */
		int   h;							/* the height of the button */
		int	  state;						/* the state, 1 if pressed, 0 otherwise */
		int	  highlighted;					/* is the mouse cursor over the control? */
		char* label;						/* the text label of the button */
		int id;
	};
	typedef struct Button Button;


	void Font(void *font, char *text, int x, int y), ButtonRelease(Button *b, int x, int y),
		ButtonPress(Button *b, int x, int y), ButtonPassive(Button *b, int x, int y),
		ButtonDraw(Button *b), Draw2D(), MouseButton(int button, int state, int x, int y),
		MouseMotion(int x, int y), MousePassiveMotion(int x, int y);
	int ButtonClickTest(Button* b, int x, int y);

	void setWindow(int window);

	Menus(std::shared_ptr<GameManager> gm);
	~Menus();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	std::shared_ptr<GameManager> gm_;
	int window_;

	Button butStart_, butHow_, butEnd_;

};