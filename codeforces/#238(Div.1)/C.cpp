#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int N, M;
struct EDGE {
    int x, i;
};
vector <EDGE> G[MAXN];
bool use[MAXN];

int f(int cur) {
    int left = -1;
    for (auto &e : G[cur]) {
        if (use[e.i]) continue;
        use[e.i] = 1;
        int nxt = e.x;
        int get = f(nxt);
        if (get != -1) {
            printf("%d %d %d\n", cur, nxt, get);
        } else {
            if (left == -1) {
                left = nxt;
            } else {
                printf("%d %d %d\n", left, cur, nxt);
                left = get;
            }
        }
    }
    return left;
}

int main() {
    scanf("%d%d",&N,&M);
    if (M&1) {
        puts("No solution");
        return 0;
    }
    for (int i = 1; i <= M; i++) {
        int x, y; scanf("%d%d",&x,&y);
        G[x].push_back({y, i});
        G[y].push_back({x, i});
    }
    f(1);
}