#pragma once
#include <GL\glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "Shader.hpp"
#include "SceneObject.hpp"
#include "C:/Users/LIN/Documents/Visual Studio 2015/Projects/Shoot/Shoot/SOID/SOIL.h"
#include "Shader.hpp"

class Enemies : public SceneObject
{
public:
    Enemies();
    ~Enemies();
    float Radius() const;
    glm::vec3 Position() const;

    void die(float life);
    float getLife();
    void setLife(float l);
	Shader shader_;


	
protected:
    void privateInit();
    void privateRender();
    void privateUpdate();
	void normalMovement(), sinusMovement(), cosinusMovement();

private:
    float speed_;
    float life_;
    float armor_;

    int list_id;
    float radius;
    glm::vec3 position_;
	glm::vec3 positionb_;
    int random;
    int rand2;
    double x;

};
