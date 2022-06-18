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

// Union-Find implementation to be used in the Kruskal Algorithm
struct UnionFind
{
    vector<int> id, sz;

    UnionFind(int _maxn) : id(_maxn), sz(_maxn)
    {
        for (int i = 0; i < _maxn; i++)
            id[i] = i, sz[i] = 1;
    }

    int find(int p)
    {
        if (id[p] == p)
            return p;
        return id[p] = find(id[p]);
    }

    void uni(int p, int q)
    {
        p = find(p);
        q = find(q);
        if (p == q)
            return;
        if (sz[p] > sz[q])
            swap(p, q);
        id[p] = q;
        sz[q] += sz[p];
    }
};

int kruskal(vector<pair<int, pair<int, int>>> edges, int max_vertex)
{
    UnionFind uf(max_vertex + 10);
    int current_cost = 0;
    sort(edges.begin(), edges.end());

    for (auto edge : edges)
    {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if (uf.find(u) != uf.find(v))
        {
            uf.uni(u, v);
            current_cost += w;
        }
    }

    return current_cost;
}

TEST(RetroactiveMSFTest, biTest)
{
    RetroactiveMSF rmsf;
    set<int> used_times;
    set<pair<pair<int, int>, pair<int, int>>> added_edges;

    mt19937 rng(123);
    uniform_int_distribution<std::mt19937::result_type> dist_vertex(1, 500);
    uniform_int_distribution<std::mt19937::result_type> dist_weight(1, 1000);
    uniform_int_distribution<std::mt19937::result_type> dist_time(1, 100000);

    // we'll perform 20 validation steps running kruskal algo
    for (int step = 1; step <= 20; step++)
    {
        for (int amt_edges = 1; amt_edges <= 100; amt_edges++)
        {
            int t = dist_time(rng);
            int u = dist_vertex(rng);
            int v = dist_vertex(rng);
            int w = dist_weight(rng);

            while (used_times.count(t) > 0)
            {
                t = dist_time(rng);
            }
            while (u == v)
            {
                v = dist_vertex(rng);
            }

            rmsf.add_edge(u, v, w, t);
            used_times.insert(t);
            added_edges.insert({{t, w}, {u, v}});
        }

        vector<pair<int, pair<int, int>>> edges_to_check;
        for (auto edge : added_edges)
        {
            int t = edge.first.first;
            int w = edge.first.second;
            int u = edge.second.first;
            int v = edge.second.second;

            edges_to_check.push_back({w, {u, v}});
            int from_kruskal = kruskal(edges_to_check, 500);
            int from_rmsf = rmsf.get_msf_weight(t);
            EXPECT_EQ(from_rmsf, from_kruskal);
        }
    }
}
