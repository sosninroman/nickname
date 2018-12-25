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
    ASSERT_EQ(*itr, "l");
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
    ASSERT_EQ(*itr2, "k");
    ++itr2;
    ASSERT_EQ(*itr2, "p");
    ++itr2;
    ASSERT_EQ(*itr2, "s");
    ++itr2;
    ASSERT_EQ(*itr2, "p");
    ++itr2;
    ASSERT_EQ(*itr2, "s");
    ++itr2;
    ASSERT_EQ(itr2, nickNameTree2.end() );
}
