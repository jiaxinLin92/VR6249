#include "BitMap.hpp"

BitMap::BitMap()
{
	
}

BitMap::~BitMap()
{
}

void BitMap::drawBitmapText(const char * string, float x, float y)
{
	
		//string_ = string;
		const char *c;
		glWindowPos2f(x, y);

		for (c = string; *c != '\0'; c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
	
}


void BitMap::privateInit()
{

}


void BitMap::privateRender()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0.5, 0.7);
	drawBitmapText("Shooting", 10, 660);
	
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//glDepthFunc(GL_ALWAYS);
}
