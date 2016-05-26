#include "Skybox.hpp"


Skybox::Skybox(std::shared_ptr<Camera> cam) {
	cam_ = cam;
}

Skybox::~Skybox() {
}

void Skybox::privateInit() {

	loadSkybox();
	shadersky_.initShaders("shaders/skybox");
	shadersky_.enable();
	GLint texSampler;
	texSampler = glGetUniformLocation(shadersky_.getProg(), "skybox");
	glUniform1i(texSampler, 0);
	shadersky_.disable();

}

void Skybox::privateRender() {
	
	//glGenTextures(1, &cubeBox);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBox);

	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // right
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // left
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // above
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // below
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // front
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_); // behind


	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
	//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
	//glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_GEN_T);
	//glEnable(GL_TEXTURE_GEN_R);

	//glEnble(GL_TEXTURE_CUBE_MAP);
	//


	shadersky_.enable();
	glFrontFace(GL_CW);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBox);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	float v[8][3] = {
		{ -1.0f, -1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
		{ 1.0f,  1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f,  1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
	};

	unsigned int i[24] = {
		0,1,2,3,
		1,5,6,2,
		5,4,7,6,
		4,0,3,7,
		0,4,5,1,
		2,6,7,3
	};

	glBegin(GL_QUADS);
	for (int k = 0; k < 24; ++k) {
		glTexCoord3f(v[i[k]][0], v[i[k]][1], v[i[k]][2]);
		glVertex3f(v[i[k]][0], v[i[k]][1], v[i[k]][2]);
	}
	glEnd();

	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	shadersky_.disable();
}

void Skybox::privateUpdate() {

	matrix_[3][0] = -cam_->getMatrix()[3][0];
	matrix_[3][1] = -cam_->getMatrix()[3][1];
	matrix_[3][2] = -cam_->getMatrix()[3][2];
}
void Skybox::loadSkybox() {
	cubeBox = SOIL_load_OGL_cubemap
		(
			//"rescourse/skybox_east.bmp",			/*x-positive right*/
			//"rescourse/skybox_west.bmp",			/*x-negative left*/
			//"rescourse/skybox_up.bmp",			/*y-positive aboue*/
			//"rescourse/skybox_down.bmp",			/*y-negative below*/
			//"rescourse/skybox_north.bmp",		   /*z-positive front*/
			//"rescourse/skybox_south.bmp",	       /*z-negative behind*/

			"rescourse/entropic_rt.tga",
			"rescourse/entropic_lf.tga",
			"rescourse/entropic_up.tga",
			"rescourse/entropic_dn.tga",
			"rescourse/entropic_ft.tga",
			"rescourse/entropic_bk.tga",

			SOIL_LOAD_RGB,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS
			);

	// check for an error during the load process 
	if (0 == cubeBox)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}