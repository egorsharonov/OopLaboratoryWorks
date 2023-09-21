#ifndef OBJECT_H
#define OBJECT_H


#include <iostream>
class Object
{
    std::string name_;
    int price_;
    int volume_;
public:
    enum id {
        object,
        coinsStack
    };
    Object();
    Object(const std::string&, int = 0, int = 1);
    Object(const Object&);
    virtual ~Object();
    std::string getName() const;
    int getPrice() const;
    int getVolume() const;
    void setName(const std::string&);
    virtual void setPrice(int);
    virtual void setVolume(int);
    bool operator==(const Object& right);
    bool operator!=(const Object& right);
    virtual id identify() const;
    friend std::ostream& operator<<(std::ostream&, const Object&);
};

#endif // OBJECT_H
