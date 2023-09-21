#include "HashTable.h"
#include <QString>


template<typename K, typename V, class hash>
HashTable<K, V, hash>::HashTable()
{
    capacity = 5;
    size = 0;
    table = new list<ValueType>[capacity];
}

template<typename K, typename V, class hash>
HashTable<K, V, hash>::HashTable(const HashTable& other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->table = new list<ValueType>[capacity];
    for (int i = 0; i < capacity; ++i) {
        this->table[i] = other.table[i];
    }
}

template<typename K, typename V, class hash>
HashTable<K, V, hash>::HashTable(int c)
{
    int size = getPrime(c);
    this->capacity = size;
    table = new list<ValueType>[capacity];
    this->size = 0;
}

template<typename K, typename V, class hash>
HashTable<K, V, hash>::~HashTable()
{
    clear();
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::rehash()
{
    int newCapacity = getPrime(capacity * 2);
    int newSize = size;
    list <ValueType>* newTable = new list <ValueType>[newCapacity];
    for (int i = 0; i < capacity; ++i) {
        for (auto value : table[i]) {
            uint64_t cache = value.cache_;
            int index = cache % newCapacity;
            K key = value.key_;
            V data = value.data_;
            auto pos = value.pos_;
            newTable[index].push_back(ValueType(key, data, cache,pos));
        }
    }
    if (table != nullptr) delete[] table;
    size = newSize;
    capacity = newCapacity;
    table = newTable;
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::clear()
{
    if (table != nullptr) delete[] table;
    keys.clear();
    capacity = 5;
    size = 0;
    table = new list<ValueType>[capacity];
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::insertItem(K key, V data)
{
    if (find(key)) {
        return;
    }
    ++size;
    keys.push_back(key);
    auto pos = --keys.end();
    if (load() >= MAX_LOAD_FACTOR) {
        rehash();
    }
    uint64_t cache = hash{}(key);
    int index = cache % capacity;
    table[index].push_back(ValueType(key, data, cache, pos));

}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::deleteItem(K key)
{
    if (not find(key)) {
        return;
    }
    uint64_t cache = hash{}(key);
    int index = cache % capacity;
    auto iter = table[index].begin();
    for (; iter != table[index].end(); iter++)
        if ((*iter).key_ == key) break;

    auto pos = (*iter).pos_;
    keys.erase(pos);
    table[index].erase(iter);
    --size;
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::print() const{
    for( auto key : keys){
        auto value = (*this)[key];
        std::cout << "{ " << key << ", " << value << " }\n";
    }
}

template<typename K, typename V, class hash>
int HashTable<K, V, hash>::getSum()
{
    int sum = 0;
    for( auto key : keys){
        sum += (*this)[key];
    }
    return sum;
}

template<typename K, typename V, class hash>
bool HashTable<K, V, hash>::find(K key) const
{
    int index = hash{}(key) % capacity;
    for (auto& value : table[index]) {
        if (value.key_ == key)
            return true;
    }
    return false;
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::write(const string& path) const
{
    std::ofstream fout(path);
    fout << capacity << "\n";
    for( auto key : keys){
        auto val = (*this)[key];
        fout << key << " " << val << "\n";
    }
    fout.close();
}

template<typename K, typename V, class hash>
void HashTable<K, V, hash>::read(const string& path)
{
    clear();
    std::ifstream fin(path);
    K key;
    V data;
    fin >> capacity;
    table = new list<ValueType>[capacity];
    while (fin >> key >> data) {
        size++;
        uint64_t cache = hash{}(key);
        int index = cache % capacity;
        keys.push_back(key);
        auto pos = --keys.end();
        ValueType value = ValueType(key, data, cache,pos);
        table[index].push_back(value);
    }
    fin.close();
}

template<typename K, typename V, class hash>
V& HashTable<K, V, hash>::operator[](K key) const
{
    uint64_t cache = hash{}(key);
    int index = cache % capacity;
    for (auto& x : table[index]) {
        if (x.key_ == key) {
            return x.data_;
        }
    }
    throw QString("key Error");
}

template<typename K, typename V, class hash>
bool HashTable<K, V, hash>::operator==(const HashTable& other) const
{
    if (this->size != other.size)
        return false;
    for (int i = 0; i < capacity; ++i) {
        for (auto value : table[i]) {
            if (!(other.find(value.key_)) or
                other[value.key_] != value.data_)
                return false;
        }
    }
    return true;
}
