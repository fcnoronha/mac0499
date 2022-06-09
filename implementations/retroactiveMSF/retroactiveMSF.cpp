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

void RetroactiveMSF::rebuild_decomposition()
{
    block_size++;
    n_blocks = block_size + 1;

    int position = 0;
    std::vector<int> new_checkpoint_time(1, 0);
    for (auto op : edges_by_time)
    {
        position++;
        int time = op.first;
        if (position % block_size == 0)
        {
            new_checkpoint_time.push_back(time);
        }
    }

    checkpoint_structure.insert(checkpoint_structure.begin(), IncrementalMSF());
    checkpoint_structure.insert(checkpoint_structure.begin(), IncrementalMSF());
    while (checkpoint_structure.size() > new_checkpoint_time.size())
    {
        checkpoint_structure.pop_back();
    }

    move_imsf_checkpoint(checkpoint_structure[1], new_checkpoint_time[1], -1);
    for (int i = 2; i < (int)checkpoint_structure.size(); i++)
    {
        move_imsf_checkpoint(checkpoint_structure[i], new_checkpoint_time[i], checkpoint_time[i - 2]);
    }

    checkpoint_time = new_checkpoint_time;
}

void RetroactiveMSF::move_imsf_checkpoint(IncrementalMSF &imsf, int new_checkpoint_time, int old_checkpoint_time)
{
    for (auto it = edges_by_time.upper_bound(old_checkpoint_time);
         it != edges_by_time.end() && (*it).first <= new_checkpoint_time;
         it++)
    {
        auto edge = (*it).second;
        imsf.add_edge(edge.u, edge.v, edge.w);
    }
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

    for (int i = find_left_checkpoint_index(t) + 1; i < n_blocks; i++)
    {
        checkpoint_structure[i].add_edge(u, v, w);
    }

    if ((block_size + 1) * (block_size + 1) == (int)edges_by_time.size())
    {
        rebuild_decomposition();
    }
}

std::vector<Edge> RetroactiveMSF::get_msf(int t)
{
    check_time_is_valid(t);

    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_after_operations(delta_edge_operations);
}

int RetroactiveMSF::get_msf_weight(int t)
{
    check_time_is_valid(t);

    int last_checkpoint_index = find_left_checkpoint_index(t);
    auto delta_edge_operations = get_delta_edge_operations(t);
    return checkpoint_structure[last_checkpoint_index].get_msf_weight_after_operations(delta_edge_operations);
}
