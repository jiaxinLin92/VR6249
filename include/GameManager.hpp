#pragma once
#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <String>
#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Camera.hpp"
#include "ParticleGenerators.hpp"
#include "BitMap.hpp"
#include "Enemies.hpp"
#include "Bullet.hpp"
#include "Skybox.hpp"
#include "Water.hpp"
#include "Menus.hpp"
#include <memory>

#include <iostream>
//#include <sstream>
#include <stdlib.h>
#include <stdio.h>
class GameManager : public SceneObject, public std::enable_shared_from_this<GameManager>
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
	
	std::shared_ptr<SpaceShip> getSpaceship();
	std::shared_ptr<Menus> getMenu();

    void addEnemies();
    void addBullet();
    void addBulletPlayer();
    bool Collision(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2);
	void showMenu();
	void restartGame();
	void initGame();
	void endGame();
	bool shouldMenuBeShown();
	bool isGameActive();
  
protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

		bool isshowMenu_;
		bool isGameActive_;
		bool isGameOver_;


	private:
    std::shared_ptr<BattleField> bf1_;
	std::shared_ptr<Water> water1_;
    std::shared_ptr<SpaceShip> spaceship_;
//	std::shared_ptr<Enemies> enemies_;
	std::shared_ptr<ParticleGenerators> particle_;
	std::shared_ptr<BitMap> bitmap_;

	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Menus> menu_;
    std::shared_ptr<Camera> cam_;
	std::vector< std::shared_ptr<Enemies> > Enemiess_;
    std::vector< std::shared_ptr<Bullet> > bullets_;
    std::vector< std::shared_ptr<Bullet> > bulletsPlayer_;
	



	float counter1_;
	//float counter2_;
	std::string fpscounter_;
};

