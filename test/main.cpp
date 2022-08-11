#include <iostream>
#include "../src/Vector/Vector.hpp"
#include <vector>

int main()
{
    Vector<int> n(2, 5);
    std::vector <int> tab(2, 5);

    auto i = tab.begin();

    std::cout << i << std::endl;
    std::cout << n.data()[1] << std::endl;

}