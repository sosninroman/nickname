#include "nicknametree.h"
#include <algorithm>
#include <stack>

namespace nickname
{

namespace internal
{
const std::string& NickNameTreeNode::getValue() const
{
    if(!cacheIsLoaded)
    {
        std::stack<const NickNameTreeNode*> fillStack;
        const NickNameTreeNode* node = this;
        while(node)
        {
            fillStack.push(node);
            node = node->parent;
        }
        while(!fillStack.empty() )
        {
            cacheValue.append(fillStack.top()->value);
            fillStack.pop();
        }
        cacheIsLoaded = true;
    }
    return cacheValue;
}

}

void NickNameTree::insert(const std::string& str)
{
    if( str.empty() )
        return;

    std::stack<internal::InsertPair> insertStack;
    insertStack.push({str, &m_root});

    while(!insertStack.empty() )
    {
        internal::InsertPair insertPair = insertStack.top();
        insertStack.pop();

        auto ind = insertPair.value[0]-'a';
        internal::NickNameTreeNode* node = insertPair.insertNode->children[ind].get();

        while( node && !insertPair.value.empty() )
        {
            std::string& valueInTree = node->value;
            if( valueInTree.size() < insertPair.value.size() )
            {
                auto pair = std::mismatch( valueInTree.begin(), valueInTree.end(), insertPair.value.begin() );
                if( pair.first != valueInTree.end() )
                {
                    insertStack.emplace(std::string(pair.first, valueInTree.end() ), node);
                    valueInTree.assign(valueInTree.begin(), pair.first);
                    node->isEnd = false;
                }
                if(pair.second != insertPair.value.end() )
                {
                    ind = *pair.second - 'a';
                    insertPair.value.assign(pair.second, insertPair.value.end() );
                    insertPair.insertNode = node;
                    node = node->children[ind].get();
                }
            }
            else
            {
                auto pair = std::mismatch( insertPair.value.begin(), insertPair.value.end(), valueInTree.begin() );
                if(pair.second != valueInTree.end() )
                {
                    insertStack.emplace(std::string(pair.second, valueInTree.end() ), node);
                    valueInTree.assign(valueInTree.begin(), pair.second);
                    node->isEnd = false;
                }
                if( pair.first != insertPair.value.end() )
                {
                    ind = *pair.first - 'a';
                    insertPair.value.assign(pair.first, insertPair.value.end() );
                    insertPair.insertNode = node;
                    node = node->children[ind].get();
                }
            }
        }
        if( !insertPair.value.empty() )
            insertPair.insertNode->children[ind] =
                    std::make_unique<internal::NickNameTreeNode>(insertPair.value, insertPair.insertNode, true);
    }
}

NickNameTree::iterator NickNameTree::begin()
{
    nickname::internal::NickNameTreeNode* result = nullptr;

    for(nickname::internal::NickNameTreeNode* node = &m_root; node;)
    {
        size_t ind = 0;
        while(!node->children[ind] && ind < node->children.size() )
        {
            ++ind;
        }

        if(ind < node->children.size() )
        {
            if(node->children[ind]->isEnd)
            {
                result = node->children[ind].get();
                break;
            }
            node = node->children[ind].get();
        }
        else
            break;
    }
    return iterator(result);
}

}
