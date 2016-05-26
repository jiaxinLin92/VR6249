
#include "SpaceShip.hpp"
#include "Objload.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
SpaceShip::SpaceShip()
{
    radius = 1.0f;
    position = glm::vec3(0.0f, 0.0f, 5.0f);
    life_ = 100;
    scores_ = 0;
}

SpaceShip::~SpaceShip()
{
}



void SpaceShip::privateInit()
{
	

	
	shader_.initShaders("shaders/red");
	shader_.enable();

	GLint lightPos;
	lightPos = glGetUniformLocation(shader_.getProg(), "LightPosition");
	glUniform3f(lightPos,1.0f, 1.0f, 1.0f);

	GLint objColor;
	objColor = glGetUniformLocation(shader_.getProg(), "ObjColor");
	glUniform3f(objColor, 1.0f, 1.0f, 1.0f);
	
	shader_.disable();

	//GLfloat light_param[] = { 1, 1, 1, 0.0 };    //初始化光参数。
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_param);    //设置光为环境光。
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_DEPTH_TEST);

	texture = SOIL_load_OGL_texture
		(
			"C:/Users/LIN/Desktop/STE6249 VR/images.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	

	if (0 == texture) printf("SOIL loading error: '%s'\n", SOIL_last_result());

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);


	
}

void SpaceShip::privateRender()
{

	
	shader_.enable();
	
	list_id = glGenLists(1);
	glNewList(list_id, GL_COMPILE);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] - 1.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] - 1.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] - 1.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] - 1.5);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] + 1.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] + 1.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] + 1.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] + 1.5);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] - 1.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] - 1.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] + 1.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] + 1.5);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] + 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] + 0.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] - 0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] - 0.5);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] + 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] + 1.5, position[2] - 0.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] - 0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] + 1.5, position[2] + 0.5);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] - 0.5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position[0] + 1.5, position[1] - 1.5, position[2] + 0.5);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] + 0.5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position[0] - 1.5, position[1] - 1.5, position[2] - 0.5);
	glEnd();
	glEndList();

	//glColor3f(1.0f, 1.0f, 0.0f);
	//float size = 1.5f;
	//glBegin(GL_QUADS);
	//// Near Face
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, size);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size, size);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size, size);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size, size);
	//glEnd();
	glCallList(list_id);


	shader_.disable();
	

	
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//GLfloat lightpos[] = { 10, 10, 10, 1.0 };
	//GLfloat mat_ambient[] = { 0.5,0.5,0.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture);

	

	//glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHTING);


}
void SpaceShip::privateUpdate()
{
	

}


void SpaceShip::moveRight()
{
    if ( position[0] < 150 ){
        glm::vec3 v = glm::vec3(0.03f, 0.0f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }

}
void SpaceShip::moveLeft()
{
    if ( position[0] > -150 ){
        glm::vec3 v = glm::vec3(-0.03f, 0.0f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}

void SpaceShip::moveUp()
{
    if ( position[1] < 10 ){
        glm::vec3 v = glm::vec3(0.0f, 0.01f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}
void SpaceShip::moveDown()
{
    if ( position[1] > -10 ){
        glm::vec3 v = glm::vec3(0.0f, -0.01f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}


float SpaceShip::Radius()
{
    return radius;
}

glm::vec3 SpaceShip::Position()
{
    return position;
}

void SpaceShip::die(float life)
{
  life_ -= life;
}

float SpaceShip::getLife()
{
  return life_;
}

void SpaceShip::setLife(float l)
{
  life_ = l;
}

//int SpaceShip::getScores()
//{
//  return scores_;
//}
//
//void SpaceShip::addScores(int score)
//{
//  scores_ += score;
//}
