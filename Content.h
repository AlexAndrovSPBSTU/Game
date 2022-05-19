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
		map->load(window);

		loadMoving();
	}

	void loadMoving() {
		if (Keyboard::isKeyPressed) {
			//Прогрузка изменения движений
			if (Keyboard::isKeyPressed(Keyboard::Key::W))
				map->tank1->move(direction::Up);
			if (Keyboard::isKeyPressed(Keyboard::Key::S))
				map->tank1->move(direction::Down);
			if (Keyboard::isKeyPressed(Keyboard::Key::A))
				map->tank1->move(direction::Left);
			if (Keyboard::isKeyPressed(Keyboard::Key::D))
				map->tank1->move(direction::Right);



			if (Keyboard::isKeyPressed(Keyboard::Key::Up))
				map->tank2->move(direction::Up);
			if (Keyboard::isKeyPressed(Keyboard::Key::Down))
				map->tank2->move(direction::Down);
			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
				map->tank2->move(direction::Left);
			if (Keyboard::isKeyPressed(Keyboard::Key::Right))
				map->tank2->move(direction::Right);
		}
	}



};

