#pragma once
#include "Position.hpp"
#include <iostream>

class Sheet : public Position
{
protected:
	int _lenght;
	int _width;
public:
	Sheet();
	Sheet(const int&, const int& = 0, const int& = 0,
		const int& = 0, const int& = 0);
	Sheet(const Sheet&);

	int get_lenght() const;
	int get_width() const;

	void set_lenght(const int&);
	void set_width(const int&);

	bool operator== (const Sheet&) const;
	bool operator!= (const Sheet&) const;

    virtual std::string what_is_it() const override;
};

