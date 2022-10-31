
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include "../src/Stack/Stack.hpp"
#include "../src/RedBlackTree/Red_black_tree.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    RedBlackTree<int> m;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++) {
        int x = rand() % 800;
        m.insert(x);
    }
    std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;

    for (int i = 0; i < 10000; i++) {
        int x = rand() % 800;
        // std::cout << i << std::endl;
        m.deleteNode(x);
    std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    }

    for (int i = 0; i < 10000; i++) {
        int x = rand() % 800;
        m.insert(x);
    }
    std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    // std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    // m.display(2, m.getRoot(), 2);
    // m.printTree();
    // for (int i = 0; i < 10000; i++) {
    //     m.deleteNode(rand() % 100);
    // }
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
    // m.insert(48);
    // m.insert(38);
    // m.insert(31);
    // m.insert(12);
    // m.insert(19);
    // m.insert(8);
    // m.insert(200);
    // m.display(2, m.getRoot(), 2);
    // std::cout << "print" << std::endl;
    // m.testTree(m.getRoot());
    // m.testTree(m.getRoot());
    // m.deleteNode(12);
    // m.deleteNode(2);
    // m.deleteNode(10);
    // std::cout << "*******************************" << std::endl;
    // m.display(2, m.getroot(), 2);
    // // m.leftRotate(m.getroot());
    // // m.display(2, m.getroot(), 2);
    // // m.rigthRotate(m.getroot());
    // // t = m.search(25);
    // m.display(2, m.getroot(), 2);

};