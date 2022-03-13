#include <bits/stdc++.h>
#include "splayTree.hpp"

void SplayTree::checkNullNodePointer(Node *u)
{
    if (u == NULL)
    {
        throw std::invalid_argument("NULL node pointer");
    }
}

Node::Node(int _value)
    : max_subtree_value(_value), value(_value){};

void Node::push_reversed_bit()
{
    if (!is_reversed)
        return;

    is_reversed = false;
    std::swap(l_child, r_child);

    if (l_child)
        l_child->is_reversed ^= true;
    if (r_child)
        r_child->is_reversed ^= true;
}

void Node::recalculate_max_subtree_value()
{
    max_subtree_value = value;

    if (l_child)
        max_subtree_value = std::max(max_subtree_value, l_child->max_subtree_value);
    if (r_child)
        max_subtree_value = std::max(max_subtree_value, r_child->max_subtree_value);
}

void Node::reverse_subtree()
{
    is_reversed ^= true;
}

bool Node::is_root()
{
    // link-cut tree root
    if (parent == NULL)
        return true;

    // splay tree root
    if (parent->l_child != this && parent->r_child != this)
        return true;

    return false;
}

void SplayTree::rotate(Node *u)
{
    checkNullNodePointer(u);

    Node *parent = u->parent;
    Node *grandparent = parent->parent;

    if (!parent->is_root())
    {
        if (grandparent->r_child == parent)
            grandparent->r_child = u;
        else
            grandparent->l_child = u;
    }

    // always keep parent and u updated regarding it reversed status. By doing this, u's children
    // will always be correct while splaying up
    parent->push_reversed_bit();
    u->push_reversed_bit();

    if (parent->l_child == u)
    {
        // right-rotate
        parent->l_child = u->r_child;
        u->r_child = parent;
        if (parent->l_child)
            parent->l_child->parent = parent;
    }
    else
    {
        // left rotate
        parent->r_child = u->l_child;
        u->l_child = parent;
        if (parent->r_child)
            parent->r_child->parent = parent;
    }

    parent->parent = u;
    u->parent = grandparent;

    parent->recalculate_max_subtree_value();
    u->recalculate_max_subtree_value();
}

void SplayTree::splay(Node *u)
{
    checkNullNodePointer(u);

    while (!u->is_root())
    {
        Node *parent = u->parent;
        Node *grandparent = parent->parent;

        if (!parent->is_root())
        {
            // not zig-zag
            if ((grandparent->r_child == parent) == (parent->r_child == u))
                rotate(parent);
            // zig zag
            else
                rotate(u);
        }
        rotate(u);
    }
    u->push_reversed_bit();
}