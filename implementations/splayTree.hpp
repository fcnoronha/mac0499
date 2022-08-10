/******************************************************************************
 * This work is part of the Bachelor’s dissertation of Felipe C. Noronha, at  *
 * the Department of Computer Science of the University of São Paulo, Brazil. *
 ******************************************************************************/

#pragma once

#include <bits/stdc++.h>

class Node
{
public:
   Node *parent = NULL;
   Node *l_child = NULL;
   Node *r_child = NULL;
   bool is_reversed = false;
   int max_subtree_value;
   int max_subtree_value_id;
   int value;
   int id;

   /* Constructor with default value as neutral element in max() and 0 id. */
   Node(int = INT_MIN, int = 0);

   /* Swap left and right childs of current node and propagate reversed bit
      to childs, reverting the order of the substree. */
   void push_reversed_bit();

   /* Recalculates the maximum value stored in the current node subtree. */
   void recalculate_max_subtree_value();

   /* Check if the node is either a Splay Tree root or a Link-Cut tree root. */
   bool is_root();
};

/* In our implementation, the Splay Tree is used to maintain the preferred paths
   of the Link-Cut Tree. For this, each edge of the LCT is also a node in here
   and the depth of the nodes in the represented tree are used as implicit keys. */
class SplayTree
{
private:
   /* Implement the rotations used by the splay method. It takes care of
      pushing the reversed bits and also updating the maximum subtree values. */
   void rotate(Node *);

   /* Sanitization method to check if a given node poiter is null. */
   void check_null_node_pointer(Node *);

public:
   /* Performs a series of rotations (splays) to bring the node u to the top of
      the Splay Tree. The node will end up with its maximum subtree value
      recalculated and its reversed bit zeroed out (propagated to children).
      After this, u will be its path identifier. */
   void splay(Node *);

   /* Separates u's preferred path in 2, breaking the connection between u and
      its parent in the represented tree. In other words, separates u from all
      the nodes shallower than it in the preferred path. Erases the respectives
      parent and child pointers. */
   void split(Node *);

   /* Given u and v, ids of their respective paths and with v deeper than u,
      separates u from the deepest part of its path and concatenates v's path
      instead. Used when creating new preferred paths, will let the separated
      path with a parent pointer to u. */
   void join(Node *, Node *);

   /* Changes the orientation of u's preferred path by flipping the is_reversed
      flag of u. Assumes u is path identifier. */
   void reverse_path(Node *);

   /* Return the vertex immediately above the end of u's preferred path in the
      represented tree, the parent node of the Splay Tree root. */
   Node *get_parent_path_node(Node *);

   /* Return the shallowest vertex of u's preferred path, the one in the end of
      it, by accessing the smallest value in the Splay Tree. */
   Node *get_path_end_node(Node *);

   /* Return the maximum value stored in a vertex of u's preferred path.
      Assumes u is path identifier. */
   int get_maximum_path_value(Node *);

   /* Return the id of the vertex with maximum value in u's preferred path.
      Assumes u is path identifier. */
   int get_maximum_path_value_id(Node *);
};