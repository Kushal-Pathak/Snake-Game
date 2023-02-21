#include <iostream>
#include <conio.h>
#define h 27
#define w 39
#define max (h-2)*(w-2)
using namespace std;

char buffer[h][w];

struct cell {
	int x, y;
};

cell snake[max];
int head = -1;
int dir = 2;


void init_buffer();
void render();
void bind_snake();
void grow_snake();

int main() {
	init_buffer();
	grow_snake(); grow_snake(); dir = 3; grow_snake(); grow_snake();
	bind_snake();
	render();
	_getch();
	return 0;
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
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j]<<' ';
		}
		cout << endl;
	}
}