#include "Position.hpp"


Position::Position(int x, int y, int height)
{
    _x = _y = _height = 0;
	set_x(x);
	set_y(y);
    set_height(height);
}

int Position::get_height() const
{
	return _height;
}

int Position::get_x() const
{
	return _x;
}

int Position::get_y() const
{
	return _y;
}

void Position::set_height(const int& height)
{
	if (height > 0)
		_height = height;
}

void Position::set_x(const int& x)
{
	if (x > 0)
		_x = x;
}

void Position::set_y(const int& y)
{
	if (y > 0)
		_y = y;
}

std::string Position::what_is_it() const
{
	return "class Position";
}

bool Position::operator==(const Position& other_object) const
{
	return _height == other_object.get_height() &&
		_x == other_object.get_x() && _y == other_object.get_y();
}

bool Position::operator!=(const Position& other_position) const
{
	return !(*this == other_position);
}

