#include <iostream>
#include "nicknametree.h"

int main()
{
    nickname::NickNameTree nickNameTree;

    nickNameTree.insert("alek");
    nickNameTree.insert("sasha");
    nickNameTree.insert("aleks");
    nickNameTree.insert("aleksey");
    nickNameTree.insert("alesha");


    for(auto pair = nickNameTree.begin() ; pair != nickNameTree.end(); ++pair)
    {
        std::cout << "{" << pair.fullValue() << ", " << pair.shortValue() << "}" << std::endl;
    }
    std::cout << std::endl;
    nickNameTree.print();
    return 0;
}
