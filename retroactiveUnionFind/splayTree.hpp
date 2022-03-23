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
   int value;

   /* Constructor with default value as neutral element in max(). */
   Node(int = INT_MIN);

   /* Swap left and right childs of current node and propagate reversed bit
      to childs, reverting the order of the substree. */
   void push_reversed_bit();

   /* Recalculates the maximum value stored in the current node subtree. */
   void recalculate_max_subtree_value();

   /* Flip the is_reversed flag of the current node. */
   void reverse_subtree();

   /* Set the parent pointer of the current node. */
   void set_parent(Node *newParent);

   /* Separates the current node from its left subtree by erasing the
      respectives parent and child pointers. In other words, separates it
      from all the nodes smaller than it.*/
   void split_left_subtree();

   /* Sets a new right subtree to the current node. Used when creating new
      preferred paths and will let the preview right child with a parent
      pointer to the current node. */
   void join_right_subtree(Node *newChild);

   /* Check if the node is either a Splay Tree root or a Link-Cut tree root. */
   bool is_root();
};

class SplayTree
{
private:
   /* Implement the rotations used by the splay method. It takes care of
      pushing the reversed bits and also updating the maximum subtree values. */
   void rotate(Node *);

   /* Sanitization method to check if a given node poiter is null. */
   void check_null_node_pointer(Node *);

public:
   /* Performs a series of rotations to bring the node u to the top of the
      Splay Tree. The node will end up with its maximum subtree value
      recalculated and its reversed bit zeroed out (propagated to children) */
   void splay(Node *);
};