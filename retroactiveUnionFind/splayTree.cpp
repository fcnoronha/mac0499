#include <bits/stdc++.h>
#include "splayTree.hpp"

void SplayTree::check_null_node_pointer(Node *u)
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
    push_reversed_bit();
}

void Node::set_parent(Node *newParent)
{
    parent = newParent;
}

void Node::split_left_subtree()
{
    l_child->parent = NULL;
    l_child = NULL;
}

void Node::join_right_subtree(Node *newChild)
{
    // newChild->parent = this; TODO: investigate
    r_child = newChild;
    recalculate_max_subtree_value();
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
    check_null_node_pointer(u);

    Node *parent = u->parent;
    Node *grandparent = parent->parent;

    // always keep grandparent, parent and u updated regarding it reversed status
    // by doing this, u's children will always be correct while splaying up
    if (!parent->is_root())
        grandparent->push_reversed_bit();
    parent->push_reversed_bit();
    u->push_reversed_bit();

    if (!parent->is_root())
    {
        if (grandparent->r_child == parent)
            grandparent->r_child = u;
        else
            grandparent->l_child = u;
    }

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
    check_null_node_pointer(u);

    while (!u->is_root())
    {
        Node *parent = u->parent;
        Node *grandparent = parent->parent;

        if (!parent->is_root())
        {
            // we push the reversed bit from grandparent to parent in order to
            // guarantee the next conditional will check the correct children
            grandparent->push_reversed_bit();
            parent->push_reversed_bit();

            // zig-zig or zag-zag
            if ((grandparent->r_child == parent) == (parent->r_child == u))
                rotate(parent);
            // zig-zag
            else
                rotate(u);
        }
        rotate(u);
    }
    u->push_reversed_bit();
}