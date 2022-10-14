
#include <iostream>
#include "../src/Vector/Vector.hpp"
#include <vector>

int main()
{
    /** assign test */

        // std::vector<int> tab1(12, 45);
        std::vector<int> tab(45, 45);
        ft::vector<int> tab2(4, 12);

        // tab.assign(tab1.begin(), tab1.end());

        // std::cout << tab2.size() << " size " << tab.size() << std::endl;
        // std::cout << tab2.capacity() << " capacity " << tab.capacity() << std::endl;
        // for (unsigned int i (0); i < tab.size(); i++)
        //     std::cout << tab1[i] << " " << tab[i] << std::endl;


//     std::vector<std::string> init1(5, "fode");
//     ft::vector<std::string> init2(5, "fode");
//     std::vector<std::string> tab1(init1.begin(), init1.end());
//     ft::vector<std::string> tab2(init2);

//     std::cout << tab1.size() << std::endl;
//     std::cout << tab2.size() << std::endl;
//    tab1.pop_back(); tab2.pop_back();

//     std::cout << tab1.size() << std::endl;
//     std::cout << tab2.size() << std::endl;

    for (unsigned int i = 0; i < tab2.size(); i++)
    {
        std::cout << tab2[i] << " " << tab[i] << std::endl;
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
}