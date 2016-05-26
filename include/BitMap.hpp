#include <GL/glew.h>
#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output
#include <gl\gl.h>					// Header File For The OpenGL32 Library
#include <gl\glu.h>					// Header File For The GLu32 Library

#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "SceneObject.hpp"
//#include "SrdAfx.hpp"

class BitMap : public SceneObject
{
public:
	BitMap();
	~BitMap();

	void drawBitmapText(const char *string, float x, float y);

protected:
	 
	


	 void privateInit();

	 void privateRender();


private:

	const char *string_;

};

