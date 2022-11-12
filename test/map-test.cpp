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

    for (unsigned int i = 10; i < 20; i++) {
        x = rand() % 800;
        a.insert(std::make_pair(i, x));
        a1.insert(ft::make_pair(i, x));
    }
    compare_map(a, a1, "insert 1");

    for (unsigned int i = 20; i < 30; i++) {
        x = rand() % 800;
        a.insert(++a.begin(), std::make_pair(i, x));
        a1.insert(++a1.begin(), ft::make_pair(i, x));
    }
    compare_map(a, a1, "insert 2");

    std::map<int, int> w;
    ft::map<int, int> y;
    for (unsigned int i = 30; i < 40; i++) {
        x = rand() % 800;
        w.insert(std::make_pair(i, x));
        y.insert(ft::make_pair(i, x));
    }

    a.insert(w.begin(), w.end());
    a1.insert(y.begin(), y.end());
    compare_map(a, a1, "insert 3");

    // Erase
    
    for (unsigned int i = 10; i < 10; i++) {
        a.erase(i);
        a1.erase(i);
    }
    compare_map(a, a1, "erase 1");

    std::map<int, int>::iterator iter1(a.begin());
    ft::map<int, int>::iterator iter2(a1.begin());
    for (unsigned int i = 10; i < 10; i++) {
        ++iter1;
        ++iter2;
    }

    a.erase(a.begin(), iter1);
    a1.erase(a1.begin(), iter2);
    compare_map(a, a1, "erase 2");

    for (unsigned int i = 10; i < 10; i++) {
        a.erase(++a.begin());
        a1.erase(++a1.begin());
    }
    compare_map(a, a1, "erase 3");

    a.swap(w);
    a1.swap(y);

    compare_map(a, a1, "swap");

    a.clear();
    a1.clear();
    compare_map(a, a1, "clear");

    a = w;
    a1 = y;

    iter1 = a.find(35);
    iter2 = a1.find(35);
    if (((*iter1).first == (*iter2).first))
        message("find", 0);
    else
        message("find", 1);
    
    int ret1 = a.count(find);
    int ret2 = a1.count(find);

     if ((ret1 == ret2))
        message("count", 0);
    else
        message("count", 1);
}