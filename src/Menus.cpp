#include "Menus.hpp"
#include "GameManager.hpp"

Menus::Menus(std::shared_ptr<GameManager> gm) {
	gm_ = gm;

	winW = glutGet(GLUT_WINDOW_WIDTH);
	winH = glutGet(GLUT_WINDOW_HEIGHT);
	butStart_ = { 200, 200, 200, 50, 0, 40, "Start game", 0 };
	butHow_ = { 0, 0, 0, 0, 0, 0, "  ", 1 };
	butEnd_ = { 200, 250, 200, 50, 0, 40, "End game", 1 };
}

Menus::~Menus() {
}

void Menus::privateInit() {
}

void Menus::privateRender() {

	if (gm_->shouldMenuBeShown()) {
		//Disable depth test and lighting for 2D elements
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, winW, winH, 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Draw the 2D overlay
		Draw2D();

		//Enable depth test and lighting for 2D elements
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		//Set the orthographic viewing transformation
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, float(winW) / float(winH), 0.5f, 2000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}


void Menus::privateUpdate() {
	winW = glutGet(GLUT_WINDOW_WIDTH);
	winH = glutGet(GLUT_WINDOW_HEIGHT);
}


// code found at: https://nccastaff.bournemouth.ac.uk/jmacey/RobTheBloke/www/opengl_programming.html#6
/*----------------------------------------------------------------------------------------
*	\brief	This function draws a text string to the screen using glut bitmap fonts.
*	\param	font	-	the font to use. it can be one of the following :
*
*					GLUT_BITMAP_9_BY_15
*					GLUT_BITMAP_8_BY_13
*					GLUT_BITMAP_TIMES_ROMAN_10
*					GLUT_BITMAP_TIMES_ROMAN_24
*					GLUT_BITMAP_HELVETICA_10
*					GLUT_BITMAP_HELVETICA_12
*					GLUT_BITMAP_HELVETICA_18
*
*	\param	text	-	the text string to output
*	\param	x		-	the x co-ordinate
*	\param	y		-	the y co-ordinate
*/
void Menus::Font(void *font, char *text, int x, int y) {
	glRasterPos2i(x, y);

     while (*text != '\0') {
		glutBitmapCharacter(font, *text);
		++text;
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is used to see if a mouse click or event is within a button
*			client area.
*	\param	b	-	a pointer to the button to test
*	\param	x	-	the x coord to test
*	\param	y	-	the y-coord to test
*/
int Menus::ButtonClickTest(Button* b, int x, int y) {
	if (b) {
		//If clicked within button area, then return true
		if (x > b->x      &&
			x < b->x + b->w &&
			y > b->y      &&
			y < b->y + b->h) {
			return 1;
		}
	}
	//otherwise false.
	return 0;
}
/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void Menus::ButtonRelease(Button *b, int x, int y) {
	if (b) {
		/*
		*	If the mouse button was pressed within the button area
		*	as well as being released on the button.....
		*/
		if (ButtonClickTest(b, x, y)) {
			if (b->id == 0) {
				gm_->initGame();
			}
		
			else if (b->id == 1) {
				glutDestroyWindow(window_);
			}
		}
		//Set state back to zero.
		b->state = 0;
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void Menus::ButtonPress(Button *b, int x, int y) {
	if (b) {
		/*
		*	if the mouse click was within the buttons client area,
		*	set the state to true.
		*/
		if (ButtonClickTest(b, x, y)) {
			b->state = 1;
		}
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to check.
*	\param	x	-	the x location of the mouse cursor.
*	\param	y	-	the y location of the mouse cursor.
*/
void Menus::ButtonPassive(Button *b, int x, int y) {
	if (b) {
		//if the mouse moved over the control
		if (ButtonClickTest(b, x, y)) {
			/*
			*	If the cursor has just arrived over the control, set the highlighted flag
			*	and force a redraw. The screen will not be redrawn again until the mouse
			*	is no longer over this control
			*/
			if (b->highlighted == 0) {
				b->highlighted = 1;
				glutPostRedisplay();
			}
		}
		else
			/*
			*	If the cursor is no longer over the control, then if the control
			*	is highlighted (ie, the mouse has JUST moved off the control) then
			*	we set the highlighting back to false, and force a redraw.
			*/
			if (b->highlighted == 1) {
				b->highlighted = 0;
				glutPostRedisplay();
			}
	}
}

/*----------------------------------------------------------------------------------------
*	\brief	This function draws the specified button.
*	\param	b	-	a pointer to the button to draw.
*/
void Menus::ButtonDraw(Button *b) {
	int fontx;
	int fonty;

	if (b) {
		//We will indicate that the mouse cursor is over the button by changing its colour.
		if (b->highlighted)
			glColor3f(0.7f, 0.7f, 0.8f);
		else
			glColor3f(0.6f, 0.6f, 0.6f);

		//draw background for the button.
		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		//Draw an outline around the button with width 3
		glLineWidth(3);

		//The colours for the outline are reversed when the button.
		if (b->state)
			glColor3f(0.4f, 0.4f, 0.4f);
		else
			glColor3f(0.8f, 0.8f, 0.8f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glEnd();

		if (b->state)
			glColor3f(0.8f, 0.8f, 0.8f);
		else
			glColor3f(0.4f, 0.4f, 0.4f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(1);
		//Calculate the x and y coords for the text string in order to center it.
		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)b->label)) / 2;
		fonty = b->y + (b->h + 10) / 2;
		/*
		*	if the button is pressed, make it look as though the string has been pushed
		*	down. It's just a visual thing to help with the overall look....
		*/
		if (b->state) {
			fontx += 2;
			fonty += 2;
		}
		//If the cursor is currently over the button we offset the text string and draw a shadow
		if (b->highlighted) {
			glColor3f(0, 0, 0);
			Font(GLUT_BITMAP_HELVETICA_18, b->label, fontx, fonty);
			fontx--;
			fonty--;
		}
		glColor3f(1, 1, 1);
		Font(GLUT_BITMAP_HELVETICA_18, b->label, fontx, fonty);
	}
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw an overlay over the 3D scene.
*	This will be used to draw our fonts, buttons etc......
*/
void Menus::Draw2D() {
	ButtonDraw(&butStart_);
	ButtonDraw(&butHow_);
	ButtonDraw(&butEnd_);
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever a mouse button is pressed or released
*	\param	button	-	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
*	\param	state	-	GLUT_UP or GLUT_DOWN depending on whether the mouse was released
*						or pressed respectivly.
*	\param	x		-	the x-coord of the mouse cursor.
*	\param	y		-	the y-coord of the mouse cursor.
*/
void Menus::MouseButton(int button, int state, int x, int y) {
	//update the mouse position
	TheMouse.x = x;
	TheMouse.y = y;

	//has the button been pressed or released?
	if (state == GLUT_DOWN) {
		//This holds the location of the first mouse click
		if (!(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb)) {
			TheMouse.xpress = x;
			TheMouse.ypress = y;
		}

		//Which button was pressed?
		switch (button) {
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 1;
			ButtonPress(&butStart_, x, y);
			ButtonPress(&butHow_, x, y);
			ButtonPress(&butEnd_, x, y);
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 1;
			break;
		}
	}
	else {
		//Which button was released?
		switch (button) {
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			ButtonRelease(&butStart_, x, y);
			ButtonRelease(&butHow_, x, y);
			ButtonRelease(&butEnd_, x, y);
			break;
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 0;
			break;
		}
	}
	/*
	*	Force a redraw of the screen. If we later want interactions with the mouse
	*	and the 3D scene, we will need to redraw the changes.
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND A BUTTON IS HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void Menus::MouseMotion(int x, int y) {
	//Calculate how much the mouse actually moved
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	//update the mouse position
	TheMouse.x = x;
	TheMouse.y = y;

	//Check MyButton to see if we should highlight it cos the mouse is over it
	ButtonPassive(&butStart_, x, y);
	ButtonPassive(&butHow_, x, y);
	ButtonPassive(&butEnd_, x, y);

	//Force a redraw of the screen
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND NO BUTTONS ARE HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void Menus::MousePassiveMotion(int x, int y) {
	//Calculate how much the mouse actually moved
	int dx = x - TheMouse.x;
	int dy = y - TheMouse.y;

	//update the mouse position
	TheMouse.x = x;
	TheMouse.y = y;

	//Check MyButton to see if we should highlight it cos the mouse is over it
	ButtonPassive(&butStart_, x, y);
	ButtonPassive(&butHow_, x, y);
	ButtonPassive(&butEnd_, x, y);

	/*
	*	Note that I'm not using a glutPostRedisplay() call here. The passive motion function
	*	is called at a very high frequency. We really don't want much processing to occur here.
	*	Redrawing the screen every time the mouse moves is a bit excessive. Later on we
	*	will look at a way to solve this problem and force a redraw only when needed.
	*/
}

void Menus::setWindow(int window) {
	window_ = window;
}