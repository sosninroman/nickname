#include "nicknametree.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>

namespace nickname
{

namespace internal
{

void NickNameTreeIterator::switchToNext()
{
    auto child = findDown(node, 0);
    if(child)
    {
        node = child;
    }
    else
    {
        assert(!node->value.empty() );
        auto ind = node->value[0] - ALPHABET_FIRST_SYMBOL;
        assert(ind >= 0 && ind <= ALPHABET_SIZE);
        node = node->parent;
        while(node)
        {
            auto child = findDown(node, ind+1);
            if(child)
            {
                node = child;
                break;
            }
            else
            {
                if(node->parent)
                {
                    assert(!node->value.empty() );
                    ind = node->value[0] - ALPHABET_FIRST_SYMBOL;
                }
                node = node->parent;
            }
        }
    }
}

NickNameTreeNode* NickNameTreeIterator::findDown(NickNameTreeNode* startNode, size_t startInd)
{
    std::stack<NickNameTreeNode*> searchStack;
    searchStack.push(startNode);
    while(!searchStack.empty() )
    {
        NickNameTreeNode* searchNode = searchStack.top();
        searchStack.pop();
        for(auto ind = startInd; ind < searchNode->children.size(); ++ind)
        {
            auto child = searchNode->child(ind);
            if(child)
            {
                if(child->isEnd)
                {
                    return child;
                }
                else
                {
                    searchStack.push(child);
                }
                break;
            }
        }
        startInd = 0;
    }
    return nullptr;
}

const std::string& NickNameTreeNode::getFullValue() const
{
    if(!fullValueIsLoaded)
    {
        if(!parent)
            fullValue = value;
        else
        {
            auto prev = parent->getFullValue();
            fullValue = prev + value;
        }
        fullValueIsLoaded = true;
    }
    return fullValue;
}

const std::string& NickNameTreeNode::getShortValue() const
{
    if(!shortValueIsLoaded)
    {
        if(parent)
        {
            shortValue = parent->getFullValue();
        }
        bool hasChildren = false;
        for(const auto& child : children)
        {
            if(child)
            {
                hasChildren = true;
                break;
            }
        }
        if(hasChildren)
        {
            shortValue += value;
        }
        else if(!value.empty() )
        {
            shortValue += value.front();
        }
        shortValueIsLoaded = true;
    }
    return shortValue;
}

}

void NickNameTree::splitNode(internal::NickNameTreeNode& node, std::string::iterator splitIterator)
{
    node.isEnd = false;
    auto newChild =
            std::make_unique<internal::NickNameTreeNode>(std::string(splitIterator, node.value.end() ), nullptr, true);
    for(size_t pos = 0; pos < ALPHABET_SIZE; ++pos)
    {
        if(node.children[pos])
        {
            node.children[pos]->parent = newChild.get();
            newChild->children[pos] = std::move(node.children[pos]);
        }
    }
    newChild->parent = &node;

    auto ind = *splitIterator - ALPHABET_FIRST_SYMBOL;
    assert(ind >= 0 && ind <= ALPHABET_SIZE);
    node.children[ind] = std::move(newChild);
    node.value.assign(node.value.begin(), splitIterator);
}

void NickNameTree::insert(std::string insVal)
{
    if(insVal.empty() )
        return;

    internal::NickNameTreeNode* parentNode = &m_root;
    auto ind = insVal[0] - ALPHABET_FIRST_SYMBOL;
    assert(ind >= 0 && ind <= ALPHABET_SIZE);

    while(parentNode->child(ind) && !insVal.empty() )
    {
        auto& valueInTree = parentNode->child(ind)->value;
        if(valueInTree.size() < insVal.size() )
        {
            const auto pair = std::mismatch(valueInTree.begin(), valueInTree.end(), insVal.begin() );
            if(pair.first != valueInTree.end() )
            {
                splitNode(*parentNode->child(ind), pair.first);
            }
            insVal.assign(pair.second, insVal.end() );
        }
        else
        {
            const auto pair = std::mismatch(insVal.begin(), insVal.end(), valueInTree.begin() );
            if(pair.second != valueInTree.end() )
            {
                splitNode(*parentNode->child(ind), pair.second);
            }
            insVal.assign(pair.first, insVal.end() );
        }
        parentNode = parentNode->child(ind);
        if(!insVal.empty() )
        {
            ind = insVal[0] - ALPHABET_FIRST_SYMBOL;
        }
    }
    if(!insVal.empty() )
    {
        parentNode->children[ind] =
                std::make_unique<internal::NickNameTreeNode>(insVal, parentNode, true);
        ++m_size;
    }
}

NickNameTree::iterator NickNameTree::begin() const
{
    nickname::internal::NickNameTreeNode* result = nullptr;

    for(auto node = &m_root; node;)
    {
        internal::NickNameTreeNode* nextNode = nullptr;
        for(const auto& child : node->children)
        {
            if(child)
            {
                if(child->isEnd)
                {
                    result = child.get();
                }
                else
                {
                    nextNode = child.get();
                }
                break;
            }
        }
        node = nextNode;
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
