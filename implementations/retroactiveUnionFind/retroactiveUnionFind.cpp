#include <bits/stdc++.h>
#include "linkCutTree.hpp"
#include "retroactiveUnionFind.hpp"

void RetroactiveUnionFind::checkVerticesAlreadyConnected(int u, int v)
{
    if (linkCutTree.is_connected(u, v))
    {
        throw std::invalid_argument("vertices u and v are already connected");
    }
}

void RetroactiveUnionFind::checkEdgeExistAtTime(int t)
{
    if (edges_by_time.count(t) == 0)
    {
        throw std::invalid_argument("no given union at time t");
    }
}

void RetroactiveUnionFind::create_union(int u, int v, int t)
{
    linkCutTree.create_node(u);
    linkCutTree.create_node(v);
    checkVerticesAlreadyConnected(u, v);

    edges_by_time[t] = {u, v};
    linkCutTree.link(u, v, t);
}

void RetroactiveUnionFind::delete_union(int t)
{
    checkEdgeExistAtTime(t);

    std::pair<int, int> edge = edges_by_time[t];
    linkCutTree.cut(edge.first, edge.second);
    edges_by_time.erase(edges_by_time.find(t));
}

bool RetroactiveUnionFind::same_set(int u, int v, int t)
{
    linkCutTree.create_node(u);
    linkCutTree.create_node(v);

    if (!linkCutTree.is_connected(u, v))
        return false;

    return (linkCutTree.maximum_edge(u, v) <= t);
}
