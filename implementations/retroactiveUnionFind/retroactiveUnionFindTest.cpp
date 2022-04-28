#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "retroactiveUnionFind.hpp"

using namespace std;

TEST(LinkCutTreeTest, FirstTest)
{
    LinkCutTree lct_1;
    for (int i = 1; i <= 7; i++)
        lct_1.create_node(i);

    lct_1.link(1, 2, 20);
    lct_1.link(2, 3, 25);
    lct_1.link(4, 5, 40);
    EXPECT_EQ(lct_1.is_connected(1, 2), true);
    EXPECT_EQ(lct_1.is_connected(2, 3), true);
    EXPECT_EQ(lct_1.is_connected(4, 5), true);
    EXPECT_EQ(lct_1.is_connected(2, 5), false);
    EXPECT_EQ(lct_1.is_connected(6, 7), false);

    lct_1.make_root(2);
    EXPECT_EQ(lct_1.is_connected(1, 2), true);
    EXPECT_EQ(lct_1.is_connected(2, 3), true);
    EXPECT_EQ(lct_1.maximum_edge(1, 2), 20);
    EXPECT_EQ(lct_1.maximum_edge(1, 3), 25);
    EXPECT_EQ(lct_1.maximum_edge(4, 5), 40);

    lct_1.cut(2, 3);
    lct_1.link(1, 4, 10);
    lct_1.link(3, 7, 50);
    EXPECT_EQ(lct_1.is_connected(2, 5), true);
    EXPECT_EQ(lct_1.is_connected(2, 3), false);
    EXPECT_EQ(lct_1.is_connected(3, 7), true);
    EXPECT_EQ(lct_1.maximum_edge(2, 5), 40);
    EXPECT_EQ(lct_1.maximum_edge(3, 7), 50);
}

TEST(LinkCutTreeTest, SecondTest)
{
    LinkCutTree lct_2;
    for (int i = 1; i <= 9; i++)
        lct_2.create_node(i);

    lct_2.link(1, 2, 7);
    lct_2.link(1, 3, 6);
    lct_2.link(2, 4, 3);
    lct_2.link(2, 5, 1);
    lct_2.link(3, 6, 3);
    lct_2.link(3, 7, 5);
    lct_2.link(5, 8, 2);
    lct_2.link(7, 9, 4);
    EXPECT_EQ(lct_2.is_connected(1, 4), true);
    EXPECT_EQ(lct_2.is_connected(1, 9), true);
    EXPECT_EQ(lct_2.is_connected(9, 8), true);
    EXPECT_EQ(lct_2.maximum_edge(1, 2), 7);
    EXPECT_EQ(lct_2.maximum_edge(1, 4), 7);
    EXPECT_EQ(lct_2.maximum_edge(4, 3), 7);
    EXPECT_EQ(lct_2.maximum_edge(9, 6), 5);
    EXPECT_EQ(lct_2.maximum_edge(9, 8), 7);

    lct_2.cut(1, 2);
    lct_2.cut(3, 7);
    lct_2.link(1, 4, 0);
    lct_2.link(5, 7, 10);
    EXPECT_EQ(lct_2.is_connected(9, 6), true);
    EXPECT_EQ(lct_2.maximum_edge(6, 8), 6);
    EXPECT_EQ(lct_2.maximum_edge(9, 8), 10);
    EXPECT_EQ(lct_2.maximum_edge(9, 7), 4);
    EXPECT_EQ(lct_2.maximum_edge(4, 9), 10);
    EXPECT_EQ(lct_2.maximum_edge(4, 5), 3);
}

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
