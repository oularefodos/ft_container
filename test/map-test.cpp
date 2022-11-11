#include "index.hpp"


// const iterator

bool compare_map(std::map<int, int>& a, ft::map<int, int>& b, std::string str) {
    if (a.size() != b.size()) {
        std::cout << " size ";
        message(str, 1);
        return false;
    }
    // if (a.max_size() != b.max_size()) {
    //     std::cout << " max_size ";
    //     message(str, 1);
    //     return false;
    // }
        std::map<int, int>::iterator x = a.begin();
        for(ft::map<int, int>::iterator i = b.begin(); i != b.end(); i++) {
            if ((*i).first != (*x).first ){
                std::cout << " first ";
                message(str, 1);
                return false;
            }
            if ((*i).second != (*x).second ){
                std::cout << " second ";
                message(str, 1);
                return false;
            }
            x++;
        }
    message(str, 0);
    return true;
}

void map_test() {
    std::map<int,int> a;
    ft::map<int,int> a1;
    compare_map(a, a1, "Default constructor");

    srand(time(0));
    int x;
    for (unsigned int i = 0; i < 10; i++) {
        x = rand() % 600;
        a.insert(std::make_pair(i, x));
        a1.insert(ft::make_pair(i, x));
    }

    std::map<int,int> b(a);
    ft::map<int,int> b1(a1);
    compare_map(a, a1, "Copie Constructor");

    std::map<int,int> c(b.begin(), b.end());
    ft::map<int,int> c1(b1.begin(), b1.end());
    compare_map(a, a1, "iterator Constructor");

    std::map<int,int> d = c;
    ft::map<int,int> d1 = c1;
    compare_map(a, a1, "Operator =");

    for (unsigned int i = 0; i < d1.size(); i++) {
        if (d[i] != d1[i])
            message("Operator []", 1);
        if (d.at(i) != d1.at(i))
            message("at []", 1);
        else
            message("at and Operator []", 0);
    }
    
    /**Modifier*/

    //insert

    for (unsigned int i = 20; i < 10; i++) {
        x = rand() % 800;
        a.insert(std::make_pair(i, x));
        a1.insert(ft::make_pair(i, x));
    }
    compare_map(a, a1, "insert 1");
}