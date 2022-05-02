#pragma once

#include <bits/stdc++.h>
#include "../incrementalMSF/incrementalMSF.hpp"

class RetroactiveMSF
{
private:
   std::vector<IncrementalMSF> incrementalMSF;
   std::vector<int> checkpoints;
   std::map<int, edge> edges_by_time;
   std::set<int> vertices;
   int block_size = 1;
   int insertions_left = 1;

   /* Sanitization method used to check wether or not we already have an
      add_edge operation at time t. */
   void check_time_is_available(int);

   /* Sanitization method used to check wether or not a vertex exist in the
      structure. */
   void check_vertex_exist(int);

   /* Rebuilds the square-root decomposition of the timeline, changing the
      block_size and defining new checkpoints. This is used to maintain the
      O(√N lgN) complexity of the add_edge method. This will also add a
      O(√N lgN) amortized constraint to all calls. */
   void rebuild_structure();

   /* Return the index of the checkpoint to the left of time t in the timeline,
      that is, the last checkpoint smaller than t. */
   int find_left_checkpoint_index(int);

   /* Return a vector containing all the edges that were added after the last
      checkpoint smaller than t and t. In other words, let ct be the time of
      the last checkpoint smaller than t, then it will return all the edges
      added in the range [tc+1, t]. */
   std::vector<edge> get_delta_edge_operations(int);

public:
   /* Create a new node in the graph if it doens't already exist. */
   void create_node(int);

   /* Add an edge from node u to v with weigth w into the graph at the time t. */
   void add_edge(int, int, int, int);

   /* Return the list of edges that compose the MSF at time t. */
   std::vector<edge> get_msf(int);

   /* Return the cost of the MSF at time t. */
   int get_msf_cost(int);
};