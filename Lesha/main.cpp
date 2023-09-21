#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>


void printList(List& lst);
void testing(){
    const int DEFAULT_PRICE = 0;
    const int DEFAULT_CAPACITY = 1;
    const std::string DEFAULT_NAME = "default";

    std::string name = "some_Item";
    int capacity = 80;
    int price = 125;

    Item obj1(name, price);
    assert(obj1.getName() == name or obj1.getName() == DEFAULT_NAME);
    assert(obj1.getCapacity() == capacity or obj1.getCapacity() == DEFAULT_CAPACITY);
    assert(obj1.getPrice() == price or obj1.getPrice() == DEFAULT_PRICE);

    Item obj2(obj1);
    assert(obj2.getName() == obj1.getName());
    assert(obj2.getCapacity() == obj1.getCapacity());
    assert(obj2.getPrice() == obj1.getPrice());

    Item obj3;
    assert(obj3.getName() == DEFAULT_NAME);
    assert(obj3.getCapacity() == DEFAULT_CAPACITY);
    assert(obj3.getPrice() == DEFAULT_PRICE);

    int capacity2 = 235;
    std::string name2 = "";
    int price2 = -32;
    obj3.setName(name2);
    obj3.setCapacity(capacity2);
    obj3.setPrice(price2);
    assert(obj3.getName() != name2 and obj3.getName() == DEFAULT_NAME);
    assert(obj3.getCapacity() == capacity2);
    assert(obj3.getPrice() != price2 and obj3.getPrice() == DEFAULT_PRICE);

    List list1;
    list1.pushBack({ "name1", 23, 12 });
    list1.pushBack({ "name2", 34, 181 });
    list1.pushBack({ "name2'", 34, 290 });

    int oldSize = list1.getSize();
    list1.pushBack({ "name3", 56, 100 });
    assert(list1.getSize() == oldSize + 1);

    List list2(list1);

    assert(list1 == list2);

    oldSize = list1.getSize();
    list1.del();
    assert(list1.getSize() == oldSize - 1);
    assert(list1 != list2);

    printList(list1);

    list1.popAll();
    assert(list1.getSize() == 0);

    std::string path = "text.txt";
    list2.write(path);
    list1.read(path);
    assert(list1 == list2);

    std::string DEFAUL_COINS_NAME = "Coins";
    Coins coin1(name, price);
    assert(coin1.getName() == name or coin1.getName() == DEFAUL_COINS_NAME);
    assert(coin1.getPrice() == price or coin1.getPrice() == DEFAULT_PRICE);

    Coins coin2(coin1);
    assert(coin2.getName() == coin1.getName());
    assert(coin2.getCapacity() == coin1.getCapacity());
    assert(coin2.getPrice() == coin1.getPrice());

    Coins coin3;
    assert(coin3.getName() == DEFAUL_COINS_NAME);
    assert(coin3.getCapacity() == DEFAULT_CAPACITY);
    assert(coin3.getPrice() == DEFAULT_PRICE);


    coin3.setName(name2);
    coin3.setPrice(price2);
    assert(coin3.getName() != name2 and coin3.getName() == DEFAUL_COINS_NAME);
    assert(coin3.getCapacity() == DEFAULT_CAPACITY);
    assert(coin3.getPrice() != price2 and coin3.getPrice() == DEFAULT_PRICE);

    qDebug() << "all tests are succesfully passed\n";
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testing();
    MainWindow w;
    w.show();
    return a.exec();
    return 0;
}
