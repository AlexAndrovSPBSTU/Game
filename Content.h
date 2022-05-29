#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Content {
private:
	Map* map;

public:
	Content() {
		map = new Map();
	
	}

	void loadMap(RenderWindow* window){
		//Прогрузка карты
		map->update(window);

		//loadMoving();
	}

	void loadMoving() {
		bool flag = false; 

		map->tank1->updateProjectiles();
		map->tank2->updateProjectiles();
		map->tank1->isCollided();
		map->tank2->isCollided();

		if (Keyboard::isKeyPressed) {	
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				map->tank1->move(direction::Up);
			if (Keyboard::isKeyPressed(Keyboard::Key::S))
			{
				flag = true;
				map->tank1->move(direction::Down);
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && flag)
				map->tank1->move(direction::Right);
			if (Keyboard::isKeyPressed(Keyboard::Key::A) && !flag)
				map->tank1->move(direction::Left);
			if (Keyboard::isKeyPressed(Keyboard::Key::D) && flag)
				map->tank1->move(direction::Left);
			if (Keyboard::isKeyPressed(Keyboard::Key::D) && !flag)
				map->tank1->move(direction::Right);
			//Прогрузка изменения движений

			if (Keyboard::isKeyPressed(Keyboard::Key::Space))
				map->tank1->shoot();
				

			if (Keyboard::isKeyPressed(Keyboard::Key::F1))
				map->createTanks();






			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				map->tank2->move(direction::Up);
			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
				map->tank2->move(direction::Down);
			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
				map->tank2->move(direction::Left);
			if (Keyboard::isKeyPressed(Keyboard::Key::Right))
				map->tank2->move(direction::Right);
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
				map->tank2->shoot();

		}
	}



};

