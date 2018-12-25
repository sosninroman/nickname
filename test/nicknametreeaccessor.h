#ifndef NICKNAMETREEACCESSOR_H
#define NICKNAMETREEACCESSOR_H

#include "nicknametree.h"

namespace nicknametest
{

class NickNameTreeAccessor
{
public:
    static nickname::internal::NickNameTreeNode* getRootNode(nickname::NickNameTree& tree);
};

}

#endif
