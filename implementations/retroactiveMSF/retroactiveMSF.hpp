#pragma once

#include <bits/stdc++.h>
#include "../incrementalMSF/incrementalMSF.hpp"

#define dbg(x) std::cerr << "-- BDG -- " << #x << " = " << x << std::endl

class RetroactiveMSF
{
private:
   std::vector<IncrementalMSF> checkpoint_structure;
   std::vector<int> checkpoint_time;
   std::map<int, Edge> edges_by_time;
   int block_size = 0;
   int n_blocks = 0;

   /* Sanitization method used to check wether or not we already have an
      add_edge operation at time t. */
   void check_time_is_available(int);

   /* Sanitization method used to check wether or not the time t is valid for
      an operation, that is, it is grater than 0. */
   void check_time_is_valid(int);

   /* Sanitization method used to check wether or not a vertex exist in the
      structure. */
   void check_vertex_exist(int);

   /* Rebuilds the square-root decomposition of the timeline, changing the
      block_size and defining new checkpoints. This is used to maintain the
      O(√N lgN) complexity of the add_edge method. This will also add a
      O(√N lgN) amortized constraint to all add_edge calls. */
   void rebuild_decomposition();

   /* Moves the Incremental MSF from one checkpoint to another one to the right
      of it in the timeline. */
   void move_imsf_checkpoint(IncrementalMSF &, int, int);

   /* Return the index of the checkpoint to the left of time t in the timeline,
      that is, the last checkpoint smaller than or equal to t. */
   int find_left_checkpoint_index(int);

   /* Return a vector containing all the edges that were added after the last
      checkpoint smaller than t and t. In other words, let ct be the time of
      the last checkpoint smaller than t, then it will return all the edges
      added in Edge range (tc, t]. */
   std::vector<Edge> get_delta_edge_operations(int, int);

public:
   /* Add an edge from node u to v with weigth w into the graph at the time t. */
   void add_edge(int, int, int, int);

   /* Return the list of edges that compose the MSF at time t. */
   std::vector<Edge> get_msf(int);

   /* Return the weight of the MSF at time t. */
   int get_msf_weight(int);
};