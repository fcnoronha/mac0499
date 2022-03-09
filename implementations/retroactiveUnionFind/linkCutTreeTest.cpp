#include <bits/stdc++.h>
#include "linkCutTree.hpp"
using namespace std;

#define dbg(x) cout << #x << " = " << x << endl

int main()
{
    cout << "--- teste 1 ---" << endl;
    LinkCutTree lct_1;
    for (int i = 1; i <= 7; i++)
        lct_1.create_node(i);

    lct_1.link(1, 2, 20);
    lct_1.link(2, 3, 25);
    lct_1.link(4, 5, 40);

    dbg(lct_1.is_connected(1, 2)); // true
    dbg(lct_1.is_connected(2, 3)); // true
    dbg(lct_1.is_connected(4, 5)); // true
    dbg(lct_1.is_connected(2, 5)); // false
    dbg(lct_1.is_connected(6, 7)); // false

    cout << "new root" << endl;
    lct_1.make_root(2);
    dbg(lct_1.is_connected(1, 2)); // true
    dbg(lct_1.is_connected(2, 3)); // true
    dbg(lct_1.maximum_edge(1, 2)); // 20
    dbg(lct_1.maximum_edge(1, 3)); // 25
    dbg(lct_1.maximum_edge(4, 5)); // 40

    cout << "new tree" << endl;
    lct_1.cut(2, 3);
    lct_1.link(1, 4, 10);
    lct_1.link(3, 7, 50);
    dbg(lct_1.is_connected(2, 5)); // true
    dbg(lct_1.is_connected(2, 3)); // false
    dbg(lct_1.is_connected(3, 7)); // true
    dbg(lct_1.maximum_edge(2, 5)); // 40
    dbg(lct_1.maximum_edge(3, 7)); // 50

    cout << "--- teste 2 ---" << endl;
    LinkCutTree lct_2;
    for (int i = 1; i <= 9; i++)
        lct_2.create_node(i);

    lct_2.link(1, 2, 7);
    lct_2.link(1, 3, 6);
    lct_2.link(2, 4, 3);
    lct_2.link(2, 5, 1);
    lct_2.link(3, 6, 3);
    lct_2.link(3, 7, 5);
    lct_2.link(5, 8, 2);
    lct_2.link(7, 9, 4);

    dbg(lct_2.is_connected(1, 4)); // true
    dbg(lct_2.is_connected(1, 9)); // true
    dbg(lct_2.is_connected(9, 8)); // true
    dbg(lct_2.maximum_edge(1, 2)); // 7
    dbg(lct_2.maximum_edge(1, 4)); // 7
    dbg(lct_2.maximum_edge(4, 3)); // 7
    dbg(lct_2.maximum_edge(9, 6)); // 5
    dbg(lct_2.maximum_edge(9, 8)); // 7

    cout << "new tree" << endl;
    lct_2.cut(1, 2);
    lct_2.cut(3, 7);
    lct_2.link(1, 4, 0);
    lct_2.link(5, 7, 10);
    dbg(lct_2.is_connected(9, 6)); // true
    dbg(lct_2.maximum_edge(6, 8)); // 6
    dbg(lct_2.maximum_edge(9, 8)); // 10
    dbg(lct_2.maximum_edge(9, 7)); // 4
    dbg(lct_2.maximum_edge(4, 9)); // 10
    dbg(lct_2.maximum_edge(4, 5)); // 3
}
