#include "Bullet.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL\glut.h>

Bullet::Bullet()
{
  radius = 12.5;

}

Bullet::~Bullet()
{
}

void Bullet::privateInit()
{

	//texture_bullet = SOIL_load_OGL_texture
	//	(
	//		"C:/Users/LIN/Desktop/STE6249 VR/PINK.png",
	//		SOIL_LOAD_AUTO,
	//		SOIL_CREATE_NEW_ID,
	//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	//		);

	///* check for an error during the load process */

	///*texture = SOIL_load_OGL_texture(Resources.data(),
	//SOIL_LOAD_AUTO,
	//SOIL_CREATE_NEW_ID,
	//SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//*/
	//if (0 == texture_bullet) printf("SOIL loading error: '%s'\n", SOIL_last_result());

	//glBindTexture(GL_TEXTURE_2D, texture_bullet);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 110.0f, 560.0f );
    glColor3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( position[0] + 0.1, position[1] - 0.1, position[2] );
    glVertex3f( position[0] + 0.1, position[1] + 0.1, position[2] );
    glVertex3f( position[0] - 0.1, position[1] + 0.1, position[2] );
    glVertex3f( position[0] - 0.1, position[1] - 0.1, position[2] );
    glEnd();
    glEndList();
}

void Bullet::privateRender()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = {10, 10, 10, 1.0};
    GLfloat mat_ambient[] = {0.5,0.5,0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    matrix_ = glm::translate(matrix_, direction);
    glCallList(list_id);

    position += direction;

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void Bullet::privateUpdate()
{

}

void Bullet::SetPosition(glm::vec3 pos)
{
    position = pos;
    privateInit();
}

void Bullet::SetDirection(glm::vec3 dir)
{
    direction = dir;
    privateInit();
}


float Bullet::Radius()
{
    return radius;
}

glm::vec3 Bullet::Position()
{
    return position;
}



