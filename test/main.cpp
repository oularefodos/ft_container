
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include "../src/Stack/Stack.hpp"
#include "../src/RedBlackTree/Red_black_tree.hpp"
#include "../src/Map/map.hpp"
#include "../src/Set/set.hpp"
#include "../src/Utils/utils.hpp"
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
// #include <functional.h>

void f() {
    system("leaks container");
}




int main() {
    ft::set<const int, int> m;
    typedef std::map<const int, int> map;
    typedef ft::set<const int, int> map2;
    std::map<const int, int> m2;
    std::pair<map::iterator, bool> n;
    
    srand(time(NULL));
    for (int i = 0; i < 10; i+=2) {
        int x = rand() % 800;
        m.insert(x);
        m2.insert(std::pair<int, int> (i, x));
        // int y = m2.erase(i);
        std::cout << "m : " << x <<std::endl;
    }

    map::iterator xy = m2.upper_bound(1);
    map2::iterator xyz = m.upper_bound(1);
    std::cout << (*xy).second << std::endl;
    std::cout << (*xyz)<< std::endl;
    // m.print();
    // compar<std::pair<int, int> > comp;
    // std::pair<int, int> m(1, 2);
    // std::pair<int, int> m2(4, 5);
    // std::cout << comp(m, m2) << std::endl;
    // atexit(f);
    // RedBlackTree<std::pair<const int, int>, compar<std::pair<int, int> > > m;
    // // srand(time(NULL));
    // for (int i = 0; i < 100000; i++) {
    //     int x = rand() % 800;
    //     m.insert(std::pair<int, int> (i, x));
    //     // std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    //     // std::cout << i << std::endl;
    // }
    // // std::cout<< "mm***m" << std::endl;
    // // m.printTree();
    // for (int i = 0; i < 100000; i++) {
    //     int x = rand() % 800;
    //     // std::cout << x << std::endl;
    //     m.deleteNode(std::pair<int, int> (i, x));
    // std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    //     std::cout << i << std::endl;

    // }

    // for (int i = 0; i < 10000; i++) {
    //     int x = rand() % 800;
    //     m.insert(x);
    // }
    // std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    // std::cout << std::boolalpha <<  m.testRedBlack() << std::endl;
    // m.display(2, m.getRoot(), 2);
    // for (int i = 0; i < 10000; i++) {
    //     m.deleteNode(rand() % 100);
    // }
    // Node<int> *t;
    // m.insert(10);
    // m.insert(50);
    // m.insert(5);
    // m.insert(25);
    // m.insert(28);
    // // m.print();
    // m.swap(25, 10);
    // m.print();

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
    // // m._leftRotate(m.getroot());
    // // m.display(2, m.getroot(), 2);
    // // m._rigthRotate(m.getroot());
    // // t = m.search(25);
    // m.display(2, m.getroot(), 2);
    

};