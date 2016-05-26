#include "BattleField.hpp"

BattleField::BattleField()
{

	grid_x =32;
	grid_z =512;
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	Arrays();

	//shader landscape
	//Association between texture unit and sampler variable: 
	shaderbattle_.initShaders("../Shoot/shaders/terrain");
	shaderbattle_.enable();




	GLint color;
	color = glGetUniformLocation(shaderbattle_.getProg(), "color");
	glUniform1i(color, 0);

	GLint light;
	light = glGetUniformLocation(shaderbattle_.getProg(), "light");
	glUniform1i(light, 1);
	
	GLint height;
	height = glGetUniformLocation(shaderbattle_.getProg(), "height");
	glUniform1i(height, 2);



	shaderbattle_.disable();

	//colormap

	
	tex_2d[0] = SOIL_load_OGL_texture
		(
			"../Shoot/rescourse/colorMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	if (0 == tex_2d[0])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[0]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//lightmap

	tex_2d[1] = SOIL_load_OGL_texture
		(
			"../Shoot/rescourse/lightMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	if (0 == tex_2d[1])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[1]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//heightmap
	tex_2d[2] = SOIL_load_OGL_texture
		(
			"../Shoot/rescourse/heightMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	if (0 == tex_2d[2])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[2]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
}

void BattleField::privateRender()
{
	shaderbattle_.enable();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_PRIMITIVE_RESTART);
	glEnable(GL_FOG);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[0]); // binds the texture
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[1]);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[2]);

	// 初始化雾效 
	GLfloat fog[4] = { 0.8f,0.8f,0.8f,1.0f };

	glFogi(GL_FOG_MODE, GL_EXP); // specify fog equation used
	glFogfv(GL_FOG_COLOR, fog);         /** 指定雾的颜色 */
	glFogf(GL_FOG_START, 1.0f); // specify start parameters
	glFogf(GL_FOG_END, 512.0f); // specify end parameters
	glHint(GL_FOG_HINT, GL_DONT_CARE);       /** 规定雾化效果的质量 */

	glEnableClientState(GL_VERTEX_ARRAY);										// enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);								// enable texture coord arrays
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);							// set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &coordArray_[0]);						// set texture coord pointer
	glDrawElements(GL_QUAD_STRIP, index_.size(), GL_UNSIGNED_INT, &index_[0]);	// draw quads
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);								// disable texture coord arrays
	glDisableClientState(GL_VERTEX_ARRAY);										// disable vertex arrays


	glActiveTexture(GL_TEXTURE2);    //关闭纹理单元2
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE1);	//关闭纹理单元1
	glDisable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);	//关闭纹理单元0
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_FOG);
	glDisable(GL_PRIMITIVE_RESTART);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	shaderbattle_.disable();



}

void BattleField::privateUpdate()
{

}

void BattleField::Arrays()
{

	// Create vertex arrays

	/*for (int j = 0; j > - grid_z; j--) {
	for (int i = - grid_x; i < grid_x; i++) {
	vertexArray_.push_back(glm::vec3(i * 10, 0, j * 10));
	float x = float(i + grid_x) / float(grid_x * 2 - 1);
	float z = float(-j) / float(grid_z + 1);
	coordArray_.push_back(glm::vec2(x, z));
	}
	}*/

	//glm::vec3 v;
	//glm::vec2 t;//用于插图是定坐标
	//for (int z = 0; z < grid_z; z++)
	//{
	//	for (int x = 0; x < grid_x; x++)
	//	{
	//		v[0] = float(x)*10.0f - ((grid_x / 2.0f)*10.0f); //定义landscape的坐标（放于屏幕中间）
	//		v[1] = 0.0f;	//y坐标
	//		v[2] = float(z)*(-10.0f);//z坐标
	//		vertexArray_.push_back(v);

	//		t[0] = float(x) / grid_x;
	//		t[1] = float(z) / grid_z;

	//		coordArray_.push_back(t);
	//	}
	//}
	//glEnable(GL_PRIMITIVE_RESTART);



	for (int i = -grid_z; i < 0; i++)
	{
		for (int j = 0; j < grid_x; j++)
		{
			vertexArray_.push_back(glm::vec3((j - grid_x /2)* 10.0f, 0.0f, i * 10.0f));
			float x = std::abs(float(j ) / float(grid_x - 1));
			float z = std::abs(float(i+ grid_z+1) / float(grid_z + 1));
			coordArray_.push_back(glm::vec2(x, z));
		}
	}
	glPrimitiveRestartIndex(MAXINT);
	for (int k = 0; k < vertexArray_.size() - grid_x; k++)
	{
		index_.push_back(k);
		index_.push_back(k + grid_x);

		if ((k + 1) % grid_x == 0)
		{
			index_.push_back(MAXINT);
		}
	}


	/*glPrimitiveRestartIndex(MAXINT);

	for (int i = 0; i < vertexArray_.size() - grid_z; i++)
	{
		index_.push_back(i + grid_z);

		index_.push_back(i);


		if ((1 + i) % (grid_z) == 0)
		{
			index_.push_back(MAXINT);
		}
	}*/
	//glDisable(GL_PRIMITIVE_RESTART);

}

