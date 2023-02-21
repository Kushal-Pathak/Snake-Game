#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define h 27
#define w 39
#define maxsize ((h-2)*(w-2))
using namespace std;

char buffer[h][w];

struct cell {
	int x, y;
};

cell snake[maxsize];
cell food;
int food_exists = 0;
int head = -1;
int dir = 2;
int score = 0;
int  game_over = 0;


void init_buffer();
void render();
void bind_snake();
void grow_snake();
void crawl();
void control();
void generate_food();
void eat_food();
void detect_collision();

int main() {
	srand((unsigned int)time(0));
	grow_snake();
	while (!game_over) {
		init_buffer();
		bind_snake();
		generate_food();
		render();
		control();
		crawl();
		eat_food();
		detect_collision();
		Sleep(200);
	}
	cout << " Game Over!";
	_getch();
	return 0;
}

void detect_collision() {
	if (snake[head].x >= w - 1 || snake[head].x <= 0) {
		game_over = 1;
	}
	if (snake[head].y >= h - 1 || snake[head].y <= 0) {
		game_over = 1;
	}
	for (int i = 0; i < head; i++) {
		if (snake[i].x == snake[head].x && snake[i].y == snake[head].y) game_over = 1;
	}
}

void eat_food() {
	if (snake[head].x == food.x && snake[head].y == food.y) {
		food_exists = 0;
		grow_snake();
		score++;
	}
}

void control() {
	if (_kbhit()) {
		char c = _getch();
		if (dir == 1 || dir == 3) {
			switch (c) {
			case 'a': dir = 4;  break; // left
			case 'd': dir = 2; break; // right
			}
		}
		if (dir == 4 || dir == 2) {
			switch(c){
			case 'w': dir = 1; break; // up
			case 's': dir = 3; break; // down
			}
		}
	}
}

void crawl() {
	int dx = 0, dy = 0;
	for (int i = 0; i < head; i++) {
		snake[i].x = snake[i + 1].x;
		snake[i].y = snake[i + 1].y;
	}
	switch (dir) {
	case 1: dy = -1; break;
	case 2: dx = 1; break;
	case 3: dy = 1; break;
	case 4: dx = -1; break;
	}
	snake[head].x += dx;
	snake[head].y += dy;
}

void grow_snake() {
	cell new_cell;
	if (head == -1) {
		new_cell.x = w / 2; new_cell.y = h / 2;
		snake[0] = new_cell;
		head++;
	}
	else {
		int dx = 0, dy = 0;
		switch (dir) {
		case 1: dy = -1; break;
		case 2: dx = 1; break;
		case 3: dy = 1; break;
		case 4: dx = -1; break;
		}
		new_cell.x = snake[head].x + dx; new_cell.y = snake[head].y + dy;
		head++;
		snake[head] = new_cell;
	}
}

void bind_snake() {
	for (int i = 0; i <= head; i++) {
		buffer[snake[i].y][snake[i].x] = '#';
	}
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			buffer[i][j] = ' ';
		}
	}
	for (int i = 0; i < h; i++) {
		buffer[i][0] = '|';
		buffer[i][w-1] = '|';
	}
	for (int i = 0; i < w; i++) {
		buffer[0][i] = '=';
		buffer[h-1][i] = '=';
	}
}

void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j]<<' ';
		}
		cout << endl;
	}
	cout << "Score: " << score;
}

void generate_food() {
	if (!food_exists) {
		int x, y;
		x = 1 + rand() % (w - 1);
		y = 1 + rand() % (h - 1);
		for (int i = 0; i <= head; i++) {
			if (snake[i].x == x && snake[i].y == y) generate_food();
		}
		food.x = x;
		food.y = y;
		food_exists = 1;
	}
	buffer[food.y][food.x] = 'O';
}