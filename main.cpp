#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

float timer = 0;
//Частота обновления
float delay = 0.3f;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "The Game!");

	Texture tanks, castleT, wall;
	tanks.loadFromFile("sprites.png");
	castleT.loadFromFile("castle.gif");
	wall.loadFromFile("wall.png");

	Sprite tank(tanks), castle1(castleT), castle2(castleT), pieceOfWall(wall);

	//Танк
	tank.setTextureRect(IntRect(0, 0, 180, 200));
	tank.setScale(Vector2f(0.5, 0.5));
	//Первая башня
	castle1.setPosition(340, 340);
	castle1.setScale(Vector2f(0.5, 0.5));
	//Вторая башня
	castle2.setPosition(1580, 340);
	castle2.setScale(Vector2f(0.5, 0.5));
	//Кусок стены
	pieceOfWall.setScale(Vector2f(0.1f, 0.15f));
	pieceOfWall.rotate(90);
	pieceOfWall.setPosition(240, 340);

	for (int i = 0; i < 7; i++) {
	}


	while (window.isOpen())
	{
		// Обрабатываем события в цикле
		Event event;
		Clock clock;
		float time;
		// Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Если timer выходит за частоту выполняется тело условия
		if (timer > delay) {



			timer = 0;
		}

		while (window.pollEvent(event))
		{

			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
			{
				// тогда закрываем его
				window.close();
			}

		}

		// Установка цвета фона - белый
		window.clear(Color::White);

		window.draw(tank);
		window.draw(castle1);
		window.draw(castle2);
		window.draw(pieceOfWall);
		window.display();
	}

	return 0;
}



