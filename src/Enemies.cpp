
#include "Enemies.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

#define M_PI 3.1415926535

Enemies::Enemies()
{
  x = 0;
  srand(time(0));
  random = rand()%40 - 20;
  rand2 = rand()%20;

  if (rand2 > 150){
    radius = 1.0;
    life_ = 20;
  }
  else{
    radius = 0.5;
    life_ = 10;
  }
  position_ = glm::vec3(random, 0.0f, -200.0f);

  privateInit();
}

Enemies::~Enemies()
{
}

void Enemies::privateInit()
{
	

	
	shader_.initShaders("../Shoot/shaders/phong");


	list_id = glGenLists(1);
	float z = rand2 / 4 - 2;

	glNewList(list_id, GL_COMPILE);
	
	glBegin(GL_QUADS);

	
	glColor3f(0.0, 0.0, 0.0); glVertex3f(position_[0] + radius , position_[1] - radius , position_[2] - radius + z );
	glColor3f(0.0, 0.0, 1.0); glVertex3f(position_[0] + radius , position_[1] + radius , position_[2] - radius + z );
	glColor3f(1.0, 0.0, 1.0); glVertex3f(position_[0] - radius , position_[1] + radius , position_[2] - radius + z );
	glColor3f(0.0, 1.0, 0.0); glVertex3f(position_[0] - radius , position_[1] - radius , position_[2] - radius + z );


	glColor3f(1.0, 1.0, 0.0); glVertex3f(position_[0]  + radius, position_[1]  - radius, position_[2]  + radius + z);
	glColor3f(1.0, 1.0, 1.0); glVertex3f(position_[0]  + radius, position_[1]  + radius, position_[2]  + radius + z);
	glColor3f(1.0, 0.0, 1.0); glVertex3f(position_[0]  - radius, position_[1]  + radius, position_[2]  + radius + z);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(position_[0]  - radius, position_[1]  - radius, position_[2]  + radius + z);

	glColor3f(0.0, 1.0, 0.0); glVertex3f(position_[0]  + radius, position_[1]  - radius, position_[2]  - radius + z);
	glColor3f(0.0, 1.0, 1.0); glVertex3f(position_[0]  + radius, position_[1]  + radius, position_[2]  - radius + z);
	glColor3f(1.0, 1.0, 1.0); glVertex3f(position_[0]  + radius, position_[1]  + radius, position_[2]  + radius + z);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(position_[0]  + radius, position_[1]  - radius, position_[2]  + radius + z);

	glColor3f(1.0, 0.0, 0.0); glVertex3f(position_[0]  - radius, position_[1]  - radius, position_[2]  + radius + z);
	glColor3f(1.0, 0.0, 1.0); glVertex3f(position_[0]  - radius, position_[1]  + radius, position_[2]  + radius + z);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(position_[0]  - radius, position_[1]  + radius, position_[2]  - radius + z);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(position_[0]  - radius, position_[1]  - radius, position_[2]  - radius + z);

	glColor3f(1.0, 1.0, 1.0); glVertex3f(position_[0]  + radius, position_[1]  + radius, position_[2]  + radius + z);
	glColor3f(0.0, 1.0, 1.0); glVertex3f(position_[0]  + radius, position_[1]  + radius, position_[2]  - radius + z);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(position_[0]  - radius, position_[1]  + radius, position_[2]  - radius + z);
	glColor3f(1.0, 0.0, 1.0); glVertex3f(position_[0]  - radius, position_[1]  + radius, position_[2]  + radius + z);

	glColor3f(0.0, 1.0, 0.0); glVertex3f(position_[0]  + radius, position_[1]  - radius, position_[2]  - radius + z);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(position_[0]  + radius, position_[1]  - radius, position_[2]  + radius + z);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(position_[0]  - radius, position_[1]  - radius, position_[2]  + radius + z);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(position_[0]  - radius, position_[1]  - radius, position_[2]  - radius + z);
	glEnd();
	
	glTranslatef(position_[0], position_[1], -100);
	glutSolidSphere(radius, 20, 20);

	glEndList();
	
}

void Enemies::privateRender()
{

	//shader_.enable();

	////normal
	//if (this->mode_ == 0) {
	//	normalMovement();
	//}
	////sinus
	//if (this->mode_ == 1) {
	//	sinusMovement();
	//}
	////cosinus
	//if (this->mode_ == 2) {
	//	cosinusMovement();
	//}

	//shader_.disable();


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat lightpos[] = {10, 10, 10, 1.0};
  GLfloat mat_ambient[] = {10,0.5,0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

  glm::vec3 move1 = glm::vec3(0.0f, 0.0f, 0.5f);
  glm::vec3 move2 = glm::vec3(sin(x)/30, 0.0f, 0.5f);

  if (rand2 > 15){
    matrix_ = glm::translate(matrix_, move1);
    position_ += move1;
  }
  else{
    matrix_ = glm::translate(matrix_, move2);
    position_ += move2;

    x += 0.5;
    if (x > 2*M_PI) x = 0;
  }
  glCallList(list_id);

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void Enemies::privateUpdate()
{


}

float Enemies::Radius() const
{
  return radius;
}

glm::vec3 Enemies::Position() const
{
  return position_;
}

void Enemies::die(float life)
{
  life_ -= life;
}

float Enemies::getLife()
{
  return life_;
}

void Enemies::setLife(float life)
{
  life_ = life;
}



