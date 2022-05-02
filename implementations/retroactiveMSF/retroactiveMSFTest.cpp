#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "retroactiveMSF.hpp"

using namespace std;

TEST(RetroactiveMSFTest, SimpleTest)
{
    RetroactiveMSF rmsf;
    for (int i = 1; i <= 6; i++)
        rmsf.create_node(i);

    rmsf.add_edge(1, 2, 6, 1);
    rmsf.add_edge(1, 3, 4, 2);
    rmsf.add_edge(1, 4, 2, 3);
    rmsf.add_edge(1, 6, 4, 4);
    rmsf.add_edge(2, 4, 5, 5);
    rmsf.add_edge(3, 4, 8, 6);
    rmsf.add_edge(3, 5, 3, 7);
    rmsf.add_edge(4, 6, 3, 8);
    EXPECT_EQ(rmsf.get_msf_cost(10), 17);

    rmsf.add_edge(3, 2, 1, 9);
    EXPECT_EQ(rmsf.get_msf_cost(10), 13);
}
