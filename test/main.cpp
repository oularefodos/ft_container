
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include "../src/Stack/Stack.hpp"
#include "../src/RedBlackTree/Red_black_tree.hpp"
#include <vector>


int main() {
    RedBlackTree<int> m;
    // Noeud<int> *t;
    // m.insert(10);
    // m.insert(50);
    // m.insert(5);
    // m.insert(25);
    // m.insert(28);
    // m.insert(19);
    // m.insert(6);
    // m.insert(4);
    // m.insert(1);
    // m.insert(3);
    // m.insert(90);
    // m.insert(100);
    // m.insert(2);
    m.insert(48);
    m.insert(38);
    m.insert(31);
    m.insert(12);
    m.insert(19);
    m.insert(8);
    // m.display(2, m.getTree(), 2);
    m.deleteNode(12);
    // std::cout << "*******************************" << std::endl;
    // m.display(2, m.getTree(), 2);
    // m.leftRotate(m.getTree());
    // m.display(2, m.getTree(), 2);
    // m.rigthRotate(m.getTree());
    // t = m.search(25);
    m.display(2, m.getTree(), 2);

};