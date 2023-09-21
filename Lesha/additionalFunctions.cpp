#include <iostream>
#include "list.h"


void printList(List& list)
{
    auto it = list.begin();
    for (int i = 0; i < list.getSize(); ++i, ++it) {
        std::cout << i << " " << *it;
    }
}
