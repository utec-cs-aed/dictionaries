#include <iostream>
using namespace std;

const int maxColision = 3;

//itera sobre el hashtable manteniendo el orden de insercion
template <typename TK, typename TV>
class HashIterator
{
private:
    //TODO

public:   
    HashIterator<TK, TV> &operator=(HashIterator<TK, TV> other);
    bool operator!=(HashIterator<TK, TV> other); 
    HashIterator<TK, TV> &operator++();   //++it
    TV operator*();
};

template <typename TK, typename TV>
class HashTable
{
public:
    typedef HashIterator<TK, TV>  iterator; 
    iterator begin();// Retorna el inicio del iterador             
    iterator end();// Retorna el final del iterador    

private:    
    struct Node {
        TK value;
        TV value;
        //TODO
    };
    int capacity;
    int size;
    Node** array;

public:    
    HashTable(int _cap=5): capacity(_cap), size(0)  {
        array = new Node*[capacity];
        for (int i = 0; i < capacity; i++)
            array[i] = nullptr;
    }
    void insert(TK key, TV value);    
    void insert(pair<TK, TV> item); 
    TV& at(TK key);
    TV& operator[](TK key);
    bool find(TK key);
    bool remove(TK key);
    int getSize();

    /*itera sobre el hashtable manteniendo el orden de insercion*/
    vector<TK> getAllKeys();
    vector<pair<TK, TV>> getAllElements();
private:    
    /*Si una lista colisionada excede maxColision, redimensionar el array*/
    void rehashing();
};


