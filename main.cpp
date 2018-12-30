#include <iostream>
#include "nicknametree.h"

int main()
{
    nickname::NickNameTree nickNameTree;

    for(std::string name; std::getline(std::cin, name);)
    {
        nickNameTree.insert(name);
    }

    for(auto itr = nickNameTree.begin(); itr != nickNameTree.end(); ++itr)
    {
        std::cout << "{" << itr.fullValue() << ", " << itr.shortValue() << "}" << std::endl;
    }

    std::cout << std::endl;

    nickNameTree.print();
    return 0;
}
