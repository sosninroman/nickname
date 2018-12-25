#include "nicknametreeaccessor.h"

namespace nicknametest
{

nickname::internal::NickNameTreeNode* NickNameTreeAccessor::getRootNode(nickname::NickNameTree& tree)
{
    return &tree.m_root;
}

}
