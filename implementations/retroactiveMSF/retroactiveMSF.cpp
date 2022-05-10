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

void RetroactiveMSF::check_time_is_valid(int t)
{
    if (t <= 0)
    {
        throw std::invalid_argument("union time is invalid, must be greater than 0!");
    }
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
        int time = (*op).first;
        Edge edge = (*op).second;

        if (position % block_size == 0)
        {
            checkpoint_time.push_back(time);
            checkpoint_structure.push_back(IncrementalMSF());
        }
        for (auto &imsf : checkpoint_structure)
        {
            imsf.add_edge(edge.u, edge.v, edge.w);
        }
        position--;
    }

    // adding initial empty checkpoint
    checkpoint_time.push_back(0);
    checkpoint_structure.push_back(IncrementalMSF());

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

std::vector<Edge> RetroactiveMSF::get_delta_edge_operations(int t)
{
    int last_checkpoint_index = find_left_checkpoint_index(t);
    int last_checkpoint = checkpoint_time[last_checkpoint_index];
    auto edge_added_after_checkpoint = edges_by_time.upper_bound(last_checkpoint);

    std::vector<Edge> delta_edge_operations;
    for (auto it = edge_added_after_checkpoint;
         it != edges_by_time.end() && (*it).first <= t;
         it++)
    {
        delta_edge_operations.push_back((*it).second);
    }

    return delta_edge_operations;
}

void RetroactiveMSF::add_edge(int u, int v, int w, int t)
{
    check_time_is_available(t);
    check_time_is_valid(t);

    Edge newEdge = Edge(u, v, w);
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

std::vector<Edge> RetroactiveMSF::get_msf(int t)
{
    check_time_is_valid(t);

    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_after_operations(delta_edge_operations);
}

int RetroactiveMSF::get_msf_cost(int t)
{
    check_time_is_valid(t);

    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_cost_after_operations(delta_edge_operations);
}
