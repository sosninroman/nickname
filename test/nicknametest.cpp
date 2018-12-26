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
    ASSERT_EQ(*itr, "astra");
    ++itr;
    ASSERT_EQ(*itr, "astral");
    ++itr;
    ASSERT_EQ(*itr, "b");
    ++itr;
    ASSERT_EQ(itr, nickNameTree.end() );

    nickname::NickNameTree nickNameTree2;

    nickNameTree2.insert("astralp");
    nickNameTree2.insert("astrak");
    nickNameTree2.insert("astrals");
    nickNameTree2.insert("bulks");
    nickNameTree2.insert("bulkp");

    auto itr2 = nickNameTree2.begin();
    ASSERT_EQ(*itr2, "astrak");
    ++itr2;
    ASSERT_EQ(*itr2, "astralp");
    ++itr2;
    ASSERT_EQ(*itr2, "astrals");
    ++itr2;
    ASSERT_EQ(*itr2, "bulkp");
    ++itr2;
    ASSERT_EQ(*itr2, "bulks");
    ++itr2;
    ASSERT_EQ(itr2, nickNameTree2.end() );
}
