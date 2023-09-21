#include "mainwindow.h"

#include <QApplication>
typedef HashTable<string> Dict;
int main(int argc, char *argv[])
{
    Dict words1, words2, emptyDict;
    std::string path = "myfile.txt";
    std::string w1 = "milk",w2 = "hello",w3 = "cat";

    assert(emptyDict.getSize()==0);

    words1 << w2;
    words1 << w1;
    words1 << w1;
    words1 << w1;
    assert(words1.getSize() == 2);
    assert(words1[w1] == 3);
    assert(words1.find(w2));

    words1.deleteItem(w2);
    assert(not words1.find(w2));
    assert(words1.getSize() == 1);


    words1 << w3;
    words1 << w2;
    words1.write(path);

    words2.read(path);
    assert(words1==words2);

    words1.clear();
    assert(words1==emptyDict);

    std::cout << "tests completed";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
