#include <iostream>
#include "nicknametree.h"

int main()
{
    nickname::NickNameTree nickNameTree2;

    nickNameTree2.insert("astralp");
    nickNameTree2.insert("astrak");
    nickNameTree2.insert("astrals");
    nickNameTree2.insert("bulks");
    nickNameTree2.insert("bulkp");

    nickNameTree2.print();
    return 0;
}
