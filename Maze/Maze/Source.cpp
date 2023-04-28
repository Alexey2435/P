#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int TileSize = 50;

int height = 21;
int width = 21;

bool deadend(int, int, int**, int, int); // Вспомогательная функция, определяет тупики
void mazemake(int**, int, int); // Алгоритм генерации
//Проход = 1
//Стена = 0
//Финиш = 2
//Посещено = 5

bool deadend(int x, int y, int** maze, int height, int width) {
	int a = 0;

	if (x != 1) {
		if (maze[y][x - 2] == 1)
			a += 1;
	}
	else a += 1;

	if (y != 1) {
		if (maze[y - 2][x] == 1)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) {
		if (maze[y][x + 2] == 1)
			a += 1;
	}
	else a += 1;

	if (y != height - 2) {
		if (maze[y + 2][x] == 1)
			a += 1;
	}
	else a += 1;

	if (a == 4)
		return 1;
	else
		return 0;
}

void mazemake(int** maze, int height, int width) {
	int x, y, c, count;
	bool b;

	for (int i = 0; i < height; i++) // Заполнение стенами
		for (int j = 0; j < width; j++)
			maze[i][j] = 0;

	x = 1; y = 1; count = 0; // Стартовая точка и счетчик
	while (count < 10000) {
		maze[y][x] = 1; 
		count++;
		while (1) { // Бесконечный цикл, прерывается только тупиком
			c = rand() % 4;
			switch (c) {
			case 0: if (y != 1)
				if (maze[y - 2][x] == 0) { // Вверх
					maze[y - 1][x] = 1;
					maze[y - 2][x] = 1;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (maze[y + 2][x] == 0) { // Вниз
					maze[y + 1][x] = 1;
					maze[y + 2][x] = 1;
					y += 2;
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == 0) { // Налево
					maze[y][x - 1] = 1;
					maze[y][x - 2] = 1;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (maze[y][x + 2] == 0) { // Направо
					maze[y][x + 1] = 1;
					maze[y][x + 2] = 1;
					x += 2;
				}
			}
			if (deadend(x, y, maze, height, width)) 
				break;
		}

		if (deadend(x, y, maze, height, width)) // Выход из тупика
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != 1);
	}
}

float OffsetX = TileSize * (0);		//Установка поля зрения центром
float OffsetY = TileSize * (0);		//на стартовую позицию игрока

bool Win = false;
int pe = 2;

class setSound {
public:
	SoundBuffer s1, s2, s3;
	Sound time, win;

	setSound() {
		s3.loadFromFile("Sound/win.ogg");

		time.setBuffer(s1);
		win.setBuffer(s3);

		time.setLoop(true);
	}
};

setSound sound;

/*class Stopwatch {
public:
	Sprite min[2], sec[2], toc;
	int m[2], s[2], ms;

	Stopwatch(Texture& image) {
		for (int i = 0; i < 2; i++) {
			min[i].setTexture(image);
			sec[i].setTexture(image);

			min[i].setPosition(25 * i, 5);
			sec[i].setPosition(75 + 25 * i, 5);

			min[i].setTextureRect(IntRect(0, 0, 25, 36));
			sec[i].setTextureRect(IntRect(0, 0, 25, 36));

			m[i] = 0;
			s[i] = 0;
		}

		toc.setTexture(image);
		toc.setPosition(50, 5);
		toc.setTextureRect(IntRect(250, 0, 25, 36));

		ms = 0;
	}

	void update() {
		if (!Win && pe == 1)
			ms++;

		if (ms >= 1000) {
			s[1]++;
			ms = 0;
		}

		if (s[1] == 10) {
			s[0]++;
			s[1] = 0;
		}

		if (s[0] == 6) {
			m[1]++;
			s[0] = 0;
		}

		if (m[1] == 10) {
			m[0]++;
			m[1] = 0;
		}

		for (int i = 0; i < 2; i++) {
			sec[i].setTextureRect(IntRect(25 * s[i], 0, 25, 36));
			min[i].setTextureRect(IntRect(25 * m[i], 0, 25, 36));
		}
	}
};*/

void Visit(int** maze, int x, int y, Sprite plat, RenderWindow& window)
{
	if (!Win) {
		if (x < 1 || x >= width || y < 1 || y >= height) return;
		if (maze[y][x] == 2) {
			maze[y][x] = 5;

			Win = true;

			sound.win.play();
			exit;
		}
		if (maze[y][x] != 1) return;
		maze[y][x] = 5;

		window.clear(Color::White);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (maze[i][j] == 0)
					plat.setTextureRect(IntRect(0, 0, TileSize, TileSize));
				if (maze[i][j] == 5)
					plat.setTextureRect(IntRect(TileSize, 0, TileSize, TileSize));
				if (maze[i][j] == 2)
					plat.setTextureRect(IntRect(TileSize * 2, 0, TileSize, TileSize));
				if (maze[i][j] == 1)
					continue;

				plat.setPosition(j * TileSize - OffsetX, i * TileSize - OffsetY);
				window.draw(plat);
			}
		}
		window.display();

		Sleep(200);

		Visit(maze, x + 1, y, plat, window);
		Visit(maze, x, y + 1, plat, window);
		Visit(maze, x - 1, y, plat, window);
		Visit(maze, x, y - 1, plat, window);
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	cout << "Input height and width (only odd sizes):" << "\n";
	cin >> height;
	cin >> width;
	if (height % 2 == 0) {
		height++;
	}
	if (width % 2 == 0) {
		width++;
	}
	system("cls");

	height += 2;
	width += 2;

	int** maze = new int* [height];
	for (int i = 0; i < height; i++)
		maze[i] = new int[width];

	mazemake(maze, height, width);

	RenderWindow window(VideoMode(width * TileSize, height * TileSize), "Maze!");

	Texture t;
	t.loadFromFile("Paint/Bplat.png");
	Sprite plat(t);

	int x = 1, y = 1;		//Cтартовые координаты
	int newx = 0, newy = 0;
	//maze[y][x] = 5;			//Спавн игрока
	maze[height - 1][width - 2] = 2;		//Спавн финиша

	Texture w;
	w.loadFromFile("Paint/win.png");
	Sprite win(w);
	win.setPosition(TileSize * width / 2 - 150, TileSize * height / 2 - 50);

	/*Texture ti;
	ti.loadFromFile("Paint/time.png");
	Stopwatch watch(ti);*/

	/*Texture p;
	p.loadFromFile("Paint/pause.png");
	Sprite pause(p);
	pause.setPosition(80, 140);*/

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.key.code == Keyboard::Space) Visit(maze, 1, 1, plat, window);

			/*if (event.type == Event::KeyPressed) {
				if (!Win) {
					if (pe == 1) {
						newx = x;
						newy = y;

						if (event.key.code == Keyboard::Right) {
							newx += 1;

							//if (maze[newy][newx] == 1)
								//OffsetX += TileSize;
						}
						if (event.key.code == Keyboard::Left) {
							newx -= 1;

							//if (maze[newy][newx] == 1)
								//OffsetX -= TileSize;
						}
						if (event.key.code == Keyboard::Up) {
							newy -= 1;

							//if (maze[newy][newx] == 1)
								//OffsetY -= TileSize;
						}
						if (event.key.code == Keyboard::Down) {
							newy += 1;

							//if (maze[newy][newx] == 1)
								//OffsetY += TileSize;
						}
					}

					if (event.key.code == Keyboard::Space) {
						pe++;
					}
				}
			}*/
		}

		/*if (maze[newy][newx] == 1) {
			maze[y][x] = 1;

			maze[newy][newx] = 5;

			x = newx;
			y = newy;
		}
		if (maze[newy][newx] == 2) {
			maze[y][x] = ' ';

			maze[newy][newx] = 5;

			x = newx;
			y = newy;

			Win = true;

			sound.time.stop();
			sound.win.play();
		}*/

		//watch.update();
		window.clear(Color::White);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (maze[i][j] == 0)
					plat.setTextureRect(IntRect(0, 0, TileSize, TileSize));
				if (maze[i][j] == 5)
					plat.setTextureRect(IntRect(TileSize, 0, TileSize, TileSize));
				if (maze[i][j] == 2)
					plat.setTextureRect(IntRect(TileSize * 2, 0, TileSize, TileSize));
				if (maze[i][j] == 1)
					continue;

				plat.setPosition(j * TileSize - OffsetX, i * TileSize - OffsetY);
				window.draw(plat);
			}
		}
		if (Win) {
			window.draw(win);
			if (event.key.code == Keyboard::Escape)
				return 0;
		}
			
		/*for (int i = 0; i < 2; i++) {
			window.draw(watch.min[i]);
			window.draw(watch.sec[i]);
		}
		window.draw(watch.toc);*/
		/*if (pe == 2)
			window.draw(pause);*/
		window.display();
	}

	for (int i = 0; i < height; i++)
		delete[] maze[i];
	delete[] maze;

	return 0;
}