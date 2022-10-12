
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include <vector>

int main()
{
    std::vector<std::string> init1(5, "fode");
    ft::vector<std::string> init2(5, "fode");
    std::vector<std::string> tab1(init1.begin(), init1.end());
    ft::vector<std::string> tab2(init2);

    std::cout << tab1.size() << std::endl;
    std::cout << tab2.size() << std::endl;
    std::cout << tab1.capacity() << std::endl;
    std::cout << tab2.capacity() << std::endl;

    for (unsigned int i = 0; i < tab1.size(); i++)
    {
        std::cout << tab2[i] << " " << tab1[i] << std::endl;
        // std::cout << i << tab2[i] << std::endl;
    }

    // tab1.resize(5, "fode");
    // tab2.resize(5, "fode");

    // std::cout << tab1.size() << std::endl;
    // std::cout << tab2.size() << std::endl;

    // for (unsigned int i = 0; i < 15; i++)
    // {
    //     std::cout << tab2[i] << " " << tab1[i] << std::endl;
    // }

    system("leaks container");
}