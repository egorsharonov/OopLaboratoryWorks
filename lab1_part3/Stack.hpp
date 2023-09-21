#pragma once
#include "Sheet.hpp"
#include "Dish.hpp"
#include <fstream>
#include <iostream>
#include <cmath>


class Stack
{
private:
	struct Node
	{
		Node* _p_prev;
		Node* _p_next;
		Position* _value;

        Node(const Position& = Position(), Node* = nullptr);

		bool operator==(const Node&) const;
		bool operator!=(const Node&) const;
	};

	int _size;
	Node* _head;
	Node* _tail;

public:
	class iterator
	{
		Node* _node;
	public:
		iterator(Node*);
		iterator(const iterator&);

		Position& operator*();

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	};


	Stack();
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();

	int get_size() const;

	Position& show();
	void add(const Position&);
	void pop();
	void clear();

	bool is_in_balance() const;

	void write(std::string);
	bool read(std::string);

	iterator begin() const;
	iterator end() const;

	bool operator==(const Stack&) const;
	bool operator!=(const Stack&) const;
};
