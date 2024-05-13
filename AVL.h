#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>
#include "AVL_Node.h"
#include "AVL_Iterator.h"

using namespace std;

template <typename T>
class AVLTree
{ 
public:
    typedef BSTIterator<T> iterator; 
    iterator begin(AVLIterator<int>::Type _);// Retorna el inicio del iterador             
    iterator end();// Retorna el final del iterador

private:
    NodeAVL<T> *root;
public:
    AVLTree() : root(nullptr) {}
    void insert(T value);
    bool find(T value);
    string getInOrder();
    string getPreOrder();
    string getPostOrder();
    int height();
    T minValue();
    T maxValue();
    bool isBalanced();
    int size();
    void remove(T value); //Use el predecesor 

    /*Adicionales*/
    T successor(T value); // Retornar el valor siguiente de "value" en el arbol
    T predecessor(T value); // Retornar el valor anterior de "value" en el arbol
    void clear(); // Liberar todos los nodos (usar root->KillSelf)
    void displayPretty();//Muestra el arbol visualmente atractivo

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    /*Rotaciones del AVL*/    
    int balancingFactor(NodeAVL<T> *NodeAVL);
    void updateHeight(NodeAVL<T> *NodeAVL);
    void balance(NodeAVL<T> *&NodeAVL);
    void left_rota(NodeAVL<T> *&NodeAVL); 
    void right_rota(NodeAVL<T> *&NodeAVL); 
};


#endif