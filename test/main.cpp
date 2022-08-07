#include <iostream>
#include "../src/Vector/Vector.hpp"
#include <vector>

int main()
{
    Vector<int> n(25);
    std::vector <int> tab(1, 2);

    // for (int i = 0; tab[i]; i++)
    //     std::cout<<tab[i] << std::endl;

    // tab.resize(4, 5);

    // std::cout << "***********************************************" << std::endl;
    // for (int i = 0; tab[i]; i++)
    //     std::cout<<tab[i] << std::endl;

    // tab.resize(2, 18);

    // std::cout << "***********************************************" << std::endl;
    // for (int i = 0; tab[i]; i++)
    //     std::cout<<tab[i] << std::endl;
    std::vector<int> m(25);
    for (int i = 0; i < 2; i++)
        n.push_back(5);
    // for(int i = 0; i < 50; i++)
        std::cout << n.capacity() << std::endl;
        std::cout << n[250] << std::endl;
}