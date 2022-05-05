#pragma once

#include <bits/stdc++.h>
#include "../linkCutTree.hpp"

struct Edge
{
   int u, v, w;
   int id;

   Edge() {}

   Edge(int _u, int _v, int _w, int _id = 0) : u(_u), v(_v), w(_w), id(_id) {}

   bool operator==(const Edge &e) const
   {
      return (u == e.u && v == e.v && w == e.w && id == e.id);
   }
};

class IncrementalMSF
{
private:
   LinkCutTree linkCutTree;
   std::map<int, Edge> edges_by_id;
   std::set<int> current_msf;
   int current_msf_cost = 0;
   int current_unused_id = 1;

   /* Apply a list of add_edge operations into the structure and return a list
      of pairs <bool, edge> that can be used to perform the rollback of these
      operations, where the boolean value tell wether or not we should perform
      a cut on that edge. Assumes every edge in the list doesn't have an id. */
   std::vector<std::pair<bool, Edge>> apply_add_operations(std::vector<Edge>);

   /* Apply the rollbacks in the structure, undoing the action perfomed by an
      apply_add_operations call. This mechanism is used for the Retroactive MSF
      implementation, and is meant to avoid copying the whole structure. */
   void apply_rollback(std::vector<std::pair<bool, Edge>>);

public:
   /* Create a new node in the graph if it doens't already exist. */
   void create_node(int);

   /* Add an edge from node u to v, with weigth w, into the graph, and possibly
      into the MSF. */
   void add_edge(int, int, int);

   /* Return the list of edges that compose the MSF. */
   std::vector<Edge> get_msf();

   /* Return a list of edges that compose the MSF after a sequence of add_edge
      operations, doing this without copying the structure. */
   std::vector<Edge> get_msf_after_operations(std::vector<Edge>);

   /* Return the cost of the MSF. */
   int get_msf_cost();

   /* Return the cost of the MSF after a sequence of add_edge operations, doing
      this without copying the structure. */
   int get_msf_cost_after_operations(std::vector<Edge>);
};