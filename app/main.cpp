
#include <GL\glew.h>
#include <windows.h>
#include <GL/freeglut.h>  
#include <GL/glut.h>
#include <GL/GLU.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <Eigen/Core>
#include "Objload.hpp"
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"

#include "glm/glm.hpp"

#include <iostream>

using namespace Eigen;
std::shared_ptr<GameManager> gm;
std::shared_ptr<Menus> mm;
siut::FpsCounter counter;

int window;
int oldTimeFPS;
bool keyPressed[30];
int mousePosX, mousePosY; 
float moveX, moveY;


Loader loader[2];



void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);


  auto error = glewInit();
  std::cout << error << std::endl;

  counter.start();

  char *buff = (char*)glGetString(GL_VERSION);
  std::cout << buff << std::endl;


  buff = (char*)glGetString(GL_VENDOR);
  std::cout << buff << std::endl;

  buff = (char*)glGetString(GL_RENDERER);
  std::cout << buff;

  gm.reset(new GameManager());
  gm->init();
 // mm = gm->getMenu();

  for(int i=0; i<30; i++)
    keyPressed[i]=false;

  glEnable(GL_NORMALIZE);
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int startFPS = glutGet(GLUT_ELAPSED_TIME);
  int deltaFPS = startFPS - oldTimeFPS;
  oldTimeFPS = startFPS;

  gm->update((1.0f/float(deltaFPS))*1000.0f);
  gm->render();

  GLenum err = glGetError();
  if (err != GL_NO_ERROR)
	  std::cout << "OpenGL error: " << gluErrorString(err) << std::endl;
  std::cout.flush();



  

  if(keyPressed[KEY_ID_W]==true)      gm->getCam()->moveForward();
  if(keyPressed[KEY_ID_A]==true)      gm->getCam()->moveLeft();
  if(keyPressed[KEY_ID_D]==true)      gm->getCam()->moveRight();
  if(keyPressed[KEY_ID_S]==true)      gm->getCam()->moveBackward();
  if(keyPressed[KEY_ID_P]==true)	  gm->getCam()->moveUp();
  if(keyPressed[KEY_ID_C]==true)      gm->getCam()->moveDown();

  if (keyPressed[KEY_ID_L] == true)   gm->restartGame();
  if (keyPressed[KEY_ID_M] == true)   gm->showMenu();
  

if(keyPressed[KEY_ID_RIGHT]==true)    gm->getSpaceship()->moveRight();
  if(keyPressed[KEY_ID_LEFT]==true)   gm->getSpaceship()->moveLeft();
  if(keyPressed[KEY_ID_UP]==true)     gm->getSpaceship()->moveUp();
  if(keyPressed[KEY_ID_DOWN]==true)   gm->getSpaceship()->moveDown();
  if((keyPressed[KEY_ID_SPACE]==true) && (gm->getSpaceship()->getLife() > 0))
                    

  {
         gm->addBulletPlayer();
         keyPressed[KEY_ID_SPACE] = false;

  }
  //int scores = gm->getSpaceship()->getScores();
  //std::ostringstream convert;
  //convert << scores;
  //std::string score;
  //score = convert.str();

  glutSwapBuffers();
  glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
  switch (key) 
  {
   // case 'q':
    //case 27:
     // glutDestroyWindow(window);
//#ifndef _WIN32
      // Must use this with regular glut, since it never returns control to main().
     //exit(0);
	 //#endif
      //break;
      
    case 'w':
      keyPressed[KEY_ID_W] = true;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = true;
      break;
    case 's':
      keyPressed[KEY_ID_S] = true;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = true;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = true;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = true;
 break;
      case 'z':
        keyPressed[KEY_ID_Z] = true;
        break;
      case '1':
        keyPressed[KEY_ID_1] = true;
        break;
      case '2':
        keyPressed[KEY_ID_2] = true;
        break;
      case '3':
        keyPressed[KEY_ID_3] = true;
        break;
      case 'q':
        keyPressed[KEY_ID_Q] = true;
      break;
	  case 'p':
		  keyPressed[KEY_ID_P] = true;
		  break;

	  case 'l':
		  keyPressed[KEY_ID_L] = true;
		  break;
	  case 'm':
		  keyPressed[KEY_ID_M] = true;
		  break;
    default:
      glutPostRedisplay();
  }
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'w':
      keyPressed[KEY_ID_W] = false;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = false;
      break;
    case 's':
      keyPressed[KEY_ID_S] = false;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = false;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = false;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = false;
      break;
    case 'z':
      keyPressed[KEY_ID_Z] = false;
      break;
    case '1':
      keyPressed[KEY_ID_1] = false;
      break;
    case '2':
      keyPressed[KEY_ID_2] = false;
      break;
    case '3':
      keyPressed[KEY_ID_3] = false;
      break;
    case 'q':
      keyPressed[KEY_ID_Q] = false;
      break;
	case 'p':
		keyPressed[KEY_ID_P] = false;
		break;
	case 'l':
		keyPressed[KEY_ID_L] = false;
		break;
	case 'm':
		keyPressed[KEY_ID_M] = false;
		break;
  }
}

void keyDownSpesial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        keyPressed[KEY_ID_LEFT] = true;
        break;
    case GLUT_KEY_RIGHT:
        keyPressed[KEY_ID_RIGHT] = true;
        break;
    case GLUT_KEY_UP:
        keyPressed[KEY_ID_UP] = true;
        break;
    case GLUT_KEY_DOWN:
        keyPressed[KEY_ID_DOWN] = true;
        break;
    default:
        glutPostRedisplay();
  }
}
void keyUpSpesial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        keyPressed[KEY_ID_RIGHT] = false;
        break;
    case GLUT_KEY_LEFT:
        keyPressed[KEY_ID_LEFT] = false;
        break;
    case GLUT_KEY_UP:
        keyPressed[KEY_ID_UP] = false;
        break;
    case GLUT_KEY_DOWN:
        keyPressed[KEY_ID_DOWN] = false;
        break;
    }
}

void mousePressed(int button, int state, int posX, int posY)
{
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    mousePosX = posX;
    mousePosY = posY;
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }  
  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if(keyPressed[MOUSE_LEFT_BUTTON_DOWN])
  {
    int diffX = posX - mousePosX;
    mousePosX = posX;
    int diffY = posY - mousePosY;
    mousePosY = posY;
    
    // Implement quaternion based mouse move

  }
}
void addEnemies(int i){
    gm->addEnemies();
    glutTimerFunc(2000, addEnemies, 0);
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  glOrtho(-50, 700, -50, 700, -50, 50);
  gluPerspective(60.0f, float(w)/float(h) ,0.5f, 5000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}
void drawStrokeText(char*string, int x, int y, int z)
{
	char *c;
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	// glScalef(0.09f,-0.08f,z);

	for (c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}
//void DrawScene()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);                             // Switch to the drawing perspective
//	glLoadIdentity();                                       // Reset the drawing perspective
//	glTranslatef(0.0f, 0.0f, -cameraDistance);              // Move forward 5 units
//
//															// Adding light
//	if (isLightingEnabled)
//	{
//		// Set lighting intensity and color
//		glLightfv(GL_LIGHT0, GL_AMBIENT, colorDarkGray);
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLightGray);
//
//		if (isSpecularLightEnabled)
//		{
//			glLightfv(GL_LIGHT0, GL_SPECULAR, colorWhite);
//
//			// Setting material properties
//			glMaterialfv(GL_FRONT, GL_SPECULAR, colorWhite);
//			glMaterialf(GL_FRONT, GL_SHININESS, shininess); // Shininess: 0 to 128
//		}
//
//		// Set the light position
//		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//	}
//
//	if (isWireframeModeEnabled)
//	{
//		// Turn on wireframe mode
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glPolygonMode(GL_BACK, GL_LINE);
//	}
//	else
//	{
//		// Turn off wireframe mode
//		glPolygonMode(GL_FRONT, GL_FILL);
//		glPolygonMode(GL_BACK, GL_FILL);
//	}
//
//	glPushMatrix();
//
//	// Drawing a cube
//	glColor3f(0.60, 0.60, 0.60);                            // Color: Gray
//	glRotatef(rotateAngle, false, true, false);
//
//	// ------------------------------------------------
//	simpleModel->Draw();
//	// ------------------------------------------------
//
//	glPopMatrix();
//
//	glutSwapBuffers();
//}


int main(int argc, char** argv)
{



  glutInit(&argc, argv); // initialize glut
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);// specify the display mode to be RGB and single buffering  
															 // we use single buffering since this will be non animated 
  glutInitWindowSize(700, 700);  // define the size 
  glutInitWindowPosition(10, 10); // the position where the window will appear 
  window = glutCreateWindow("Space Shooter 3D");
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(reshape);
 
  char 
	  a[20] = "Obj/teapot.obj",
	  b[20] = "Obj/teapot.obj";

  if (argc>1) {
	  strcpy(a, argv[1]);
	  if (argc>2)
		  strcpy(a, argv[2]);
  }

 // loader[0].Load(a);
  loader[1].Load(b);


  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);
  //glutIdleFunc(render);
  glutSpecialFunc(keyDownSpesial);
  glutSpecialUpFunc(keyUpSpesial);
  glutTimerFunc(1000, addEnemies, 0);
  // Add other callback functions here..
  // enter the main loop 





  glutMainLoop();
  return 0;
}
