#include <bits/stdc++.h>
#include "splayTree.hpp"
#include "linkCutTree.hpp"

void LinkCutTree::check_vertex_exist(int u)
{
    if (!vertices[u])
    {
        throw std::invalid_argument("vertex does not exist");
    }
}

void LinkCutTree::check_vertices_already_connected(int u, int v)
{
    if (is_connected(u, v))
    {
        throw std::invalid_argument("vertices u and v are already connected");
    }
}

void LinkCutTree::check_vertices_are_not_connected(int u, int v)
{
    if (!is_connected(u, v))
    {
        throw std::invalid_argument("vertices u and v are not connected");
    }
}

void LinkCutTree::make_root(Node *u)
{
    access(u);
    u->reverse_subtree();
}

void LinkCutTree::access(Node *u)
{
    Node *last = NULL;
    Node *p = u;

    // transform all parent pointers from u to the root into part of the same preferred path
    while (p != NULL)
    {
        splayTree.splay(p); // makes p the root of its preferred path auxiliary tree
        p->r_child = last;  // separates the preferred path of p, appending the last auxiliary
                            // tree processed as the deepest part of this path
        p->recalculate_max_subtree_value();
        last = p;
        p = p->parent; // moves up to the parent preferred path auxiliary tree
    }
    splayTree.splay(u);
}

void LinkCutTree::create_node(int u)
{
    if (!vertices[u])
        vertices[u] = new Node();
}

void LinkCutTree::make_root(int u)
{
    check_vertex_exist(u);

    Node *u_node = vertices[u];

    access(u_node);
    u_node->reverse_subtree();
}

void LinkCutTree::link(int u, int v, int w = 0)
{
    check_vertex_exist(u);
    check_vertex_exist(v);
    check_vertices_already_connected(u, v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];

    Node *uv_edge = new Node(w);
    edges[{u, v}] = edges[{v, u}] = uv_edge;

    // linking (v) <- (uv_edge)
    make_root(uv_edge);
    uv_edge->parent = v_node;

    // linking (uv_edge) <- (u)
    make_root(u_node);
    u_node->parent = uv_edge;
}

void LinkCutTree::cut(int u, int v)
{
    check_vertex_exist(u);
    check_vertex_exist(v);
    check_vertices_are_not_connected(u, v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];
    Node *uv_edge = edges[{u, v}];

    // cutting (v) <- (uv_edge)
    make_root(uv_edge);
    access(v_node);
    v_node->l_child->parent = NULL;
    v_node->l_child = NULL;

    // cutting (uv_edge) <- (u)
    make_root(u_node);
    access(uv_edge);
    uv_edge->l_child->parent = NULL;
    uv_edge->l_child = NULL;

    edges.erase(edges.find({u, v}));
    edges.erase(edges.find({v, u}));
}

bool LinkCutTree::is_connected(int u, int v)
{
    check_vertex_exist(u);
    check_vertex_exist(v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];

    access(u_node);
    access(v_node);
    // if they are in the same tree, u is either in v's auxiliary tree or has a parent pointer to it
    return (u_node->parent != NULL);
}

int LinkCutTree::maximum_edge(int u, int v)
{
    check_vertex_exist(u);
    check_vertex_exist(v);
    check_vertices_are_not_connected(u, v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];

    make_root(v_node);
    access(u_node); // now creates a u-v preferred path
    return u_node->max_subtree_value;
}
