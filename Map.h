#include <SFML/Graphics.hpp>
#include "Content.h"
#include "Constants.h"
#include <string>
#include <iostream>
#pragma once


using namespace sf;
using std::string;


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



class Tank : public Object,Transformable {
private:
	float dx, dy,x,y;

	float speed = 0.1f;
public:

	Tank(const string fileTexture, int angle,Vector2f vector): Object(fileTexture) {
		sprite->setScale(Vector2f(0.7f, 0.7f));
		sprite->rotate(angle);
		sprite->setPosition(vector);
		x = vector.x;
		y = vector.y;
		sprite->setOrigin(Vector2f(75.f, 85.f));
	}

	void move(direction d) {
		
		switch (d)
		{
		case Up: dy = TANKS_SPEED*sin((90 - sprite->getRotation()) * 3.14 /180); dx = TANKS_SPEED * cos((- 90 - sprite->getRotation()) * 3.14 / 180); break;
		case Down: dy = -TANKS_SPEED * sin((90 - sprite->getRotation()) * 3.14 / 180); dx = -TANKS_SPEED * cos((-90 - sprite->getRotation()) * 3.14 / 180); break;
		case Left:  sprite->rotate(-TANKS_SPEED ); dx = 0 ; dy = 0; break;
		case Right: sprite->rotate(TANKS_SPEED);  dx = 0; dy = 0; break;
			
		}

		x += dx ;
		y += dy;


		speed = 0.0f;
		sprite->setPosition(x, y);
		speed = 0.1f;
	}




};



class Map : public Object
{
public:
	bool isCreated;
	//Масив клеточек (27 по вертикали, 48 по горизонтали)
	//Одна клеточка - 40 на 40 пикселей
	int world[27][48] = {0};

	//Два танка игроков
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

		// Боковые края
		for (int n = 0; n < 48; n++) {
				world[m][n] = 1;
				world[k][n] = 1;
		}
		k = 47;

		//Верхний и нижний края
		for (int n = 0; n < 27; n++) {
			world[n][m] = 1;
			world[n][k] = 1;
		}

		//Стена у базы
		for (int n = 6; n < 21; n++) {
			world[n][7] = 1;
			world[n][40] = 1;
		}
										//Синие
		//Танк
		world[15][3] = 2;
		//Башня
		world[17][9] = 4;
										//Красные
		//Танк
		world[13][46] = 3;
		//Башня
		world[10][39] = 5;
	}



	Map() : Object("background.png") {
		setWorld();
		isCreated = false;
		wall = new Wall("palikka2.png");

		//
		castle1 = new Castle("castle1.png", 0);
		castle2 = new Castle("castle2.png", 0);

		tank1 = new Tank("tank1.png", -90, Vector2f(600, 720));
		tank2 = new Tank("tank2.png", 90, Vector2f(1240, 520));
	}


	void load(RenderWindow * window) {


	window->draw(*sprite);


		for (int m = 0; m < 27; m++) {
			for (int n = 0; n < 48; n++) {
				switch (world[m][n])
				{
				case 1:	
					wall->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
					window->draw(*wall->getSprite());
					break;
				//case 2:
				//	tank1->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
				//	window->draw(*tank1->getSprite());
				//	break;
				//case 3:
				//	tank2->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
				//	window->draw(*tank2->getSprite());
				//	break;

				case 4:
					castle1->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
					window->draw(*castle1->getSprite());
					break;

				case 5:
					castle2->getSprite()->setPosition(Vector2f((float)((n * PIXEL_IN_CELL) - 15), (float)((m * PIXEL_IN_CELL) - 5)));
					window->draw(*castle2->getSprite());
					break;

				}



			}

		}

			window->draw(*tank1->getSprite());
			window->draw(*tank2->getSprite());
	}

};

