#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"
#include "C:/Users/LIN/Documents/Visual Studio 2015/Projects/Shoot/Shoot/SOID/SOIL.h"

class BattleField : public SceneObject
{
	public:
		BattleField();
		~BattleField();
		
  protected:
	    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();
		void Arrays();
	private:
		Shader shaderbattle_;
		
		int grid_x;
		int grid_z;

		
		std::vector<unsigned int> index_;
		std::vector< glm::vec3 > vertexArray_; 		
		std::vector< glm::vec2 > coordArray_;
		
		GLuint tex_2d[2];
		
};

