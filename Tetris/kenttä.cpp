#include "kenttä.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>



kenttä::kenttä(int leveys, int korkeus) :
	leveys_(leveys),
	korkeus_(korkeus){
	int x = 6;
	int y = 22;
	// L Shape
	parts_.push_back({ x, y });
	parts_.push_back({ x, y-1 });
	parts_.push_back({ x, y+1 });
	parts_.push_back({ x, y+2 });
	parts_.push_back({ x-1, y-1 });



}

void kenttä::print() {
	std::string space = std::string(33, ' ');
	for (int y = korkeus_; y > 0; y--) {
		std::cout << space << '#';
		for (int x = 0; x < leveys_; x++) {
			Point sijainti = { x,y };
			if (isInSquare(sijainti)) {
				std::cout << 'X';
			}
			else
				std::cout << ' ';
			
		}
		std::cout << '#' << std::endl;
	}
	std::cout << space << std::string(leveys_ + 2, '#') << std::endl;
}

bool kenttä::isInSquare(Point& sijainti) {
	for (unsigned int i = 0; i < parts_.size(); i++){
		if (parts_.at(i) == sijainti) {
			return 1;
		}

	}
	return 0;


}
bool kenttä::game_over() {
	return game_is_over;
}


void kenttä::move_part_down() {
	for (unsigned int i = 0; i < parts_.size(); i++) {
		parts_.at(i).y -= 1;
		std::cout << flush;
		system("CLS");
		print();
	}
	
}

void kenttä::move_part_right() {
	for (unsigned int i = 0; i < parts_.size(); i++) {
		parts_.at(i).x += 1;
		std::cout << flush;
		system("CLS");
		print();
	}

}

void kenttä::move_part_left() {
	for (unsigned int i = 0; i < parts_.size(); i++) {
		parts_.at(i).x -= 1;
		std::cout << flush;
		system("CLS");
		print();
	}

}

void kenttä::rotate_parts() {
	std::vector<Point> new_parts;
	int x_center = parts_.at(0).x;
	int y_center = parts_.at(0).y;
	if (x_center > 10 || x_center < 1)
		return;
	new_parts.push_back({ x_center,y_center });
	for (unsigned int i = 1; i < parts_.size(); i++) {
		if (parts_.at(i).x == x_center) {
			int new_y = y_center;
			int new_x = x_center + (parts_.at(i).y - y_center);
			new_parts.push_back({ new_x,new_y });
		}
		else if (parts_.at(i).y == y_center) {
			int new_x = x_center;
			int new_y = y_center + (x_center - parts_.at(i).x);
			new_parts.push_back({ new_x,new_y });
		}
		else {
			int new_x = x_center + (parts_.at(i).y-y_center);
			int new_y = y_center + (x_center - parts_.at(i).x);
			new_parts.push_back({ new_x,new_y });
		}
	}
	parts_ = new_parts;
	std::cout << flush;
	system("CLS");
	print();
}

kenttä::~kenttä()
{
}
