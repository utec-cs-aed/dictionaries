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
    typedef AVLIterator<T> iterator; 
    iterator begin(AVLIterator<int>::Type _);// Retorna el inicio del iterador             
    iterator end();// Retorna el final del iterador

private:
    NodeAVL<T> *root;
public:
    AVLTree() : root(nullptr) {}
    void insert(T value);//O(log n)
    bool find(T value,NodeAVL<T>* nodo) {
        if (nodo == nullptr) {
            return false;
        }
        if (value == nodo->data) {
            return true;
        }

        if (value < nodo->data) {
            return find(value, nodo->left);
        }
        if (value > nodo->data) {
            return find(value, nodo->right);
        }
        return false;
    }//O(log n)
    string getInOrder();
    string getPreOrder();
    string getPostOrder();
    int height() {
        return height(root);
    }
    T minValue(NodeAVL<T>* nodo) {
        if (nodo == nullptr) {
            return T();
        }
        NodeAVL<T> *temp = nodo;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp->data;
    }//O(log n)
    T maxValue(NodeAVL<T>* nodo) {
        if (nodo == nullptr) {
            return T();
        }
            NodeAVL<T> *temp = nodo;
            while (temp->right != nullptr) {
                temp = temp->right;
            }
            return temp->data;
    }
        //O(log n)
    bool isBalanced();//O(n)
    int size();
    void remove(T value); //Use el predecesor para cuando el nodo a eliminar tiene dos hijos

    /Adicionales/
    T successor(T value) {
        if (root == nullptr) {
            return T();
        }
        NodeAVL<T> *temp = root;
        while (temp->data != value) {
            if (value < temp->data) {
                temp = temp->left;
            }
            if (value > temp->data) {
                temp = temp->right;
            }
        }
        return minValue(temp->right);
    } // Retornar el valor siguiente de "value" en el arbol
    T predecessor(T value) {
        if (root == nullptr) {
            return T();
        }
        NodeAVL<T> *temp = root;
        while (temp->data != value) {
            if (value < temp->data) {
                temp = temp->left;
            }
            if (value > temp->data) {
                temp = temp->right;
            }
        }
        return maxValue(temp->left);
    }
        // Retornar el valor anterior de "value" en el arbol
    void clear(); // Liberar todos los nodos (usar root->KillSelf)
    void displayPretty();//Muestra el arbol visualmente atractivo

    ~AVLTree(){
        if(this->root != nullptr){
            this->root->killSelf();
        }
    }

private:
    /Rotaciones del AVL/
    int balancingFactor(NodeAVL<T> *NodeAVL) {
        return height(NodeAVL->left) - height(NodeAVL->right);
    }//Obtiene el factor de balanceo O(1)
    void updateHeight(NodeAVL<T> *NodeAVL) {
        return max(height(NodeAVL->left), height(NodeAVL->right))+1;
    }//Actualiza la altura de un nodo O(1)
    void balance(NodeAVL<T> *&NodeAVL) {
        if (balancingFactor(NodeAVL) > 1) {
            if (balancingFactor(NodeAVL->left) < 0) {
                rotateLeft(NodeAVL->left);
            }
            rotateRight(NodeAVL);
        }
        else if (balancingFactor(NodeAVL) < -1) {
            if (balancingFactor(NodeAVL->right) > 0) {
                rotateRight(NodeAVL->right);
            }
            rotateLeft(NodeAVL);
        }
        return;
    }
        //Agoritmo principal que verifica el balanceo del nodo y aplica las rotaciones O(1)
    void left_rota(NodeAVL<T> *&NodeAVL) {
        NodeAVL* temp = NodeAVL->right;
        NodeAVL->right = temp->left;
        temp->left = NodeAVL;
        NodeAVL = temp;
        updateHeight(NodeAVL->left);
        updateHeight(NodeAVL);
    }
        //Rotación a la izquier O(1)
    void right_rota(NodeAVL<T> *&NodeAVL){
        NodeAVL* temp = NodeAVL->left;
        NodeAVL->left = temp->right;
        temp->right = NodeAVL;
        NodeAVL = temp;
        updateHeight(NodeAVL->right);
        updateHeight(NodeAVL);
    }//Rotación a la derecha O(1)
};


#endif