#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

void printCollection(ThingsList& lst);
void testing(){
    const int DEFAULT_PRICE = 0;
    const int DEFAULT_VOLUME = 1;
    const std::string DEFAULT_NAME = "default";

    std::string name = "some_object";
    int volume = 80;
    int price = 125;

    Object obj1(name, price, 0);
    assert(obj1.getName() == name or
           obj1.getName() == DEFAULT_NAME);
    assert(obj1.getVolume() == volume or
           obj1.getVolume() == DEFAULT_VOLUME);
    assert(obj1.getPrice() == price or
           obj1.getPrice() == DEFAULT_PRICE);

    Object obj2(obj1);
    assert(obj2.getName() == obj1.getName());
    assert(obj2.getVolume() == obj1.getVolume());
    assert(obj2.getPrice() == obj1.getPrice());

    Object obj3;
    assert(obj3.getName() == DEFAULT_NAME);
    assert(obj3.getVolume() == DEFAULT_VOLUME);
    assert(obj3.getPrice() == DEFAULT_PRICE);

    int volume2 = 235;
    std::string name2 = "";
    int price2 = -32;
    obj3.setName(name2);
    obj3.setVolume(volume2);
    obj3.setPrice(price2);
    assert(obj3.getName() != name2 and
            obj3.getName() == DEFAULT_NAME);
    assert(obj3.getVolume() == volume2);
    assert(obj3.getPrice() != price2 and
            obj3.getPrice() == DEFAULT_PRICE);

    ThingsList list1;
    list1.pushBack({ "name1", 23, 12 });
    list1.pushBack({ "name2", 34, 181 });
    list1.pushBack({ "name2'", 34, 290 });

    int oldSize = list1.getSize();
    list1.pushBack({ "name3", 56, 100 });
    assert(list1.getSize() == oldSize + 1);

    ThingsList list2(list1);

    assert(list1 == list2);

    oldSize = list1.getSize();
    list1.del();
    assert(list1.getSize() == oldSize - 1);
    assert(list1 != list2);

    printCollection(list1);

    list1.clear();
    assert(list1.getSize() == 0);

    std::string path = "text.txt";
    list2.write(path);
    list1.read(path);
    assert(list1 == list2);

    std::string DEFAUL_COINS_NAME = "CoinsStack";
    CoinsStack coin1(name, price);
    assert(coin1.getName() == name or
           coin1.getName() == DEFAUL_COINS_NAME);
    assert(coin1.getPrice() == price or
           coin1.getPrice() == DEFAULT_PRICE);

    CoinsStack coin2(coin1);
    assert(coin2.getName() == coin1.getName());
    assert(coin2.getVolume() == coin1.getVolume());
    assert(coin2.getPrice() == coin1.getPrice());

    CoinsStack coin3;
    assert(coin3.getName() == DEFAUL_COINS_NAME);
    assert(coin3.getVolume() == DEFAULT_VOLUME);
    assert(coin3.getPrice() == DEFAULT_PRICE);


    coin3.setName(name2);
    coin3.setPrice(price2);
    assert(coin3.getName() != name2 and
            coin3.getName() == DEFAUL_COINS_NAME);
    assert(coin3.getVolume() == DEFAULT_VOLUME);
    assert(coin3.getPrice() != price2 and
            coin3.getPrice() == DEFAULT_PRICE);

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
