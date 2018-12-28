#include "nicknametree.h"
#include <algorithm>
#include <stack>
#include <iostream>
#include <iomanip>

namespace nickname
{

namespace internal
{
const std::pair<std::string, std::string> &NickNameTreeNode::getValue() const
{
    if(!cacheIsLoaded)
    {
        std::stack<const NickNameTreeNode*> nodesStack;
        const NickNameTreeNode* node = this;
        while(node)
        {
            nodesStack.push(node);
            node = node->parent;
        }
        while(!nodesStack.empty() )
        {
            const NickNameTreeNode* node = nodesStack.top();
            cacheValue.first.append(node->value);
            node->cacheValue.first = cacheValue.first;
            if(node->parent)
            {
                std::string prefix;
                if(node->parent->getValue().first.empty() )
                    prefix = node->value;
                else
                    prefix = node->parent->getValue().first + std::string(node->value.begin(), node->value.begin()+1);
                node->cacheValue.second = prefix;
            }
            node->cacheIsLoaded = true;
            nodesStack.pop();
        }
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

void NickNameTree::print() const
{
    std::stack<internal::NickNameTreeNode*> nodeStack;
    std::stack<int> depthStack;
    for(auto& node : m_root.children)
    {
        if(node)
        {
            nodeStack.push(node.get() );
            depthStack.push(0);
            while(!nodeStack.empty() )
            {
                internal::NickNameTreeNode* node = nodeStack.top();
                int depth = depthStack.top();
                depthStack.pop();
                nodeStack.pop();
                std::cout << std::setfill('|')
                          << std::setw(depth + node->value.size() + 1)
                          << std::string("+")+node->value
                          << (node->isEnd ? '$' : ' ')
                          << std::endl;
                for(auto& child : node->children)
                {
                    if(child)
                    {
                        nodeStack.push(child.get() );
                        depthStack.push(depth+1);
                    }
                }
            }
        }
    }
}

}
