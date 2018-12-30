#include <gtest/gtest.h>
#include "nicknametree.h"

TEST(NICKNAME_TEST, test1)
{
    nickname::NickNameTree nickNameTree;

    ASSERT_EQ(nickNameTree.size(), 0);

    nickNameTree.insert("astra");
    nickNameTree.insert("astral");
    nickNameTree.insert("b");

    ASSERT_EQ(nickNameTree.size(), 3);

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "astra");
    ASSERT_EQ(itr.shortValue(), "astra");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "astral");
    ASSERT_EQ(itr.shortValue(), "astral");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "b");
    ASSERT_EQ(itr.shortValue(), "b");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test2)
{
    nickname::NickNameTree nickNameTree;

    ASSERT_EQ(nickNameTree.size(), 0);

    nickNameTree.insert("astralp");
    nickNameTree.insert("astrak");
    nickNameTree.insert("astrals");
    nickNameTree.insert("bulks");
    nickNameTree.insert("bulkp");

    ASSERT_EQ(nickNameTree.size(), 5);

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "astrak");
    ASSERT_EQ(itr.shortValue(), "astrak");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "astralp");
    ASSERT_EQ(itr.shortValue(), "astralp");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "astrals");
    ASSERT_EQ(itr.shortValue(), "astrals");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "bulkp");
    ASSERT_EQ(itr.shortValue(), "bulkp");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "bulks");
    ASSERT_EQ(itr.shortValue(), "bulks");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test3)
{
    nickname::NickNameTree nickNameTree;

    nickNameTree.insert("alek");
    nickNameTree.insert("sasha");
    nickNameTree.insert("aleks");
    nickNameTree.insert("aleksey");
    nickNameTree.insert("alesha");

    ASSERT_EQ(nickNameTree.size(), 5);

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "alek");
    ASSERT_EQ(itr.shortValue(), "alek");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "aleks");
    ASSERT_EQ(itr.shortValue(), "aleks");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "aleksey");
    ASSERT_EQ(itr.shortValue(), "alekse");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "alesha");
    ASSERT_EQ(itr.shortValue(), "ales");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "sasha");
    ASSERT_EQ(itr.shortValue(), "s");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test4)
{
    nickname::NickNameTree nickNameTree;

    nickNameTree.insert("alek");
    nickNameTree.insert("alek");
    nickNameTree.insert("aleks");
    nickNameTree.insert("aleksey");
    nickNameTree.insert("alesha");

    ASSERT_EQ(nickNameTree.size(), 4);

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "alek");
    ASSERT_EQ(itr.shortValue(), "alek");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "aleks");
    ASSERT_EQ(itr.shortValue(), "aleks");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "aleksey");
    ASSERT_EQ(itr.shortValue(), "alekse");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "alesha");
    ASSERT_EQ(itr.shortValue(), "ales");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test5)
{
    nickname::NickNameTree nickNameTree;
    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test6)
{
    nickname::NickNameTree nickNameTree;
    nickNameTree.insert("val");
    nickNameTree.insert("val");
    nickNameTree.insert("val");
    ASSERT_EQ(nickNameTree.size(), 1);
    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "val");
    ASSERT_EQ(itr.shortValue(), "v");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}

TEST(NICKNAME_TEST, test7)
{
    nickname::NickNameTree nickNameTree;
    nickNameTree.insert("abcf");
    nickNameTree.insert("abdf");
    nickNameTree.insert("abdg");
    nickNameTree.insert("abef");
    nickNameTree.insert("bc");

    ASSERT_EQ(nickNameTree.size(), 5);

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr.fullValue(), "abcf");
    ASSERT_EQ(itr.shortValue(), "abc");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "abdf");
    ASSERT_EQ(itr.shortValue(), "abdf");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "abdg");
    ASSERT_EQ(itr.shortValue(), "abdg");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "abef");
    ASSERT_EQ(itr.shortValue(), "abe");
    ++itr;
    ASSERT_EQ(itr.fullValue(), "bc");
    ASSERT_EQ(itr.shortValue(), "b");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );
}
