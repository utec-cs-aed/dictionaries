template <typename T>
struct NodeAVL {
    T data;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    NodeAVL() : data(T()), height(0), left(nullptr), right(nullptr) {}

    NodeAVL(const T& value) : data(value), height(0), left(nullptr), right(nullptr) {}

    void killSelf() {
        if (left) left->killSelf();
        if (right) right->killSelf();
        delete this;
        }
};