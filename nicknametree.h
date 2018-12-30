#ifndef NICKNAMETREE_H
#define NICKNAMETREE_H

#include <utility>
#include <memory>
#include <array>
#include <string>

namespace nickname
{

const int ALPHABET_SIZE = 26;
const char ALPHABET_FIRST_SYMBOL = 'a';

namespace internal
{

class NickNameTreeIterator;

struct NickNameTreeNode
{
    NickNameTreeNode() = default;
    NickNameTreeNode(std::string str, NickNameTreeNode* parent, bool isEnd = false):
        value(std::move(str) ),isEnd(isEnd), parent(parent){}

    NickNameTreeNode* child(size_t ind) {return children[ind].get();}

    const std::string& getFullValue() const;
    const std::string& getShortValue() const;

    std::string value;
    bool isEnd = false;
    std::array<std::unique_ptr<NickNameTreeNode>, ALPHABET_SIZE> children;
    NickNameTreeNode* parent = nullptr;

private:
    mutable std::string fullValue;
    mutable bool fullValueIsLoaded = false;
    mutable std::string shortValue;
    mutable bool shortValueIsLoaded = false;
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

    const std::string& fullValue() const
    {
        return node->getFullValue();
    }

    const std::string& shortValue() const
    {
        return node->getShortValue();
    }

    const std::string& operator*() const noexcept
    {
        return node->value;
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
    void switchToNext();
    NickNameTreeNode* findDown(NickNameTreeNode* startNode, size_t startInd);

    NickNameTreeNode* node;
};

}

class NickNameTree
{
public:
    using iterator = nickname::internal::NickNameTreeIterator;

    NickNameTree() = default;

    size_t size() const {return m_size;}

    void insert(std::string insVal);

    iterator begin() const;
    iterator end() const { return iterator();}

    void print() const;
private:
    void splitNode(internal::NickNameTreeNode &node, std::string::iterator splitIterator);
    size_t m_size = 0;
    internal::NickNameTreeNode m_root;
};

}

#endif
