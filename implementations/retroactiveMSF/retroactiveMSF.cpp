#include <bits/stdc++.h>
#include "../incrementalMSF/incrementalMSF.hpp"
#include "retroactiveMSF.hpp"

void RetroactiveMSF::check_time_is_available(int t)
{
    if (edges_by_time.find(t) != edges_by_time.end())
    {
        throw std::invalid_argument("an operation already exist at this time!");
    }
}

void RetroactiveMSF::check_vertex_exist(int u)
{
    if (vertices.count(u) == 0)
    {
        throw std::invalid_argument("vertex does not exist!");
    }
}

IncrementalMSF RetroactiveMSF::create_blank_imsf()
{
    IncrementalMSF newIMSF;
    for (auto u : vertices)
    {
        newIMSF.create_node(u);
    }
    return newIMSF;
}

void RetroactiveMSF::rebuild_structure()
{
    block_size = ceil(sqrt(edges_by_time.size()));
    insertions_left = (block_size + 1) / 2;
    checkpoint_time.clear();
    checkpoint_structure.clear();

    // building the decomposition from right to left in the timeline
    int position = edges_by_time.size();
    for (auto op = edges_by_time.rbegin(); op != edges_by_time.rend(); op++)
    {
        int t = (*op).first;
        edge e = (*op).second;

        if (position % block_size == 0)
        {
            checkpoint_time.push_back(t);
            checkpoint_structure.push_back(create_blank_imsf());
        }
        for (auto &imsf : checkpoint_structure)
        {
            imsf.add_edge(e.u, e.v, e.w);
        }
        position--;
    }

    // adding initial empty checkpoint
    checkpoint_time.push_back(0);
    checkpoint_structure.push_back(create_blank_imsf());

    // since we built backwards, now we reverse
    std::reverse(checkpoint_time.begin(), checkpoint_time.end());
    std::reverse(checkpoint_structure.begin(), checkpoint_structure.end());

    n_blocks = checkpoint_time.size();
}

int RetroactiveMSF::find_left_checkpoint_index(int t)
{
    int i = 0;
    while (i < n_blocks && checkpoint_time[i] <= t)
    {
        i++;
    }
    return i - 1;
}

std::vector<edge> RetroactiveMSF::get_delta_edge_operations(int t)
{
    int last_checkpoint_index = find_left_checkpoint_index(t);
    int last_checkpoint = checkpoint_time[last_checkpoint_index];

    std::vector<edge> delta_edge_operations;
    for (auto it = edges_by_time.upper_bound(last_checkpoint);
         it != edges_by_time.end() && (*it).first <= t;
         it++)
    {
        delta_edge_operations.push_back((*it).second);
    }

    return delta_edge_operations;
}

void RetroactiveMSF::create_node(int u)
{
    if (vertices.count(u) != 0)
    {
        return;
    }

    vertices.insert(u);
    for (auto &imsf : checkpoint_structure)
        imsf.create_node(u);
}

void RetroactiveMSF::add_edge(int u, int v, int w, int t)
{
    check_time_is_available(t);
    check_vertex_exist(u);
    check_vertex_exist(v);

    edge newEdge = {u, v, w, 0};
    edges_by_time[t] = newEdge;
    insertions_left--;

    if (insertions_left == 0)
    {
        rebuild_structure();
        return;
    }

    for (int i = find_left_checkpoint_index(t); i < n_blocks; i++)
    {
        checkpoint_structure[i].add_edge(u, v, w);
    }
}

std::vector<edge> RetroactiveMSF::get_msf(int t)
{
    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_after_operations(delta_edge_operations);
}

int RetroactiveMSF::get_msf_cost(int t)
{
    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_cost_after_operations(delta_edge_operations);
}
