#include "Sheet.hpp"
#include "Position.hpp"

Sheet::Sheet()
{
	_lenght = _width = _height = _x = _y = 0;
}

Sheet::Sheet(const int& x, const int& y, const int& height,
             const int& lenght, const int& width) : Position(x, y, height)
{
    _lenght = _width = 0;
	set_lenght(lenght);
	set_width(width);
}

Sheet::Sheet(const Sheet& other_sheet)
{
	_lenght = other_sheet._lenght;
	_width = other_sheet._width;
	_height = other_sheet._height;
	_x = other_sheet._x;
	_y = other_sheet._y;
}

int Sheet::get_lenght() const
{
	return _lenght;
}

int Sheet::get_width() const
{
	return _width;
}


void Sheet::set_lenght(const int& lenght)
{
	if (lenght > 0)
		_lenght = lenght;
}

void Sheet::set_width(const int& width)
{
	if (width > 0)
		_width = width;
}

bool Sheet::operator==(const Sheet& other) const
{
	return _lenght == other.get_lenght() && _width == other.get_width()
		&& _height == other.get_height() && _x == other.get_x() && _y == other.get_y();
}

bool Sheet::operator!=(const Sheet& other) const
{
	return !(*this == other);
}

std::string Sheet::what_is_it() const
{
    return "class Sheet";
}
