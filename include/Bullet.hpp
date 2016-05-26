#pragma once
#include <GL\glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL\glut.h>
#include "SceneObject.hpp"
#include "C:/Users/LIN/Documents/Visual Studio 2015/Projects/Shoot/Shoot/SOID/SOIL.h"

class Bullet : public SceneObject
{
public:
    Bullet();
    ~Bullet();

    void SetPosition(glm::vec3 pos);
    float Radius();
    glm::vec3 Position();
    void SetDirection(glm::vec3 dir);



protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
	GLuint texture_bullet;
    int list_id;

    glm::vec3 position;
    float radius;
    glm::vec3 direction;



};
