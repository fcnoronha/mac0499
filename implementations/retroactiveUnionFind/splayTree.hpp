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
    void checkNullNodePointer(Node *);

public:
    /* Performs a series of rotations to bring the node u to the top of the
       Splay Tree. */
    void splay(Node *);
};