#include <bits/stdc++.h>
#include "retroactiveUnionFind.hpp"
using namespace std;

#define dbg(x) cout << #x << " = " << x << endl

int main()
{
    RetroactiveUnionFind ruf;

    ruf.create_union(1, 2, 4);
    ruf.create_union(2, 3, 5);

    dbg(ruf.same_set(1, 3, 6)); // true
    dbg(ruf.same_set(1, 3, 4)); // false

    ruf.delete_union(5);
    dbg(ruf.same_set(1, 3, 6)); // false
}
