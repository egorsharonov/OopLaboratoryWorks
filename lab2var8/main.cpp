#include "mainwindow.h"
#include <cassert>
#include <QApplication>
int main(int argc, char *argv[])
{
    std::string key3 = "key3", key2 = "key2", key1 = "key1";
    std::string wrongKey = "wrong_key";
    int value = 8, value2 = 123, value3 = 34;

    HashTable<string, int> emptyMap;
    assert(emptyMap.getSize() == 0);

    HashTable<string, int> map2;
    map2.insertItem(key1, value2);
    map2.insertItem(key2, value3);
    map2.insertItem(key3, value);
    map2.insertItem(key3, value);
    assert(map2.getSize() == 3);
    assert(map2[key3] == value);

    assert(map2.getSum()==165);

    map2.print();

    map2.deleteItem(key1);
    assert(map2.getSize() == 2);
    map2.deleteItem(wrongKey);
    assert(map2.getSize() == 2);


    assert(map2.find(key3) == true);
    assert(map2.find(wrongKey) == false);


    std::string path = "text.txt";
    map2.write(path);
    HashTable<string, int> map3;
    map3.read(path);
    assert(map3 == map2);

    map2.clear();
    assert(emptyMap == map2);


    std::cout << "all tests was completed";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}
