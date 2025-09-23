#ifndef AVLTree_H
#define AVLTree_H
#include <iostream>
using namespace std;

template <typename T>
struct NodeAVL {
    T data;
    int height;
    NodeAVL* left; 
    NodeAVL* right;        
    NodeAVL() : left(nullptr), right(nullptr), height(0) {}   
    NodeAVL(T value) : data(value), left(nullptr), right(nullptr), height(0) {}   

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};

/*Forward Iterator for the AVL*/
template <typename T>
class AVLIterator
{
public:
    enum Type {
        PreOrder, InOrder, PostOrder, BFS
    };
private:
    NodeAVL<T> *current;
    Type type;
public:
    AVLIterator() : current(nullptr), type(InOrder) {};
    AVLIterator(NodeAVL<T> *current, Type type=InOrder): type(type) {
        //TODO
    }
    AVLIterator<T> &operator=(AVLIterator<T> other);
    bool operator!=(AVLIterator<T> other);
    AVLIterator<T> &operator++();   //++it
    T operator*();
};

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
    bool find(T value);//O(log n)
    string getInOrder();
    string getPreOrder();
    string getPostOrder();
    int height();
    T minValue();//O(log n)
    T maxValue();//O(log n)
    bool isBalanced();//O(n)
    int size();
    void remove(T value); //Use el predecesor para cuando el nodo a eliminar tiene dos hijos

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
    int balancingFactor(NodeAVL<T> *NodeAVL);//Obtiene el factor de balanceo O(1)
    void updateHeight(NodeAVL<T> *NodeAVL);//Actualiza la altura de un nodo O(1) 
    void balance(NodeAVL<T> *&NodeAVL);//Agoritmo principal que verifica el balanceo del nodo y aplica las rotaciones O(1)
    void left_rota(NodeAVL<T> *&NodeAVL); //Rotación a la izquier O(1)
    void right_rota(NodeAVL<T> *&NodeAVL); //Rotación a la derecha O(1)
};


#endif
