#include <iostream>
#include "nicknametree.h"

int main()
{
    nickname::NickNameTree nickNameTree2;

    nickNameTree2.insert("alek");
    nickNameTree2.insert("sasha");
    nickNameTree2.insert("aleks");
    nickNameTree2.insert("aleksey");
    nickNameTree2.insert("alesha");

    for(const auto pair : nickNameTree2)
    {
        std::cout << "{" << pair.first << "," << pair.second << "}" << std::endl;
    }
    std::cout << std::endl;
    nickNameTree2.print();
    return 0;
}
