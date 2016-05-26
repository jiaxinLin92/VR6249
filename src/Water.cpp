#include "..\include\Water.hpp"

Water::Water()
{
	grid_x = 160;
	grid_z = 512;
	
	waveTime_ = 0.8f;
	waveFreq_ = 0.05;
	waveWidth_ = 0.5;
	waveHeight_ = 1.2;

	matrix_ = glm::translate(matrix_, glm::vec3(0.f, -100.f, 0.f));
	
}

void Water::privateInit()
{
	Arrays();

	shaderwater_.initShaders("../Shoot/shaders/water");
	shaderwater_.enable();
	glUniform3f(glGetUniformLocation(shaderwater_.getProg(), "ObjColor"), 0.0, 0.0, 0.0);
	glUniform1f(glGetUniformLocation(shaderwater_.getProg(), "waveTime"), waveTime_);
	glUniform1f(glGetUniformLocation(shaderwater_.getProg(), "waveWidth"), waveWidth_);
	glUniform1f(glGetUniformLocation(shaderwater_.getProg(), "waveHeight"), waveHeight_);
	
	
	shaderwater_.disable();
}

void Water::privateRender()
{
	shaderwater_.enable();
	//glEnable(GL_PRIMITIVE_RESTART);

	glEnableClientState(GL_VERTEX_ARRAY); // enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]); // set vertex pointer
	//glTexCoordPointer(2, GL_FLOAT, 0, &coordArray_[0]);
	glEnable(GL_PRIMITIVE_RESTART);
	glDrawElements(GL_QUAD_STRIP, index_.size(), GL_UNSIGNED_INT, &index_[0]);
	
	glDisableClientState(GL_VERTEX_ARRAY); // disable vertex arrays 
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	shaderwater_.disable();
}

void Water::privateUpdate()
{

	shaderwater_.enable();
	waveTime_ += waveFreq_;
	glUniform1f(glGetUniformLocation(shaderwater_.getProg(), "waveTime"), waveTime_);
	shaderwater_.disable();
}

void Water::Arrays()
{
	for (int i = -grid_z; i < 0; i++)
	{
		for (int j = 0; j < grid_x; j++)
		{
			vertexArray_.push_back(glm::vec3((j - grid_x / 2)* 10.0f, 0.0f, i * 10.0f));
			//float x = std::abs(float(j) / float(grid_x - 1));
			//float z = std::abs(float(i + grid_z + 1) / float(grid_z + 1));
			//coordArray_.push_back(glm::vec2(x, z));
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

}
