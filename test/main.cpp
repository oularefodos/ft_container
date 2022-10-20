
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include "../src/Stack/Stack.hpp"
#include "../src/RedBlackTree/Red_black_tree.hpp"
#include <vector>


int main() {
    RedBlackTree<int> m;
    m.insert(10);
    m.insert(50);
    m.insert(5);
    m.display(2);
};