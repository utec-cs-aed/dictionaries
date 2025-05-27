#include "AVL_Node.h"

template <typename T>
class AVLIterator {
public:
    enum Type {
        PreOrder, InOrder, PostOrder, BFS
    };

private:
    NodeAVL<T>* current;
    Type type;
    NodeAVL<T>* root;
    NodeAVL<T>* nextNode;

    void findNextInOrder(NodeAVL<T>* node) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            current = node->left;
            return;
        }

        current = node;
    }

public:
    AVLIterator() : current(nullptr), type(InOrder), root(nullptr), nextNode(nullptr) {}

    AVLIterator(NodeAVL<T>* root, Type type = InOrder) : root(root), type(type), current(nullptr) {
        if (root != nullptr) {
            if (type == InOrder) {
                findNextInOrder(root);
            }
        }
    }


    AVLIterator<T>& operator=(AVLIterator<T> other) {
        std::swap(current, other.current);
        std::swap(type, other.type);
        return *this;
    }

    bool operator!=(AVLIterator<T> other) {
        return current != other.current;
    }

    AVLIterator<T>& operator++() {
        if (type == InOrder) {
            if (current != nullptr) {
                findNextInOrder(current->right);
            }
        }
        return *this;
    }

    T operator*() {
        return current->data;
    }
};
