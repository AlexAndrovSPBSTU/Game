#include <SFML/Graphics.hpp>
#include "Content.h"
#include "Map.h"

using namespace sf;
using namespace std;

float timer = 0;
//Частота обновления
float delay = 1./8000.f;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "The tanks!",sf::Style::Fullscreen);
	Content *content = new Content();
	Event event;
	Clock clock;
	float time;
	sf::Music music;
		
	music.openFromFile("ost.ogg");
	music.play();

	while (window.isOpen())
	{
		// Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Если timer выходит за частоту выполняется тело условия
		if (timer > delay) {
			//Управление
			content->loadMoving();

			timer = 0;
		}


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		//Прорисовка элементов
		window.clear();
		content->loadMap(&window);
		window.display();
	}



	return 0;
}



