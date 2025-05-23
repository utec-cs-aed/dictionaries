#include <iostream>
using namespace std;

const int maxColision = 3;

// Nodo para la tabla hash
template <typename TK, typename TV>
struct HashNode {
    TK key;
    TV value;
    HashNode* next;
    HashNode* prevInsert;
    HashNode* nextInsert;

    HashNode(const TK& k, const TV& v)
        : key(k), value(v), next(nullptr), prevInsert(nullptr), nextInsert(nullptr) {}
};

template <typename TK, typename TV>
class HashIterator {
private:
    HashNode<TK, TV>* current;
public:
    HashIterator(HashNode<TK, TV>* node = nullptr) : current(node) {}

    HashIterator<TK, TV>& operator=(HashIterator<TK, TV> other) {
        current = other.current;
        return *this;
    }
    bool operator!=(HashIterator<TK, TV> other) {
        return current != other.current;
    }
    HashIterator<TK, TV>& operator++() {
        if (current) current = current->nextInsert;
        return *this;
    }
    pair<TK, TV> operator*() {
        return {current->key, current->value};
    }
};

template <typename TK, typename TV>
class HashTable {
public:
    typedef HashIterator<TK, TV> iterator;
    iterator begin() { return iterator(headInsert); }
    iterator end() { return iterator(nullptr); }

private:
    int capacity;
    int size;
    HashNode<TK, TV>** table;
    HashNode<TK, TV>* headInsert;
    HashNode<TK, TV>* tailInsert;

    int hash(const TK& key) {
        // Simple hash usando std::hash
        return std::hash<TK>{}(key) % capacity;
    }

public:
    HashTable(int _cap = 5) : capacity(_cap), size(0), headInsert(nullptr), tailInsert(nullptr) {
        table = new HashNode<TK, TV>*[capacity];
        for (int i = 0; i < capacity; ++i) table[i] = nullptr;
    }

    void insert(TK key, TV value) { insert({key, value}); }

    void insert(pair<TK, TV> item) {
        int idx = hash(item.first);
        HashNode<TK, TV>* node = table[idx];
        int col = 0;
        while (node) {
            if (node->key == item.first) {
                node->value = item.second;
                return;
            }
            node = node->next;
            col++;
        }
        if (col >= maxColision) {
            rehashing();
            insert(item);
            return;
        }
        HashNode<TK, TV>* newNode = new HashNode<TK, TV>(item.first, item.second);
        newNode->next = table[idx];
        table[idx] = newNode;
        if (!headInsert) {
            headInsert = tailInsert = newNode;
        } else {
            tailInsert->nextInsert = newNode;
            newNode->prevInsert = tailInsert;
            tailInsert = newNode;
        }
        size++;
    }

    TV& at(TK key) {
        int idx = hash(key);
        HashNode<TK, TV>* node = table[idx];
        while (node) {
            if (node->key == key) return node->value;
            node = node->next;
        }
        throw std::out_of_range("Key not found");
    }

    TV& operator[](TK key) {
        int idx = hash(key);
        HashNode<TK, TV>* node = table[idx];
        while (node) {
            if (node->key == key) return node->value;
            node = node->next;
        }
        insert(key, TV());
        return at(key);
    }

    bool find(TK key) {
        int idx = hash(key);
        HashNode<TK, TV>* node = table[idx];
        while (node) {
            if (node->key == key) return true;
            node = node->next;
        }
        return false;
    }

    bool remove(TK key) {
        int idx = hash(key);
        HashNode<TK, TV>* node = table[idx];
        HashNode<TK, TV>* prev = nullptr;
        while (node) {
            if (node->key == key) {
                if (prev) prev->next = node->next;
                else table[idx] = node->next;
                // Quitar del orden de inserción
                if (node->prevInsert) node->prevInsert->nextInsert = node->nextInsert;
                else headInsert = node->nextInsert;
                if (node->nextInsert) node->nextInsert->prevInsert = node->prevInsert;
                else tailInsert = node->prevInsert;
                delete node;
                size--;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    int getSize() { return size; }

    vector<TK> getAllKeys() {
        vector<TK> keys;
        for (auto it = begin(); it != end(); ++it) keys.push_back((*it).first);
        return keys;
    }
    vector<pair<TK, TV>> getAllElements() {
        vector<pair<TK, TV>> elems;
        for (auto it = begin(); it != end(); ++it) elems.push_back(*it);
        return elems;
    }

private:
    void rehashing() {
        int oldCap = capacity;
        capacity *= 2;
        HashNode<TK, TV>** oldTable = table;
        table = new HashNode<TK, TV>*[capacity];
        for (int i = 0; i < capacity; ++i) table[i] = nullptr;
        headInsert = tailInsert = nullptr;
        size = 0;
        // Reinsertar en nuevo arreglo
        for (int i = 0; i < oldCap; ++i) {
            HashNode<TK, TV>* node = oldTable[i];
            while (node) {
                insert(node->key, node->value);
                HashNode<TK, TV>* toDelete = node;
                node = node->next;
                delete toDelete;
            }
        }
        delete[] oldTable;
    }
public:
    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            HashNode<TK, TV>* node = table[i];
            while (node) {
                HashNode<TK, TV>* next = node->next;
                delete node;
                node = next;
            }
        }
        delete[] table;
    }
};