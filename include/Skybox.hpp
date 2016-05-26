#pragma once

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "C:/Users/LIN/Documents/Visual Studio 2015/Projects/Shoot/Shoot/SOID/SOIL.h"
class Skybox : public SceneObject {
public:
	Skybox(std::shared_ptr<Camera> cam);
	~Skybox();

protected:
	void loadSkybox();

private:
	void privateInit(), privateRender(), privateUpdate();

	GLuint cubeBox;
	int width_, height_;
	unsigned char* image_;
	Shader shadersky_;

	std::shared_ptr<Camera> cam_;
};