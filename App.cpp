#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define h 20 // height of the game window
#define w 20 // width of the game window
#define maxsize ((h-2)*(w-2)) // max possible size of the snake
using namespace std;

char buffer[h][w]; // buffer to store the game screen data/pixels

// structure of any location on the game screen
// used to represent a part of snake or a food particle
struct cell {
	int x, y;
};

cell snake[maxsize]; // an array of parts of snake
cell food; // used to store location of food
cell last_tail; // used to keep track of tail of snake in the last frame
int food_exists = 0; // flag to indicate if food exists(not eaten) or doesn't exist(eaten)
int head = -1; // a pointer that points the head of snake in the snake array
int dir = 2; // direction of snake head
int score = 0; // used to store and accumulate the player score
int game_over = 0; // flag to indicate if game is over or not


void init_buffer(); // fills the buffer with walls on boundary and empty space inside
void render(); // displays the buffer on the screen
void bind_snake(); // the location of snake parts in snake array is binded(transferred into buffer) with buffer
void grow_snake(); // this function when called grows the snake by one unit
void crawl(); // when called this function the snake moves forward by one unit 
void control(); // this function is called every frame to handle the keyboard input to control the snake 
void generate_food(); // generates a food in random location if food doesn't exists
void eat_food(); // checks if food is eaten and then grows the snake by calling grow_snake()
void detect_collision(); // detects collision and controls gameover mechanism
void shift_to_right();

int main() {
	srand((unsigned int)time(0));
	char play = 'y';
	cout << "Use the following key to control the snake: " << endl;
	cout << "w: Up\ns: Down\na: Left\nd: Right" << endl;
	cout << "Press any key to start the game...";
	play = _getch();
	play = 'y';
	while (play == 'y') {
		dir = 2;
		score = 0;
		game_over = 0;
		head = -1;
		grow_snake();
		food_exists = 0;
		while (!game_over) {
			init_buffer();
			bind_snake();
			generate_food();
			render();
			control();
			last_tail = snake[0];
			crawl();
			detect_collision();
			eat_food();
			Sleep(100);
		}
		play = 'n';
		cout << "               Game Over!"<<endl;
		Sleep(1000);
		cout << "            Play again(y/n)? ";
		cin >> play;
	}
	return 0;
}

void shift_to_right() {
	for (int i = head; i >= 0; i--) {
		snake[i + 1] = snake[i];
	}
	head++;
}

void grow_snake() {
	cell new_cell;
	if (head == -1) {
		head++;
		new_cell.x = w / 2; new_cell.y = h / 2;
		snake[head] = new_cell;
	}
	else {
		shift_to_right();
		snake[0] = last_tail;
	}
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
	if (game_over) Beep(300, 500);
}

void eat_food() {
	if (snake[head].x == food.x && snake[head].y == food.y) {
		food_exists = 0;
		grow_snake();
		Beep(2000, 60);
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

void bind_snake() {
	for (int i = 0; i <= head; i++) {
		if (snake[i].x > 0 && snake[i].x < w - 1 && snake[i].y > 0 && snake[i].y < h - 1)
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
		buffer[i][0] = 'H';
		buffer[i][w-1] = 'H';
	}
	for (int i = 0; i < w; i++) {
		buffer[0][i] = 'N';
		buffer[h-1][i] = 'N';
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
	cout << "                Score: " << score << endl;
}

void generate_food() {
	if (!food_exists) {
		int x, y;
		x = 1 + rand() % (w - 2);
		y = 1 + rand() % (h - 2);
		for (int i = 0; i <= head; i++) {
			if (snake[i].x == x && snake[i].y == y) generate_food();
		}
		food.x = x;
		food.y = y;
		food_exists = 1;
	}
	buffer[food.y][food.x] = '*';
}