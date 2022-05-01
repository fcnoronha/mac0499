#pragma once

#include <bits/stdc++.h>
#include "../linkCutTree.hpp"

struct edge
{
    int u, v, w;
    int id;

    bool operator==(const edge &e) const
    {
        return (u == e.u && v == e.v && w == e.w && id == e.id);
    }
};

class IncrementalMSF
{
private:
    LinkCutTree linkCutTree;
    std::map<int, edge> edges_by_id;
    std::set<int> current_msf;
    int current_msf_cost = 0;
    int current_unused_id = 1;

    // ADICIONAR CHECKS

    /* Sanitization method used to check . */
    void check_vertices_already_connected(int, int);

    /* Sanitization method used to check . */
    void check_union_already_exist_at_time(int);

    /* Sanitization method used to check . */
    void check_union_do_not_exist_at_time(int);

    /* Apply a list of add_edge operations into the structure and return a list
       of pairs <bool, edge> that can be used to perform the rollback of these
       operations, where the boolean value tell wether or not we should perform
       a cut on that edge. */
    std::vector<std::pair<bool, edge>> apply_operations(std::vector<edge>);

    /* Apply the rollbacks in the structure. */
    void apply_rollback(std::vector<std::pair<bool, edge>>);

public:
    /* Create a new node in the forest. */
    void create_node(int);

    /* Add edge into the graph, and possibly into the MSF. */
    void add_edge(int, int, int);

    /* Return a list of edges that compose the MSF. */
    std::vector<edge> get_msf();

    /* Return a list of edges that compose the MSF after a sequence of add_edge
       operations, doing this without copying the structure. */
    std::vector<edge> get_msf_after_operations(std::vector<edge>);

    /* Return the cost of the MSF. */
    int get_msf_cost();

    /* Return the cost of the MSF after a sequence of add_edge operations, doing
       this without copying the structure. */
    int get_msf_cost_after_operations(std::vector<edge>);
};