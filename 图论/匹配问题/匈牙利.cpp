#include <bits/stdc++.h>

using namespace std;

const int maxn = 600;

int nl, nr, m;
int mx[maxn], my[maxn], vis[maxn];
vector<int> G[maxn];

bool aug(int x) {
    for (int to : G[x]) {
        if (vis[to] == -1) {
            vis[to] = 1;
            if (my[to] == -1 || aug(my[to])) {
                my[to] = x;
                mx[x] = to;
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &nl, &nr, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].emplace_back(v);
    }
    int maxMatch = 0;
    memset(my, -1, sizeof(my));
    memset(mx, -1, sizeof(mx));
    for (int i = 1; i <= nl; ++i) {
        memset(vis, -1, sizeof(vis));
        if (aug(i)) ++maxMatch;
    }
    printf("%d\n", maxMatch);
    for (int i = 1; i <= nl; ++i) {
        printf("%d ", mx[i] == -1 ? 0 : mx[i]);
    }puts("");
    return 0;
}
