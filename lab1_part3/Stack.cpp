#include "Stack.hpp"


Stack::Node::Node(const Position& object, Node* p_prev)
{
	_p_next = nullptr;
	_p_prev = p_prev;

	if (object.what_is_it() == "class Sheet")
		_value = new Sheet((Sheet&)object);
	else
		_value = new Dish((Dish&)object);
}

bool Stack::Node::operator==(const Node& other) const
{
	return *_value == *(other._value);
}

bool Stack::Node::operator!=(const Node& other) const { return !(*this == other); }




Stack::iterator::iterator(Node* node) { _node = node; }
Stack::iterator::iterator(const iterator& iter) { _node = iter._node; }

Position& Stack::iterator::operator*() { return *(_node->_value); }

Stack::iterator& Stack::iterator::operator++()
{
	_node = _node->_p_next;
	return *this;
}

Stack::iterator Stack::iterator::operator++(int a)
{
	_node = _node->_p_next;

	return _node->_p_prev;
}

Stack::iterator& Stack::iterator::operator--()
{
	_node = _node->_p_prev;
	return *this;
}

Stack::iterator Stack::iterator::operator--(int a)
{
	_node = _node->_p_prev;

	return _node->_p_next;
}

bool Stack::iterator::operator==(const iterator& other) const { return (_node == other._node); }
bool Stack::iterator::operator!=(const iterator& other) const { return !(_node == other._node); }



Stack::Stack()
{
	_size = 0;
	_head = nullptr;
	_tail = nullptr;
}

Stack::Stack(const Stack& stack)
{
	_size = 0;
	_head = nullptr;
	_tail = nullptr;

	Node* current_node = stack._head;
	for (int i = 0; i < stack._size; ++i)
	{
		this->add(*(current_node->_value));
		current_node = current_node->_p_next;
	}
}


Stack& Stack::operator=(const Stack& other_stack)
{
	clear();

	Node* current_node = other_stack._head;
	for (int i = 0; i < other_stack._size; ++i)
	{
		this->add(*(current_node->_value));
		current_node = current_node->_p_next;
	}

	return *this;
}

Stack::~Stack() { clear(); }

int Stack::get_size() const { return _size; }

void Stack::add(const Position& new_element)
{
	if (_size == 0)
	{
		_head = new Node(new_element);
		_tail = _head;
		++_size;
	}
	else
	{
		Node* to_add = new Node(new_element, _tail);
		_tail->_p_next = to_add;

		_tail = _tail->_p_next;
		++_size;
	}
}

void Stack::pop()
{
	if (_size == 0)
		return;
	else if (_size == 1)
	{
		delete _tail;
		_head = _tail = new Node();
		--_size;
	}
	else
	{
		_tail = _tail->_p_prev;
		delete _tail->_p_next;
		_tail->_p_next = nullptr;

		--_size;
	}
}

void Stack::clear()
{
	while (_size)
		pop();
}

bool Stack::is_in_balance() const
{
	if (_size == 0)
		return true;
	else
	{
		int sum_x = 0;
		int sum_y = 0;

		Node* current_node = _head;
		while (current_node != nullptr)
		{
			if (current_node->_value->what_is_it() == "class Sheet")
			{
				sum_x += current_node->_value->get_x() + ((Sheet*)(current_node->_value))->get_width()/2.0;
				sum_y += current_node->_value->get_y() + ((Sheet*)(current_node->_value))->get_height()/2.0;
			}
			else
			{
				sum_x += current_node->_value->get_x();
				sum_y += current_node->_value->get_y();
			}
			current_node = current_node->_p_next;
		}

		double average_x = (double)sum_x / _size;
		double average_y = (double)sum_y / _size;

		// x, y листа - это коорд. центра масс листа
		if (_head->_value->what_is_it() == "class Sheet")
			return (average_x > _head->_value->get_x()) &&
			(average_x < (_head->_value->get_x() + ((Sheet*)(_head->_value))->get_width())) &&
				(average_y > _head->_value->get_y()) &&
				(average_y < (_head->_value->get_y() + ((Sheet*)(_head->_value))->get_height()));
		else
			return pow(average_x - _head->_value->get_x(), 2) +
				pow(average_y - _head->_value->get_y(), 2)
				< pow(((Dish&)(_head->_value)).get_radius(), 2);
	}
}

void Stack::write(std::string path)
{
	std::ofstream fout(path);

	for (auto it = this->begin(); it != this->end(); ++it)
	{
		if ((*it).what_is_it() == "class Sheet")
			fout << (*it).what_is_it() << '\n' <<
			(*it).get_x() << '\n' << 
			(*it).get_y() << '\n' <<
			((Sheet&)(*it)).get_height() << 
			'\n' << ((Sheet&)(*it)).get_lenght() <<
			'\n' << ((Sheet&)(*it)).get_width() << '\n';

		else
			fout << (*it).what_is_it() << '\n' << (*it).get_x() << '\n' << (*it).get_y() << '\n' <<
			((Dish&)(*it)).get_height() << '\n' << ((Dish&)(*it)).get_radius() << '\n';
	}
	fout.close();
}

bool Stack::read(std::string path)
{
	std::ifstream fin(path);

	if (!fin.is_open())
		return false;
	else
	{
		clear();

		while (!fin.eof())
		{
			std::string lenght = "";
			std::string width = "";
			std::string height = "";
			std::string x = "";
			std::string y = "";
			std::string radius = "";
			std::string what_is_it = "";
			getline(fin, what_is_it);

			if (what_is_it == "class Sheet")
			{
				getline(fin, x);
				getline(fin, y);
				getline(fin, height);
				getline(fin, lenght);
				getline(fin, width);

				Sheet sheet;
				sheet.set_x(stoi(x));
				sheet.set_y(stoi(y));
				sheet.set_height(stoi(height));
				sheet.set_lenght(stoi(lenght));
				sheet.set_width(stoi(width));

				this->add(sheet);
			}
			else if (what_is_it == "class Dish")
			{
				getline(fin, x);
				getline(fin, y);
				getline(fin, height);
				getline(fin, radius);

				Dish dish;
				dish.set_x(stoi(x));
				dish.set_y(stoi(y));
				dish.set_height(stoi(height));
				dish.set_radius(stoi(radius));

				this->add(dish);

			}
			else
				return true;
		}

	}
}

Position& Stack::show() { return *(_tail->_value); }

Stack::iterator Stack::begin() const { return iterator(_head); }

Stack::iterator Stack::end() const { return iterator(_tail->_p_next); }

bool Stack::operator==(const Stack& other_stack) const
{
	if (this->get_size() != other_stack.get_size())
		return false;
	else
	{
		Node* this_node = this->_head;
		Node* other_node = other_stack._head;

		for (int i = 0; i < this->get_size(); ++i)
			if (*this_node != *other_node)
				return false;
			else
			{
				this_node = this_node->_p_next;
				other_node = other_node->_p_next;
			}
		
		return true;
	}
}

bool Stack::operator!=(const Stack& other_stack) const
{
	return !(*this == other_stack);
}
