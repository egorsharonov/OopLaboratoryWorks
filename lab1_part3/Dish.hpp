#pragma once
#include "Position.hpp"

class Dish : public Position
{
protected:
	int _radius;
public:
    Dish(int = 0, int = 0, int = 0, int = 0);
	int get_radius() const;
	void set_radius(const int);

    virtual std::string what_is_it() const override;
};
