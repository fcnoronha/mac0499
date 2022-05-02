#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "retroactiveUnionFind.hpp"

using namespace std;

TEST(RetroactiveUnionFindTest, StaticOperations)
{
    RetroactiveUnionFind ruf;

    ruf.create_union(1, 2, 1);
    ruf.create_union(2, 3, 2);
    ruf.create_union(5, 6, 3);
    ruf.create_union(6, 7, 4);
    EXPECT_EQ(ruf.same_set(1, 2, 4), true);
    EXPECT_EQ(ruf.same_set(1, 3, 4), true);
    EXPECT_EQ(ruf.same_set(5, 6, 4), true);
    EXPECT_EQ(ruf.same_set(6, 7, 4), true);
    EXPECT_EQ(ruf.same_set(1, 5, 4), false);

    ruf.create_union(2, 7, 5);
    EXPECT_EQ(ruf.same_set(1, 5, 5), true);
}

TEST(RetroactiveUnionFindTest, PersistentOperations)
{
    RetroactiveUnionFind ruf;

    ruf.create_union(1, 2, 1);
    ruf.create_union(2, 3, 2);
    ruf.create_union(5, 6, 3);
    ruf.create_union(6, 7, 4);
    EXPECT_EQ(ruf.same_set(1, 3, 1), false);
    EXPECT_EQ(ruf.same_set(1, 3, 2), true);

    ruf.create_union(2, 7, 6);
    EXPECT_EQ(ruf.same_set(1, 5, 1), false);
    EXPECT_EQ(ruf.same_set(1, 5, 6), true);
}

TEST(RetroactiveUnionFindTest, RetroactiveOperations)
{
    RetroactiveUnionFind ruf;

    ruf.create_union(1, 2, 1);
    ruf.create_union(2, 3, 2);
    ruf.create_union(3, 4, 3);
    ruf.create_union(5, 6, 4);

    EXPECT_EQ(ruf.same_set(1, 4, 4), true);
    EXPECT_EQ(ruf.same_set(3, 6, 4), false);
    EXPECT_EQ(ruf.same_set(5, 6, 4), true);

    ruf.delete_union(4);
    ruf.create_union(1, 6, 5);
    EXPECT_EQ(ruf.same_set(3, 5, 5), false);
    EXPECT_EQ(ruf.same_set(3, 6, 5), true);
}
