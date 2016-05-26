#include "GameManager.hpp"
#include <iostream>
#include <exception>
GameManager::GameManager()
{
	counter1_ = 0;

}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Adding the camera to the scene
  cam_.reset(new Camera());
  //  this->addSubObject(cam_);
  //  matrix_.translate(0.0f, 0.0f, -99.0f);

  isshowMenu_ = true;

  menu_.reset(new Menus(shared_from_this()));
  this->addSubObject(menu_);

 

  fpscounter_ = std::to_string(fps_);



}

void GameManager::privateRender()
{


}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
  
  counter1_++;
  { 
	  if (counter1_ > 50)
	  {
		  counter1_ = 0;
		  fpscounter_ = std::to_string(fps_);
	  }
	  bitmap_->drawBitmapText(fpscounter_.c_str(), glutGet(GLUT_WINDOW_HEIGHT) - 100, glutGet(GLUT_WINDOW_WIDTH) - 100);
  }




}

std::shared_ptr<Camera> GameManager::getCam()
{
	return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getSpaceship ()
{
    return spaceship_;
}

std::shared_ptr<Menus> GameManager::getMenu()
{
	return menu_;
}

void GameManager::addEnemies()
{
    std::shared_ptr<Enemies> Enemies_;
    Enemies_.reset(new Enemies());
    this->addSubObject(Enemies_);
    Enemiess_.push_back(Enemies_);
    addBullet();

}


void GameManager::addBullet()
{
  for (int i=0;  i < Enemiess_.size(); i++)
  {

      std::shared_ptr<Bullet> bullet_;
      glm::vec3 dir(0,0,0.1);
      bullet_.reset(new Bullet());
      bullet_->SetPosition(Enemiess_[i]->Position());
      bullet_->SetDirection(dir);
      this->addSubObject(bullet_);
      bullets_.push_back(bullet_);
  }
}

void GameManager::addBulletPlayer()
{
    std::shared_ptr<Bullet> bullet_;
    glm::vec3 dir(0,0,-1);
    bullet_.reset(new Bullet());
    bullet_->SetPosition(spaceship_->Position());
    bullet_->SetDirection(dir);
    this->addSubObject(bullet_);
    bulletsPlayer_.push_back(bullet_);
}

bool GameManager::Collision(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2)
{
  float d = glm::length(position1-position2);
  if (d <= radius1+radius2) return true;
  return false;
}

void GameManager::showMenu()
{
	if (!isGameActive_) {
		isshowMenu_ = true;
		isGameOver_ = false;

	}
}

void GameManager::restartGame()
{
	if (isGameActive_) {
		return;
	}
	initGame();
}

void GameManager::initGame()
{
	isGameActive_ = true;
	isshowMenu_ = false;
	isGameOver_ = false;
	skybox_.reset(new Skybox(cam_));
	this->addSubObject(skybox_);

	bf1_.reset(new BattleField());
	this->addSubObject(bf1_);

	water1_.reset(new Water());
	this->addSubObject(water1_);

	spaceship_.reset(new SpaceShip());
	this->addSubObject(spaceship_);

	particle_.reset(new ParticleGenerators());
	this->addSubObject(particle_);

	bitmap_.reset(new BitMap());
	this->addSubObject(bitmap_);

	fpscounter_ = std::to_string(fps_);

	float life;
	float Enemieslife;

	for (int i = 0; i < bulletsPlayer_.size(); i++)
		if (bulletsPlayer_[i]->Position()[2] < -1200)
		{
			this->removeSubObject(bulletsPlayer_[i]);
			bulletsPlayer_.erase(bulletsPlayer_.begin() + i);
		}

	for (int i = 0; i < bullets_.size(); i++)
		if (bullets_[i]->Position()[2] > 100)
		{
			this->removeSubObject(bullets_[i]);
			bullets_.erase(bullets_.begin() + i);
		}

	for (int i = 0; i < Enemiess_.size(); i++)
		if (Collision(Enemiess_[i]->Radius(), spaceship_->Radius(), Enemiess_[i]->Position(), spaceship_->Position()))
		{
			this->removeSubObject(Enemiess_[i]);
			Enemiess_.erase(Enemiess_.begin() + i);

			spaceship_->setLife(0);
			this->removeSubObject(spaceship_);
		}

	for (int i = 0; i < bullets_.size(); i++)
		if (Collision(bullets_[i]->Radius(), spaceship_->Radius(), bullets_[i]->Position(), spaceship_->Position()))
		{
			this->removeSubObject(bullets_[i]);
			bullets_.erase(bullets_.begin() + i);

			spaceship_->die(10);
			life = spaceship_->getLife() - 10;
			spaceship_->setLife(life);

			//		spaceship_->addScores(-50);


			if (spaceship_->getLife() <= 0) {
				this->removeSubObject(spaceship_);
			}
		}

	for (int i = 0; i < Enemiess_.size(); i++)
		for (int j = 0; j < bulletsPlayer_.size(); j++)
			if (Collision(bulletsPlayer_[j]->Radius(), Enemiess_[i]->Radius(), bulletsPlayer_[j]->Position(), Enemiess_[i]->Position()))
			{
				this->removeSubObject(bulletsPlayer_[j]);
				bulletsPlayer_.erase(bulletsPlayer_.begin() + i);
				Enemiess_[i]->die(2);
				Enemieslife = Enemiess_[i]->getLife() - 2;
				Enemiess_[i]->setLife(Enemieslife);
				//				spaceship_->addScores(100);
				if (Enemiess_[i]->getLife() <= 0) {
					this->removeSubObject(Enemiess_[i]);
					Enemiess_.erase(Enemiess_.begin() + i);
				}

			}
	
	// Nothing to render
}

void GameManager::endGame()
{
	isGameActive_ = false;
	isGameOver_ = true;
	
	GLvoid KillGLWindow(GLvoid);//正常销毁窗口


}

bool GameManager::shouldMenuBeShown()
{
	return isshowMenu_;
}

bool GameManager::isGameActive()
{
	return isGameActive_;
}


