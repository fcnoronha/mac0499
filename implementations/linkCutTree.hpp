#pragma once

#include <bits/stdc++.h>
#include "splayTree.hpp"

class LinkCutTree
{
private:
    std::map<std::pair<int, int>, Node *> edges;
    std::map<int, Node *> vertices;
    SplayTree splayTree;

    /* Makes the given node u the root of the Link-Cut Tree. */
    void make_root(Node *);

    /* Used to create a new preferred path going from the root to the given node u. */
    void access(Node *);

    /* Sanitization method to check if there is a node pointer for a given node id. */
    void check_vertex_exist(int);

    /* Sanitization method to check if two nodes are already connected, ie make part
       of the same tree. */
    void check_vertices_already_connected(int, int);

    /* Sanitization method to check if two nodes are not connected, ie in separated
       trees. */
    void check_vertices_are_not_connected(int, int);

public:
    /* Create a node pointer for the given node id if it does not already exist. */
    void create_node(int);

    /* Makes the given u node the root of the Link-Cut Tree. */
    void make_root(int);

    /* Create a new edge between u and v with weight w. */
    void link(int, int, int);

    /* Remove the edge between u and v nodes. */
    void cut(int, int);

    /* Return true if u and v are part of the same tree, false otherwise. */
    bool is_connected(int, int);

    /* Return the maximum weight of an edge in the path from u to v. */
    int maximum_edge(int, int);
};