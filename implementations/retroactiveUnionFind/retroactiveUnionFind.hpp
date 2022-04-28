#pragma once

#include <bits/stdc++.h>
#include "../linkCutTree.hpp"

class RetroactiveUnionFind
{
private:
    LinkCutTree linkCutTree;
    std::map<int, std::pair<int, int>> edges_by_time;

    /* Sanitization method used to check if two nodes are connected before linking. */
    void check_vertices_already_connected(int, int);

    /* Sanitization method used to check if a union at time t already exists. */
    void check_union_already_exist_at_time(int);

    /* Sanitization method used to check if the union set to be deleted at time
       t really exists. */
    void check_union_do_not_exist_at_time(int);

public:
    /* Create a union between elements u and v at the time t. */
    void create_union(int, int, int);

    /* Deletes the union created at time t. */
    void delete_union(int);

    /* Given nodes u and v check if they are connected at the instant t. */
    bool same_set(int, int, int);
};