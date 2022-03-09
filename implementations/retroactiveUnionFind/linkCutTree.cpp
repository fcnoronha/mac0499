#include <bits/stdc++.h>
#include "splayTree.hpp"
#include "linkCutTree.hpp"

void LinkCutTree::checkVertexExist(int u)
{
    if (!vertices[u])
    {
        throw std::invalid_argument("vertex does not exist");
    }
}

void LinkCutTree::checkVerticesAlreadyConnected(int u, int v)
{
    if (is_connected(u, v))
    {
        throw std::invalid_argument("vertices u and v are already connected");
    }
}

void LinkCutTree::checkVerticesAreNotConnected(int u, int v)
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

    while (p != NULL)
    {
        splayTree.splay(p);
        p->r_child = last;
        last = p;
        last->recalculate_max_subtree_value();
        p = p->parent;
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
    checkVertexExist(u);

    Node *u_node = vertices[u];

    access(u_node);
    u_node->reverse_subtree();
}

void LinkCutTree::link(int u, int v, int w = 0)
{
    checkVertexExist(u);
    checkVertexExist(v);
    checkVerticesAlreadyConnected(u, v);

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
    checkVertexExist(u);
    checkVertexExist(v);
    checkVerticesAreNotConnected(u, v);

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
    checkVertexExist(u);
    checkVertexExist(v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];

    access(u_node);
    access(v_node);
    return (u_node->parent != NULL);
}

int LinkCutTree::maximum_edge(int u, int v)
{
    checkVertexExist(u);
    checkVertexExist(v);
    checkVerticesAreNotConnected(u, v);

    Node *v_node = vertices[v];
    Node *u_node = vertices[u];

    make_root(v_node);
    access(u_node);
    return u_node->max_subtree_value;
}
