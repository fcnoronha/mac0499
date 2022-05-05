#include <bits/stdc++.h>
#include "gtest/gtest.h"
#include "incrementalMSF.hpp"

using namespace std;

TEST(IncrementalMSFTest, SimpleTest)
{
    IncrementalMSF imsf;
    for (int i = 1; i <= 5; i++)
        imsf.create_node(i);

    imsf.add_edge(1, 2, 4);
    EXPECT_EQ(imsf.get_msf_cost(), 4);

    imsf.add_edge(2, 3, 5);
    imsf.add_edge(3, 4, 6);
    imsf.add_edge(4, 5, 7);
    EXPECT_EQ(imsf.get_msf_cost(), 22);

    imsf.add_edge(1, 4, 2);
    EXPECT_EQ(imsf.get_msf_cost(), 18);

    imsf.add_edge(2, 5, 6);
    EXPECT_EQ(imsf.get_msf_cost(), 17);
}

TEST(IncrementalMSFTest, ComplexTest)
{
    IncrementalMSF imsf;
    for (int i = 1; i <= 6; i++)
        imsf.create_node(i);

    imsf.add_edge(1, 2, 6);
    imsf.add_edge(1, 3, 4);
    imsf.add_edge(1, 4, 2);
    imsf.add_edge(1, 6, 4);
    imsf.add_edge(2, 4, 5);
    imsf.add_edge(3, 4, 8);
    imsf.add_edge(3, 5, 3);
    imsf.add_edge(4, 6, 3);
    EXPECT_EQ(imsf.get_msf_cost(), 17);

    imsf.add_edge(3, 2, 1);
    EXPECT_EQ(imsf.get_msf_cost(), 13);
}

TEST(IncrementalMSFTest, OperationsTest)
{
    IncrementalMSF imsf;
    for (int i = 1; i <= 5; i++)
        imsf.create_node(i);

    imsf.add_edge(1, 2, 4);
    imsf.add_edge(2, 3, 5);
    imsf.add_edge(3, 4, 6);
    imsf.add_edge(4, 5, 7);
    auto initial_msf = imsf.get_msf();

    Edge e1 = Edge(1, 4, 2, 0);
    Edge e2 = Edge(2, 5, 6, 0);
    int operations_msf_cost = imsf.get_msf_cost_after_operations({e1, e2});
    EXPECT_EQ(operations_msf_cost, 17);

    auto final_msf = imsf.get_msf();
    EXPECT_EQ(initial_msf, final_msf);
}
