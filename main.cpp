#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

float timer = 0;
//������� ����������
float delay = 0.3f;

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "The Game!");

	Texture tanks, castleT, wall;
	tanks.loadFromFile("sprites.png");
	castleT.loadFromFile("castle.gif");
	wall.loadFromFile("wall.png");

	Sprite tank(tanks), castle1(castleT), castle2(castleT), pieceOfWall(wall);

	//����
	tank.setTextureRect(IntRect(0, 0, 180, 200));
	tank.setScale(Vector2f(0.5, 0.5));
	//������ �����
	castle1.setPosition(340, 340);
	castle1.setScale(Vector2f(0.5, 0.5));
	//������ �����
	castle2.setPosition(1580, 340);
	castle2.setScale(Vector2f(0.5, 0.5));
	//����� �����
	pieceOfWall.setScale(Vector2f(0.1f, 0.15f));
	pieceOfWall.rotate(90);
	pieceOfWall.setPosition(240, 340);

	for (int i = 0; i < 7; i++) {
	}


	while (window.isOpen())
	{
		// ������������ ������� � �����
		Event event;
		Clock clock;
		float time;
		// �������� �����, ��������� � ������ �������, � ������������ ��� � �������
		time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//���� timer ������� �� ������� ����������� ���� �������
		if (timer > delay) {



			timer = 0;
		}

		while (window.pollEvent(event))
		{

			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
			{
				// ����� ��������� ���
				window.close();
			}

		}

		// ��������� ����� ���� - �����
		window.clear(Color::White);

		window.draw(tank);
		window.draw(castle1);
		window.draw(castle2);
		window.draw(pieceOfWall);
		window.display();
	}

	return 0;
}



