#pragma once
#include <iostream>

class Position
{
protected:
	int _height;
	int _x, _y;
public:
    Position(int = 0, int = 0, int = 0);

	int get_height() const;
	int get_x() const;
	int get_y() const;

	void set_height(const int&);
	void set_x(const int&);
	void set_y(const int&);

    virtual std::string what_is_it() const;

	bool operator==(const Position&) const;
	bool operator!=(const Position&) const;
};
