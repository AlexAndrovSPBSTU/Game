#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Content.h"
#include "Constants.h"
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

#pragma once


using namespace sf;
using std::string;
class Map;
class Tank;
class Heart;
template <typename T> inline constexpr
int signum(T x, std::true_type is_signed) {
	return (T(0) < x) - (x < T(0));
}

class Object {

protected:
	Texture texture;
	Sprite* sprite;

	Object(const string fileTexture) {
		texture.loadFromFile(fileTexture);
		sprite = new Sprite(texture);
	}

public:


	Sprite* getSprite()
	{
		return this->sprite; 
	}


};

class Wall : public Object
{
public:

	Wall(const string fileTexture): Object(fileTexture) {
		sprite->setScale(Vector2f(0.07f, 0.07f));
	}
};


class Castle : public Object
{
public:
	Castle(const string fileTexture,int angle): Object(fileTexture) {
		sprite->setScale(Vector2f(0.8f, 0.8f));
		sprite->rotate(angle);
	}
};

class Projectile : public Object
{
private:
	float dx, dy, speed, x, y;

public:
	Projectile(const string fileTexture, Vector2f startPosition, int angle, float speed) : Object(fileTexture)
	{
		sprite->rotate(angle+90);
		std::cout << angle << "\n";
		float offset = -40;
		sprite->setPosition(Vector2f(startPosition.x + (sprite->getGlobalBounds().width / 2 + offset) * sin(sprite->getRotation() * 3.14 / 180), startPosition.y + (sprite->getGlobalBounds().height / 2 + offset) * cos(sprite->getRotation() * 3.14 / 180) ) );
		this->speed = speed;
		x = sprite->getPosition().x;
		y = sprite->getPosition().y;
		sprite->setScale(Vector2f(0.5f, 0.5f));

	}

	void move()
	{
		x += speed * cos(-(sprite->getRotation()) * 3.14 / 180) ;
		y += speed * sin((sprite->getRotation()) * 3.14 / 180);

		this->sprite->setPosition(x, y);
	}

};

class Heart :public Object {
public:
	Heart(std::string fileTexture, Vector2f position) :Object(fileTexture) {
		sprite->setPosition(position);
		sprite->setScale(Vector2f(0.5f, 0.5f));
		}

};

class Tank : public Object {
private:
	float dx, dy, x, y;
	float speed = 0.1f;
	Tank* enemyTank;

	Clock shootTimer;
	float cooldown = 1.f;
	int health = 3;
	Sound soundShoot;
	Sound soundMiss;
	Sound soundHit;
	Sound soundDie;


public:
	float time;
	std::vector<Heart>* healthBar;
	std::vector <Projectile>* proj;
	bool dead = false;

	Tank(const string fileTexture, int angle, Vector2f vector) : Object(fileTexture) {
		sprite->setScale(Vector2f(0.7f, 0.7f));
		sprite->rotate(angle);
		sprite->setPosition(vector);
		x = vector.x;
		y = vector.y;

		sprite->setOrigin(Vector2f(76.f, 82.5f));
		proj = new std::vector<Projectile>();
		healthBar = new std::vector<Heart>();
		SoundBuffer* soundBuffer = new SoundBuffer();
		SoundBuffer* soundBuffer2 = new SoundBuffer();
		SoundBuffer* soundBuffer3 = new SoundBuffer();
		SoundBuffer* soundBuffer4 = new SoundBuffer();
		soundBuffer->loadFromFile("shot.wav");
		soundBuffer2->loadFromFile("miss.wav");
		soundBuffer3->loadFromFile("hit.wav");
		soundBuffer4->loadFromFile("death.wav");
		soundShoot.setBuffer(*soundBuffer);
		soundMiss.setBuffer(*soundBuffer2);
		soundHit.setBuffer(*soundBuffer3);
		soundDie.setBuffer(*soundBuffer4);
	}
	void createHealthBar(Vector2f position)
	{
		for (int i = 0; i < 3; i++)
			healthBar->push_back(*(new Heart("red.png", Vector2f(position.x + i * 64, position.y))));
	}

	void shoot()
	{
		if (shootTimer.getElapsedTime().asSeconds() < cooldown|| dead)
			return;
		soundShoot.play();
		shootTimer.restart();
		Vector2f projectileSpawn = Vector2f( sprite->getPosition().x + sprite->getGlobalBounds().width/2 * cos(sprite->getRotation() * 3.14 / 180), sprite->getPosition().y + sprite->getGlobalBounds().height / 2 * sin(sprite->getRotation() * 3.14 / 180));

		proj->push_back(*(new Projectile("bullet1.png", projectileSpawn, sprite->getRotation(), 1)));
	}

	void move(direction d) {
		
		switch (d)
		{
		case Up: dy = TANKS_SPEED*sin((90 - sprite->getRotation()) * 3.14 /180); dx = TANKS_SPEED * cos((- 90 - sprite->getRotation()) * 3.14 / 180); break;
		case Down: dy = -TANKS_SPEED * sin((90 - sprite->getRotation()) * 3.14 / 180); dx = -TANKS_SPEED * cos((-90 - sprite->getRotation()) * 3.14 / 180); break;
		case Left:  sprite->rotate(-TANKS_SPEED*0.8 ); dx = 0 ; dy = 0; break;
		case Right: sprite->rotate(TANKS_SPEED*0.8);  dx = 0; dy = 0; break;
			
		}


		if (isCollided() != Vector2f(-100., -100.)) 
		{
			//std::cout << isCollided().x << " " <<  isCollided().y << "\t\t";
			//std::cout << sprite->getPosition().x << " " <<  sprite->getPosition().y << std::endl;
			if (isCollided().x > sprite->getPosition().x)
				x -= 0.1;
			else
				x += 0.1;
			if (isCollided().y > sprite->getPosition().y)
				y -= 0.1;
			else
				y += 0.1;

		}
		else {

			x += dx;
			y += dy;

		}

		speed = 0.0f;
		sprite->setPosition(x, y);
		speed = 0.1f;
	}
	void updateProjectiles()
	{
		for (int i = 0; i < proj->size(); i++)
			proj->at(i).move();
	}
	Vector2f isCollided() {
		RectangleShape rectangle[7];
		rectangle[0].setPosition(Vector2f(0.f, 0.f)); // верхний край
		rectangle[0].setSize(Vector2f(1920.f, 40.f));

		rectangle[1].setPosition(Vector2f(0.f, 0.f)); //левый край
		rectangle[1].setSize(Vector2f(40.f, 1080.f));

		rectangle[2].setPosition(Vector2f(1880.f, 0.f)); //правый край
		rectangle[2].setSize(Vector2f(40.f, 1080.f));

		rectangle[3].setPosition(Vector2f(0.f, 1040.f)); //нижний край
		rectangle[3].setSize(Vector2f(1920.f, 40.f));

		rectangle[4].setPosition(Vector2f(265.f, 235.f)); //лева€ стена у базы
		rectangle[4].setSize(Vector2f(60.f, 600.f));

		rectangle[5].setPosition(Vector2f(1585.f, 235.f)); //права€ стена у базы
		rectangle[5].setSize(Vector2f(60.f, 600.f));

		

		FloatRect tankBounds = sprite->getGlobalBounds();
		FloatRect rectangleBounds[6];


		for (int i = 0; i < 6; i++) {
			rectangleBounds[i] = rectangle[i].getGlobalBounds();
			for(int j = 0; j < proj->size(); j++)
				if (proj->at(j).getSprite()->getGlobalBounds().intersects(rectangleBounds[i]))
				{
					std::swap(proj->at(j), proj->back());
					proj->pop_back();
					soundMiss.play();
				}


			if (tankBounds.intersects(rectangleBounds[i])) {
				return rectangle[i].getPosition();
			}


		}

		for (int j = 0; j < proj->size(); j++)
			if (proj->at(j).getSprite()->getGlobalBounds().intersects(enemyTank->getSprite()->getGlobalBounds()))
			{
				std::swap(proj->at(j), proj->back());
				proj->pop_back();
				enemyTank->takeHit();
				soundHit.play();
			}

		if (tankBounds.intersects(enemyTank->getSprite()->getGlobalBounds()))
		{
			return enemyTank->getSprite()->getPosition();
		}
		


		return Vector2f(-100., -100.);
	}
	void takeHit()
	{
		health--;
		if (health == 0)
		{
			dead = true;
			sprite->setPosition(-100, -100);
			x = -100;
			y = -100;
			soundDie.play();
			
		}
		healthBar->pop_back();
	}

	void setEnemyTank(Tank * tank) {
		this->enemyTank = tank;
	}
};



class Map : public Object
{
public:
	bool isCreated;
	//ћасив клеточек (27 по вертикали, 48 по горизонтали)
	//ќдна клеточка - 40 на 40 пикселей
	int world[27][48] = {0};

	//ƒва танка игроков
	Tank* tank1;
	Tank* tank2;

	//
	Wall* wall;

	//
	Castle* castle1;
	Castle* castle2;



	//1- где надо установить
	void setWorld() {
		int m = 0;
		int k = 26;

		// Ѕоковые кра€
		for (int n = 0; n < 48; n++) {
				world[m][n] = 1;
				world[k][n] = 1;
		}
		k = 47;

		//¬ерхний и нижний кра€
		for (int n = 0; n < 27; n++) {
			world[n][m] = 1;
			world[n][k] = 1;
		}

		//—тена у базы
		for (int n = 6; n < 21; n++) {
			world[n][7] = 1;
			world[n][40] = 1; 
			//world[n][24] = 1;
		}

	}

	Map() : Object("background.png") {
		setWorld();
		isCreated = false;
		wall = new Wall("palikka2.png");

		//
		castle1 = new Castle("castle1.png", 0);
		castle2 = new Castle("castle2.png", 0);

		

		createTanks();

		
	}

	void createTanks()
	{			

			tank1 = new Tank("tank1.png", -90, Vector2f(150, 720));
			tank2 = new Tank("tank2.png", 90, Vector2f(1780, 320));

			tank1->setEnemyTank(tank2);
			tank2->setEnemyTank(tank1);
			tank1->createHealthBar(Vector2f(100, 940));
			tank2->createHealthBar(Vector2f(1600, 940));

	}

	void checkCollision() {
		FloatRect spriteBounds1 = tank1->getSprite()->getGlobalBounds();

	}


	//Vector2f checkTankCollision(Tank *tank) {
	//	if (tank1 != tank)
	//	{
	//		FloatRect tankEnemy = tank1->getSprite()->getGlobalBounds();

	//		if (tank->getSprite()->getGlobalBounds().intersects(tankEnemy))
	//		{
	//			return tank1->getSprite()->getPosition();
	//		}
	//	}
	//	return Vector2f(-100., -100.);
	//}

	void update(RenderWindow * window) {


		window->draw(*sprite);


		for (int m = 0; m < 27; m++) {
			for (int n = 0; n < 48; n++) {
				if(world[m][n] == 1)
				{
					wall->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
					window->draw(*wall->getSprite());
				}
			}

		}
		//std::cout << std::endl;

		if(!tank1->dead)
			window->draw(*tank1->getSprite());
		if(!tank2->dead)
			window->draw(*tank2->getSprite());

		for (int i = 0; i < tank1->proj->size(); i++)
		{
  			window->draw(*tank1->proj->at(i).getSprite());
		}

		for (int i = 0; i < tank2->proj->size(); i++)
		{
			window->draw(*tank2->proj->at(i).getSprite());
		}


		for (int i = 0; i < tank1->healthBar->size(); i++)
			window->draw(*tank1->healthBar->at(i).getSprite());
		
		for (int i = 0; i < tank2->healthBar->size(); i++)
			window->draw(*tank2->healthBar->at(i).getSprite());


	}
	


};

