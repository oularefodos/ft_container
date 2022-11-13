#include "index.hpp"
typedef std::set<int>::iterator type_iter1;
typedef ft::set<int>::iterator type_iter2;

// const iterator

bool compare_set(std::set<int>& a, ft::set<int>& b, std::string str) {
    if (a.size() != b.size()) {
        std::cout << " size ";
        message(str, 1);
        return false;
    }
        std::set<int>::iterator x = a.begin();
        for(ft::set<int>::iterator i = b.begin(); i != b.end(); i++) {
            if ( *i != *x ){
                std::cout << " first ";
                message(str, 1);
                return false;
            }
            x++;
        }
    message(str, 0);
    return true;
}

void set_test() {
    std::set<int> a;
    ft::set<int> a1;
    compare_set(a, a1, "Default constructor");

    srand(time(0));
    int x;
    for (unsigned int i = 0; i < 10; i++) {
        x = rand() % 600;
        a.insert(x);
        a1.insert(x);
    }


    std::set<int> b(a);
    ft::set<int> b1(a1);
    compare_set(b, b1, "Copie Constructor");

    std::set<int> c(b.begin(), b.end());
    ft::set<int> c1(b1.begin(), b1.end());
    compare_set(c, c1, "iterator Constructor");

    std::set<int> d = c;
    ft::set<int> d1 = c1;
    compare_set(a, a1, "Operator =");
    
    /**Modifier*/

    //insert

    for (unsigned int i = 10; i < 20; i++) {
        x = rand() % 800;
        a.insert(x);
        a1.insert(x);
    }
    compare_set(a, a1, "insert 1");

    for (unsigned int i = 20; i < 30; i++) {
        x = rand() % 800;
        a.insert(++a.begin(), x);
        a1.insert(++a1.begin(), x);
    }
    compare_set(a, a1, "insert 2");

    std::set<int> w;
    ft::set<int> y;
    for (unsigned int i = 30; i < 40; i++) {
        w.insert(i);
        y.insert(i);
    }

    a.insert(w.begin(), w.end());
    a1.insert(y.begin(), y.end());
    compare_set(a, a1, "insert 3");

    // Erase
    
    for (unsigned int i = 10; i < 10; i++) {
        a.erase(i);
        a1.erase(i);
    }
    compare_set(a, a1, "erase 1");

    std::set<int>::iterator iter1(a.begin());
    ft::set<int>::iterator iter2(a1.begin());
    for (unsigned int i = 10; i < 10; i++) {
        ++iter1;
        ++iter2;
    }

    a.erase(a.begin(), iter1);
    a1.erase(a1.begin(), iter2);
    compare_set(a, a1, "erase 2");

    for (unsigned int i = 10; i < 10; i++) {
        a.erase(++a.begin());
        a1.erase(++a1.begin());
    }
    compare_set(a, a1, "erase 3");

    a.swap(w);
    a1.swap(y);

    compare_set(a, a1, "swap");

    a.clear();
    a1.clear();
    compare_set(a, a1, "clear");

    a = w;
    a1 = y;

    iter1 = a.find(35);
    iter2 = a1.find(35);
    if ((*iter1 == *iter2))
        message("find", 0);
    else
        message("find", 1);
    
    int ret1 = a.count(35);
    int ret2 = a1.count(35);

     if (ret1 == ret2)
        message("count", 0);
    else
        message("count", 1);
    
    // Lower_bound

    for(unsigned int i  = 0; i < 40; i++) {
        iter1 = a.lower_bound(i);
        iter2 = a1.lower_bound(i);
        if (*iter1 == *iter2)
            message("Lower bound", 0);
        else
            message("Lower Bound", 1);
    }

    // upper_bound
    for(unsigned int i  = 0; i < 39; i++) {
        iter1 = a.upper_bound(i);
        iter2 = a1.upper_bound(i);
        if (*iter1 == *iter2)
            message("Upper Bound", 0);
        else
            message("Upper Bound", 1);
    }

    // equal Range
    for(unsigned int i  = 0; i < 39; i++) {
         std::pair<type_iter1, type_iter1> pair_ret1 = a.equal_range(i);
         ft::pair<type_iter2, type_iter2> pair_ret2 = a1.equal_range(i);
        if ((*(pair_ret1.first))== (*(pair_ret2.first)) &&
        (*(pair_ret1.second)) == (*(pair_ret2.second)))
            message("equal_rqange", 0);
        else
            message("equal_range", 1);
    }
}