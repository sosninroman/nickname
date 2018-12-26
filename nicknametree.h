#ifndef NICKNAMETREE_H
#define NICKNAMETREE_H

#include <stack>
#include <memory>
#include <array>
#include <string>

namespace nicknametest
{
class NickNameTreeAccessor;
}

namespace nickname
{

namespace internal
{

class NickNameTreeIterator;

struct NickNameTreeNode
{
    NickNameTreeNode() = default;
    NickNameTreeNode(std::string str, NickNameTreeNode* parent, bool isEnd = false):
        value(std::move(str) ),isEnd(isEnd), parent(parent){}

    std::string value;
    bool isEnd = false;
    std::array<std::unique_ptr<NickNameTreeNode>, 26> children;

    friend class NickNameTreeIterator;
private:
    const std::string& getValue() const;

    NickNameTreeNode* parent = nullptr;
    mutable std::string cacheValue;
    mutable bool cacheIsLoaded = false;
};

struct InsertPair
{
    InsertPair(std::string v, NickNameTreeNode* ptr):value(std::move(v) ), insertNode(ptr){}
    std::string value;
    NickNameTreeNode* insertNode;
};

class NickNameTreeIterator
{
public:
    typedef std::bidirectional_iterator_tag iterator_category;

    explicit NickNameTreeIterator(NickNameTreeNode* node = nullptr) noexcept:
        node(node)
    {
    }

    const std::string& operator*() const noexcept
    {
        return node->getValue();
    }

    const std::string* operator->() const noexcept
    {
        return &(node->value);
    }

    NickNameTreeIterator& operator++() noexcept
    {
        switchToNext();
        return *this;
    }

    NickNameTreeIterator operator++(int) noexcept
    {
        NickNameTreeIterator tmp = *this;
        switchToNext();
        return tmp;
    }

    bool operator==(const NickNameTreeIterator& rhs) const noexcept
    { return node == rhs.node; }

    bool operator!=(const NickNameTreeIterator& rhs) const noexcept
    { return node != rhs.node; }

private:

    void switchToNext()
    {
        auto child = findDown(node, 0);
        if(child)
        {
            node = child;
        }
        else
        {
            auto ind = node->value[0] - 'a';
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
                    ind = node->value[0] - 'a';
                    node = node->parent;
                }
            }
        }
    }

    NickNameTreeNode* findDown(NickNameTreeNode* startNode, size_t startInd)
    {
        std::stack<NickNameTreeNode*> searchStack;
        searchStack.push(startNode);
        while(!searchStack.empty() )
        {
            NickNameTreeNode* searchNode = searchStack.top();
            searchStack.pop();
            for(auto ind = startInd; ind < searchNode->children.size(); ++ind)
            {
                auto child = searchNode->children[ind].get();
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
                }
            }
        }
        return nullptr;
    }

    NickNameTreeNode* node;
};

}

class NickNameTree
{
public:
    using iterator = nickname::internal::NickNameTreeIterator;

    NickNameTree() = default;

    size_t size() const {return m_size;}

    void insert(const std::string& str);

    iterator begin();
    iterator end()
    {
        return iterator();
    }
private:
    friend class nicknametest::NickNameTreeAccessor;
    size_t m_size;
    internal::NickNameTreeNode m_root;
};

}

#endif
