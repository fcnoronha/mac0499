#include <bits/stdc++.h>
#include "../linkCutTree.hpp"
#include "IncrementalMSF.hpp"

std::vector<std::pair<bool, edge>> IncrementalMSF::apply_add_operations(std::vector<edge> edges_to_add)
{
    std::vector<std::pair<bool, edge>> rollback_operations;
    for (edge e : edges_to_add)
    {
        e.id = current_unused_id++;
        edges_by_id[e.id] = e;

        if (!linkCutTree.is_connected(e.u, e.v))
        {
            linkCutTree.link(e.u, e.v, e.w, e.id);
            current_msf.insert(e.id);
            current_msf_cost += e.w;
            rollback_operations.push_back({true, e});
        }

        if (linkCutTree.maximum_edge(e.u, e.v) > e.w)
        {
            int maximum_edge_id = linkCutTree.maximum_edge_id(e.u, e.v);
            edge maximum_edge = edges_by_id[maximum_edge_id];

            linkCutTree.cut(maximum_edge.u, maximum_edge.v);
            current_msf.erase(maximum_edge.id);
            current_msf_cost -= maximum_edge.w;
            rollback_operations.push_back({false, maximum_edge});

            linkCutTree.link(e.u, e.v, e.w, e.id);
            current_msf.insert(e.id);
            current_msf_cost += e.w;
            rollback_operations.push_back({true, e});
        }
    }
    return rollback_operations;
}

void IncrementalMSF::apply_rollback(std::vector<std::pair<bool, edge>> rollback_operations)
{
    std::reverse(rollback_operations.begin(), rollback_operations.end());
    for (auto operation : rollback_operations)
    {
        bool should_cut = operation.first;
        edge e = operation.second;

        if (should_cut)
        {
            linkCutTree.cut(e.u, e.v);
            current_msf.erase(e.id);
            current_msf_cost -= e.w;
        }
        else
        {
            linkCutTree.link(e.u, e.v, e.w, e.id);
            current_msf.insert(e.id);
            current_msf_cost += e.w;
        }
    }
}

void IncrementalMSF::create_node(int u)
{
    linkCutTree.create_node(u);
}

void IncrementalMSF::add_edge(int u, int v, int w)
{
    edge newEdge = {u, v, w};
    auto _ = apply_add_operations({newEdge});
}

std::vector<edge> IncrementalMSF::get_msf()
{
    std::vector<edge> msf;
    for (int id : current_msf)
        msf.push_back(edges_by_id[id]);
    return msf;
}

std::vector<edge> IncrementalMSF::get_msf_after_operations(std::vector<edge> edges_to_add)
{
    auto rollback_operations = apply_add_operations(edges_to_add);
    auto msf = get_msf();
    apply_rollback(rollback_operations);
    return msf;
}

int IncrementalMSF::get_msf_cost()
{
    return current_msf_cost;
}

int IncrementalMSF::get_msf_cost_after_operations(std::vector<edge> edges_to_add)
{
    auto rollback_operations = apply_add_operations(edges_to_add);
    int msf_cost = get_msf_cost();
    apply_rollback(rollback_operations);
    return msf_cost;
}
