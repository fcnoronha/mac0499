#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "retroactiveMSF.hpp"

using namespace std;

TEST(RetroactiveMSFTest, SimpleTest)
{
    RetroactiveMSF rmsf;

    rmsf.add_edge(1, 2, 6, 1);
    rmsf.add_edge(1, 3, 4, 2);
    rmsf.add_edge(1, 4, 2, 3);
    rmsf.add_edge(1, 6, 4, 4);
    rmsf.add_edge(2, 4, 5, 5);
    rmsf.add_edge(3, 4, 8, 6);
    rmsf.add_edge(3, 5, 3, 7);
    rmsf.add_edge(4, 6, 3, 8);
    EXPECT_EQ(rmsf.get_msf_weight(10), 17);

    rmsf.add_edge(3, 2, 1, 9);
    EXPECT_EQ(rmsf.get_msf_weight(10), 13);
}

TEST(RetroactiveMSFTest, GrowingTimeTest)
{
    RetroactiveMSF rmsf;

    // creating just a tree
    rmsf.add_edge(1, 2, 3, 1);
    EXPECT_EQ(rmsf.get_msf_weight(1), 3);
    rmsf.add_edge(1, 3, 2, 2);
    EXPECT_EQ(rmsf.get_msf_weight(2), 5);
    rmsf.add_edge(1, 4, 5, 3);
    EXPECT_EQ(rmsf.get_msf_weight(3), 10);
    rmsf.add_edge(3, 5, 10, 4);
    EXPECT_EQ(rmsf.get_msf_weight(4), 20);
    rmsf.add_edge(3, 6, 1, 5);
    EXPECT_EQ(rmsf.get_msf_weight(5), 21);
    rmsf.add_edge(2, 7, 7, 6);
    EXPECT_EQ(rmsf.get_msf_weight(6), 28);
    rmsf.add_edge(5, 8, 5, 7);
    EXPECT_EQ(rmsf.get_msf_weight(7), 33);
    rmsf.add_edge(5, 9, 2, 8);
    EXPECT_EQ(rmsf.get_msf_weight(8), 35);
    rmsf.add_edge(6, 10, 4, 9);
    EXPECT_EQ(rmsf.get_msf_weight(9), 39);

    // adding edges to reduce the weight
    rmsf.add_edge(3, 8, 3, 10);
    EXPECT_EQ(rmsf.get_msf_weight(10), 32);
    rmsf.add_edge(4, 7, 1, 11);
    EXPECT_EQ(rmsf.get_msf_weight(11), 26);
    rmsf.add_edge(9, 10, 9, 12);
    EXPECT_EQ(rmsf.get_msf_weight(12), 26);
    rmsf.add_edge(2, 3, 2, 13);
    EXPECT_EQ(rmsf.get_msf_weight(13), 25);

    // checking weight afterwards
    EXPECT_EQ(rmsf.get_msf_weight(1), 3);
    EXPECT_EQ(rmsf.get_msf_weight(2), 5);
    EXPECT_EQ(rmsf.get_msf_weight(3), 10);
    EXPECT_EQ(rmsf.get_msf_weight(4), 20);
    EXPECT_EQ(rmsf.get_msf_weight(5), 21);
    EXPECT_EQ(rmsf.get_msf_weight(6), 28);
    EXPECT_EQ(rmsf.get_msf_weight(7), 33);
    EXPECT_EQ(rmsf.get_msf_weight(8), 35);
    EXPECT_EQ(rmsf.get_msf_weight(9), 39);
    EXPECT_EQ(rmsf.get_msf_weight(10), 32);
    EXPECT_EQ(rmsf.get_msf_weight(11), 26);
    EXPECT_EQ(rmsf.get_msf_weight(12), 26);
    EXPECT_EQ(rmsf.get_msf_weight(13), 25);
}

TEST(RetroactiveMSFTest, ShuffledTimeTest)
{
    RetroactiveMSF rmsf;

    // creating the same graph as above, but with edges shuffled
    rmsf.add_edge(1, 4, 5, 3);
    rmsf.add_edge(1, 2, 3, 1);
    rmsf.add_edge(2, 3, 2, 13);
    rmsf.add_edge(6, 10, 4, 9);
    rmsf.add_edge(9, 10, 9, 12);
    rmsf.add_edge(1, 3, 2, 2);
    rmsf.add_edge(2, 7, 7, 6);
    rmsf.add_edge(5, 8, 5, 7);
    rmsf.add_edge(3, 5, 10, 4);
    rmsf.add_edge(5, 9, 2, 8);
    rmsf.add_edge(3, 8, 3, 10);
    rmsf.add_edge(4, 7, 1, 11);
    rmsf.add_edge(3, 6, 1, 5);

    EXPECT_EQ(rmsf.get_msf_weight(1), 3);
    EXPECT_EQ(rmsf.get_msf_weight(2), 5);
    EXPECT_EQ(rmsf.get_msf_weight(3), 10);
    EXPECT_EQ(rmsf.get_msf_weight(4), 20);
    EXPECT_EQ(rmsf.get_msf_weight(5), 21);
    EXPECT_EQ(rmsf.get_msf_weight(6), 28);
    EXPECT_EQ(rmsf.get_msf_weight(7), 33);
    EXPECT_EQ(rmsf.get_msf_weight(8), 35);
    EXPECT_EQ(rmsf.get_msf_weight(9), 39);
    EXPECT_EQ(rmsf.get_msf_weight(10), 32);
    EXPECT_EQ(rmsf.get_msf_weight(11), 26);
    EXPECT_EQ(rmsf.get_msf_weight(12), 26);
    EXPECT_EQ(rmsf.get_msf_weight(13), 25);
}
