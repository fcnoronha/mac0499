#include <bits/stdc++.h>
#include "../linkCutTree.hpp"
#include "incrementalMSF.hpp"

std::vector<std::pair<bool, Edge>> IncrementalMSF::apply_add_operations(std::vector<Edge> edges_to_add)
{
    std::vector<std::pair<bool, Edge>> rollback_operations;
    for (Edge edge : edges_to_add)
    {
        edge.id = current_unused_id++;
        edges_by_id[edge.id] = edge;

        linkCutTree.create_node(edge.u);
        linkCutTree.create_node(edge.v);

        if (!linkCutTree.is_connected(edge.u, edge.v))
        {
            linkCutTree.link(edge.u, edge.v, edge.w, edge.id);
            current_msf.insert(edge.id);
            current_msf_cost += edge.w;
            rollback_operations.push_back({true, edge});
        }

        if (linkCutTree.maximum_edge(edge.u, edge.v) > edge.w)
        {
            int maximum_edge_id = linkCutTree.maximum_edge_id(edge.u, edge.v);
            Edge maximum_edge = edges_by_id[maximum_edge_id];

            linkCutTree.cut(maximum_edge.u, maximum_edge.v);
            current_msf.erase(maximum_edge.id);
            current_msf_cost -= maximum_edge.w;
            rollback_operations.push_back({false, maximum_edge});

            linkCutTree.link(edge.u, edge.v, edge.w, edge.id);
            current_msf.insert(edge.id);
            current_msf_cost += edge.w;
            rollback_operations.push_back({true, edge});
        }
    }
    return rollback_operations;
}

void IncrementalMSF::apply_rollback(std::vector<std::pair<bool, Edge>> rollback_operations)
{
    std::reverse(rollback_operations.begin(), rollback_operations.end());
    for (auto operation : rollback_operations)
    {
        bool should_cut = operation.first;
        Edge edge = operation.second;

        if (should_cut)
        {
            linkCutTree.cut(edge.u, edge.v);
            current_msf.erase(edge.id);
            current_msf_cost -= edge.w;
        }
        else
        {
            linkCutTree.link(edge.u, edge.v, edge.w, edge.id);
            current_msf.insert(edge.id);
            current_msf_cost += edge.w;
        }
    }
}

void IncrementalMSF::add_edge(int u, int v, int w)
{
    Edge newEdge = Edge(u, v, w);
    auto _ = apply_add_operations({newEdge});
}

std::vector<Edge> IncrementalMSF::get_msf()
{
    std::vector<Edge> msf;
    for (int id : current_msf)
        msf.push_back(edges_by_id[id]);
    return msf;
}

std::vector<Edge> IncrementalMSF::get_msf_after_operations(std::vector<Edge> edges_to_add)
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

int IncrementalMSF::get_msf_cost_after_operations(std::vector<Edge> edges_to_add)
{
    auto rollback_operations = apply_add_operations(edges_to_add);
    int msf_cost = get_msf_cost();
    apply_rollback(rollback_operations);
    return msf_cost;
}
