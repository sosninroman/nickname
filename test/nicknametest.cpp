#include <gtest/gtest.h>
#include "nicknametreeaccessor.h"

TEST(NICKNAME_TEST, nickname_test)
{
    nickname::NickNameTree nickNameTree;
    ASSERT_TRUE(nicknametest::NickNameTreeAccessor::getRootNode(nickNameTree) );

    nickNameTree.insert("astra");
    nickNameTree.insert("astral");
    nickNameTree.insert("b");

    auto itr = nickNameTree.begin();
    ASSERT_EQ(itr->first, "astra");
    ASSERT_EQ(itr->second, "astra");
    ++itr;
    ASSERT_EQ(itr->first, "astral");
    ASSERT_EQ(itr->second, "astral");
    ++itr;
    ASSERT_EQ(itr->first, "b");
    ASSERT_EQ(itr->second, "b");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );

    nickname::NickNameTree nickNameTree2;

    nickNameTree2.insert("astralp");
    nickNameTree2.insert("astrak");
    nickNameTree2.insert("astrals");
    nickNameTree2.insert("bulks");
    nickNameTree2.insert("bulkp");

    auto itr2 = nickNameTree2.begin();
    ASSERT_EQ(itr2->first, "astrak");
    ASSERT_EQ(itr2->second, "astrak");
    ++itr2;
    ASSERT_EQ(itr2->first, "astralp");
    ASSERT_EQ(itr2->second, "astralp");
    ++itr2;
    ASSERT_EQ(itr2->first, "astrals");
    ASSERT_EQ(itr2->second, "astrals");
    ++itr2;
    ASSERT_EQ(itr2->first, "bulkp");
    ASSERT_EQ(itr2->second, "bulkp");
    ++itr2;
    ASSERT_EQ(itr2->first, "bulks");
    ASSERT_EQ(itr2->second, "bulks");
    ++itr2;
    ASSERT_EQ(itr2, nickNameTree2.end() );
}
