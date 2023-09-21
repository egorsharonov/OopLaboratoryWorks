#pragma once
#include <functional>
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

template<typename K, typename V, class hash = std::hash<K>>
class HashTable
{
    const double MAX_LOAD_FACTOR = 0.75;
    struct ValueType {
        K key_;
        V data_;
        uint64_t cache_;
        typename list<K>::iterator pos_;
        ValueType(K key, V data, uint64_t cache,typename list<K>::iterator pos) :
            key_(key), data_(data), cache_(cache), pos_(pos){}
    };
    int capacity;
    int size;
    list <ValueType>* table;
    list <K> keys;
    double load() {
        if (capacity == 0) return 1;
        return size / capacity;
    }
    bool checkPrime(int n)const
    {
        if (n == 1 || n == 0) return false;
        for (int i = 2; i < n / 2; i++)
            if (n % i == 0) return false;
        return true;
    }
    int getPrime(int n) const
    {
        n += (n % 2 == 0);
        while (!checkPrime(n))
            n += 2;
        return n;
    }
public:
    HashTable();
    HashTable(const HashTable& other);
    HashTable(int c);
    ~HashTable();
    void rehash();
    void clear();
    int getSize() { return size; }
    int getCapacity() {return capacity;}
    list<K> getKeys(){return keys;}
    void insertItem(K key, V data);
    void deleteItem(K key);
    void displayHash() const;
    void print() const;
    list<K> getlist(V value) const;
    bool find(K key) const;
    void write(const string& path)const;
    void read(const string& path);
    V& operator[](K key) const;
    bool operator==(const HashTable& other)const;
};
