#pragma once
#include <functional>
#include <iostream>
#include <fstream>
#include <list>
#include <QString>
//using namespace std;
template<typename K, typename V>
class BinaryTree
{
    struct Node {
        K key;
        V data;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(K key, V data, Node* l = nullptr, Node* r=nullptr) :
            key(key), data(data), left(l), right(r) {}
        Node(Node* other) :
            key(other->key), data(other->data) {}
    };
    int size;
    Node* tree;

    void del(Node*);
    Node* addNode(K key, V data, Node* tree) {
        if (tree == nullptr) tree = new Node(key, data);
        else if (key < tree->key) tree->left = addNode(key, data, tree->left);
        else tree->right = addNode(key, data, tree->right);
        return tree;
    }
public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    void clear();
    void insertItem(K key, V data);
    void deleteItem(K key);
    void displayTree() const;
    bool find(K key) const;
    void write(const std::string& path) const;
    void read(const std::string& path);
    V& operator[](K key) const;
    std::list <V> lst() const;
    bool operator==(const BinaryTree& other)const;
    bool operator!=(const BinaryTree& other)const { return not ((*this)==other); }
    int getSize() const { return size; }
    std::list<K> getKeys(Node* curr = nullptr) const;
};


template<typename K, typename V>
inline void BinaryTree<K, V>::del(Node* delTree)
{
    if (delTree != nullptr) {
        if (delTree->left) del(delTree->left);
        if (delTree->right) del(delTree->right);
        delete delTree;
    }
}


template<typename K, typename V>
inline BinaryTree<K, V>::BinaryTree()
{
    size = 0;
    tree = nullptr;
}


template<typename K, typename V>
inline BinaryTree<K, V>::BinaryTree(const BinaryTree& other)
{
    for (const auto& key : other.getKeys())
        insertItem(key, other[key]);
}


template<typename K, typename V>
inline BinaryTree<K, V>::~BinaryTree()
{
    clear();
}


template<typename K, typename V>
inline void BinaryTree<K, V>::clear()
{
    size = 0;
    del(tree);
    tree = nullptr;
}


template<typename K, typename V>
inline void BinaryTree<K, V>::insertItem(K key, V data)
{
    if (find(key)) {
        (*this)[key] = data;
        return;
    }
    tree = addNode(key, data, tree);
    ++size;
    return;
}


template<typename K, typename V>
void BinaryTree<K, V>::deleteItem(K key)
{
    if (not find(key)) return;
    bool isReady = false;
    if (tree->key == key) {
        isReady = true;
        delete tree;
    }
    Node* curr = tree;
    while (not isReady) {
        if (curr->key > key) {
            if (curr->left == nullptr)
                throw "key Error";
            isReady = curr->left->key == key;
            if (isReady) {
                Node* temp = curr->left;
                curr->left = temp->right;
                while (curr->left)curr = curr->left;
                curr->left = temp->left;
                delete temp;
            }
            else {
                curr = curr->left;
            }
        }
        else if (curr->key < key) {
            if (curr->right == nullptr)
                throw "key Error";
            isReady = curr->right->key == key;
            if (isReady) {
                Node* temp = curr->right;
                curr->right = temp->left;
                while (curr->right)curr = curr->right;
                curr->right = temp->right;
                delete temp;
            }
            else {
                curr = curr->right;
            }
        }
    }
    --size;
}

template<typename K, typename V>
void BinaryTree<K, V>::displayTree() const
{
    for (auto& key : getKeys()) {
        std::cout << key << " " << (*this)[key] << "\n";
    }
}

template<typename K, typename V>
bool BinaryTree<K, V>::find(K key) const
{
    Node* curr = tree;
    while (curr!=nullptr and curr->key != key) 
        curr = ((curr->key > key) ? curr->left : curr->right);
    return curr != nullptr;
}

template<typename K, typename V>
void BinaryTree<K, V>::write(const std::string& path) const
{
    std::ofstream fout(path);
    for (const auto& key : getKeys()) {
        fout << key << " " << (*this)[key] << "\n";
    }
    fout.close();
}

template<typename K, typename V>
void BinaryTree<K, V>::read(const std::string& path)
{
    clear();
    std::ifstream fin(path); K key; V data;
    while (fin >> key >> data) {
        insertItem(key, data);
    }
    fin.close();
}

template<typename K, typename V>
V& BinaryTree<K, V>::operator[](K key) const
{
    Node* curr = tree;
    while (curr != nullptr and curr->key != key)
        curr = ((curr->key > key) ? curr->left : curr->right);
    if (curr != nullptr)
        return curr->data;
    throw QString("key Error");
}

template<typename K, typename V>
std::list<V> BinaryTree<K, V>::lst() const
{
    std::list<V> values;
    for (auto& key : getKeys())
        values.push_back((*this)[key]);
    return values;
}

template<typename K, typename V>
bool BinaryTree<K, V>::operator==(const BinaryTree& other) const
{
    if (size != other.size)
        return false;
    if (other.size == 0)
        return true;
    for (const auto& key : other.getKeys()) {
        if (not find(key) or (*this)[key] != other[key])
            return false;
    }
    return true;
}

template<typename K, typename V>
std::list<K> BinaryTree<K, V>::getKeys(Node* curr) const
{
    if (curr == nullptr) curr = tree;
    std::list<K> keys1, keys2;
    if(!curr) return keys1;
    if(curr->left) keys1 = getKeys(curr->left);
    keys1.push_back(curr->key);
    if(curr->right) keys2 = getKeys(curr->right);
    keys1.insert(keys1.end(), keys2.begin(), keys2.end());
    return keys1;
}

