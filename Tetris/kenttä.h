#pragma once
#include <string>
#include <vector>
using namespace std;

struct Point {
	bool operator ==(const Point& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator !=(const Point& rhs) const
	{
		return x != rhs.x && y != rhs.y;
	}

	int x;
	int y;
	
};


class kentt‰
{
public:
	kentt‰(int leveys,int korkeus);
	//tulostetaan kentt‰ rivi kerrallaan n‰kyviin
	void print();
	//boolean, kertoo onko peli ohi vai ei
	bool game_over();
	//tarkistaa onko kysytty piste osa tetrominoa
	bool isInSquare(Point&);
	//uusi palikka aina kun edellinen on pys‰htynyt
	void add_parts();
	//koko palikka liikkuu alas
	void move_part_down();
	//koko palikka liikkuu vasempaan
	void move_part_left();
	//koko palikka liikkuu oikealle
	void move_part_right();
	//k‰‰nt‰‰ palikkaa keskipisteen ymp‰ri 90 astetta myˆt‰p‰iv‰‰n
	void rotate_parts();
	~kentt‰();
private:
	int korkeus_;

	int leveys_;

	bool game_is_over = false;

	std::vector<Point> parts_;
};

