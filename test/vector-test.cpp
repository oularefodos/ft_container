#include "index.hpp"

bool compare(std::vector<int> a, ft::vector<int> b, int x) {
    if (a.size() != b.size()) {
        std::cout << " size ";
        return false;
    }
    if (a.capacity() != b.capacity()) {
        std::cout << " capacity ";
        return false;
    }
    if (a.max_size() != b.max_size()) {
        std::cout << " max_size ";
        return false;
    }
    if (x) {
        std::vector<int>::iterator x = a.begin();
        for(ft::vector<int>::iterator i = b.begin(); i != b.end(); i++) {
            if (*i != *x){
                std::cout << " content ";
                return false;
            }
            x++;
        }
    }
    return true;
}

void message(std::string m, int i) {
    if (i)
        std::cout << "\033[1;31m " << m << " : KO" << std::endl;
    else
        std::cout << "\033[1;32m " << m << " : OK" << std::endl;
}



void vector_test() {
    /* constructeur test */
    std::vector<int> first;                            
    std::vector<int> second (4,100);                       
    std::vector<int> x (1000,1800);                       
    std::vector<int> third (second.begin(),second.end());  
    std::vector<int> fourth (third);

    ft::vector<int> my_first;                            
    ft::vector<int> my_second (4,100);
    ft::vector<int> my_third (my_second.begin(), my_second.end());  
    ft::vector<int> z (1000,1800);                       
    ft::vector<int> my_fourth (my_second);

    if (compare(first, my_first, 0))
        message("default constructor", 0);
    else
        message("default constructor", 1);
    if (compare(second, my_second, 1))
        message("default constructor", 0);
    else
        message("size constructor", 1);
    if (compare(fourth, my_fourth, 1))
        message("copi constructor", 0);
    else
        message("copi constructor", 1);

    /* Modifiers test */

    // push_back 
    for (int i = 0; i < 10; i++) {
        first.push_back(i);
        my_first.push_back(i);
    }
    if (compare(first, my_first, 1))
        message("push_back", 0);
    else
        message("push_back", 1);
    
    // pop_back
    for (int i = 0; i < 10; i++) {
        first.pop_back();
        my_first.pop_back();
    }
    if (compare(first, my_first, 1))
        message("pop_back", 0);
    else
        message("pop_back", 1);
    // assign -->template
    first.assign(100, 45);
    my_first.assign(100, 45);
    if (compare(first, my_first, 1))
        message("assign", 0);
    else
        message("assign", 1);
    // insert --> template 
    std::vector<int>::iterator iter1 = first.insert(first.begin() += 2, 78);
    ft::vector<int>::iterator iter2 = my_first.insert(my_first.begin() += 2, 78);
    if (*iter1 == *iter2)
        message("insert return value", 0);
    else 
        message("insert return value", 1);

    first.insert(first.begin() + 2, 5, 78);
    my_first.insert(my_first.begin() + 2, 5, 78);

    if (compare(first, my_first, 1))
        message("insert", 0);
    else
        message("insert", 1);

    // erase

    iter1 = first.erase(first.begin()+ 3);
    iter2 = my_first.erase(my_first.begin() + 3);
    if (*iter1 == *iter2)
        message("erase return value1", 0);
    else
        message("erase return value", 1);
    iter1 = first.erase(first.begin(), first.begin() + 5);
    iter2 = my_first.erase(my_first.begin(), my_first.begin() + 5);

    if (*iter1 == *iter2)
        message("erase return value2", 0);
    else
        message("erase return value", 1);

    iter1 = first.erase(first.begin(), first.begin() + 3);
    iter2 = my_first.erase(my_first.begin(), my_first.begin() + 3);

    if (*iter1 == *iter2)
        message("erase return value3", 0);
    else
        message("erase return value", 1);

    if (compare(first, my_first, 1))
        message("erase", 0);
    else
        message("erase", 1);

    // swap
    first.swap(x);
    my_first.swap(z);

    if (compare(first, my_first, 1))
        message("swap", 0);
    else
        message("swap", 1);
    // clear
    first.clear();
    my_first.clear();

    if (compare(first, my_first, 1))
        message("clear", 0);
    else
        message("clear", 1);

    /** Iterator */ 
    for (int i = 0; i < 10; i++)
    {
        first.push_back(i);
        my_first.push_back(i);
    }

    std::vector<int>::reverse_iterator v = first.rbegin();
    ft::vector<int>::reverse_iterator i = my_first.rbegin();
    while(i != my_first.rend()) {
        if (*i != *v){
            message("revers iterator", 1);
            break;
        }
            v++;
            i++;
    }
    message("revers iterator", 0);

    /* Capacity */

    // resize
    first.resize(20);
    my_first.resize(20);

    if (compare(first, my_first, 1))
        message("resize", 0);
    else
        message("resize", 1);

    for (int i = 0; i < 10; i++)
    {
        first.push_back(i * i);
        my_first.push_back(i * i);
    }

    // reserve 
    
    first.reserve(45);
    my_first.reserve(45);
    if (compare(first, my_first, 1))
        message("reserve", 0);
    else
        message("reserve", 1);

    first.reserve(4);
    my_first.reserve(4);

    if (compare(first, my_first, 1))
        message("reserve", 0);
    else
        message("reserve", 1);
    
    /** access element */

    for (unsigned int i = 0; i < first.size(); i++) {
        if (first.at(i) != my_first.at(i) || first[i] != my_first[i]) {
            message("at and []", 1);
        }
        else
            message("at and []", 0);

    }
    if (first.front() != my_first.front())
        message("front", 1);
    else
        message("front", 0);
    if (first.back() != my_first.back())
        message("Back", 1); 
    else
        message("Back", 0);   

}