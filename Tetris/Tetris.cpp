#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "kenttä.h"
#include <stdlib.h>

// system("CLS");
// cout << "Hello" << flush;
// system("CLS");
#define YLOS 72
#define ALAS 80
#define VASEN 75
#define OIKEA 77


using namespace std;

const int leveys = 10;
const int korkeus = 20;

int main() {
	kenttä Tetris(leveys, korkeus);
	Tetris.print();
	int c = 0;
	while(!Tetris.game_over()){
		c = 0;
		switch ((c = _getch())) {
		case YLOS:
			Tetris.rotate_parts();
			break;
		case ALAS:
			Tetris.move_part_down();
			break;
		case VASEN:
			Tetris.move_part_left();
			break;
		case OIKEA:
			Tetris.move_part_right();
			break;
		default:
			continue;
		}	
	}

	return 0;
}
