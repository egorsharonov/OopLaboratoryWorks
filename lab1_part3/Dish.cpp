#include "Dish.hpp"


Dish::Dish(int x, int y, int height, int radius) : Position(x, y, height)
{
	_radius = 0;
	set_radius(radius);
}

int Dish::get_radius() const
{
	return _radius;
}

void Dish::set_radius(const int radius)
{
    if (radius > 0)
		_radius = radius;
}

std::string Dish::what_is_it() const
{
	return "class Dish";
}
