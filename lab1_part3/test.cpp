#include "Sheet.hpp"
#include "Dish.hpp"
#include "Stack.hpp"
#include <iostream>
#include <cassert>
using namespace std;

void print(const Stack& stack)
{
	int count = 1;
	for (auto i = stack.begin(); i != stack.end(); ++i)
	{
		if ((*i).what_is_it() == "class Sheet")
			cout << "Stack" << count << "\nlenght: " << ((Sheet&)(*i)).get_lenght() << "\twidth: " <<
				((Sheet&)(*i)).get_width() << "\theight: " << ((Sheet&)(*i)).get_height() <<
				"\tx: " << (*i).get_x() << "\t\ty: " << (*i).get_y() << endl << endl;
		else
			cout << "Dish" << count << "\nheight: " << ((Dish&)(*i)).get_height() << "\t\tx: "
			<< ((Dish&)(*i)).get_x() << "\t\ty: " << ((Dish&)(*i)).get_y() << "\tradius: " 
			<< ((Dish&)(*i)).get_radius() << endl << endl;

		++count;
	}

}


int main()
{
	Stack list1;
	list1.add(Dish());
	list1.add(Sheet(1, -3));
	list1.add(Sheet());
	list1.add(Dish(-2, 2, 4, -10));
	list1.add(Sheet(1, 7, 2, 13, 9));


	int old_size = list1.get_size();
	list1.add(Sheet(1));
	assert(list1.get_size() == old_size + 1);

	Stack list2(list1);
	assert(list1 == list2);

	old_size = list1.get_size();
	list1.pop();
	assert(list1.get_size() == old_size - 1);
	assert(list1 != list2);

	list1.clear();
	assert(list1.get_size() == 0);

	std::string path = "text.txt";
	list2.write(path);
	list1.read(path);

	print(list1);
	print(list2);
	assert(list1 == list2);
	std::cout << "All tests passed succesfull!!!\n";
}