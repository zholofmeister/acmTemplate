//时间复杂度O(n^3)
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1100;
int n, m, x, y;
vector<int> G[maxn];
namespace Blossom {
    int mate[maxn], n, ret, nxt[maxn], f[maxn], mark[maxn], vis[maxn], t;
    queue<int> q;
    int F(int x) {return x == f[x] ? x : f[x] = F(f[x]);}
    void Merge(int a, int b) {f[F(a)] = F(b);}
    int lca(int x, int y) {
        for (t++;;swap(x, y)) {
            if (~x) {
                if (vis[x = F(x)] == t) return x;
                vis[x] = t;
                x = (mate[x] != -1 ? nxt[mate[x]] : -1);
            }
        }
    }
    void group(int a, int p) {
        for (int b, c; a != p; Merge(a, b), Merge(b, c), a = c) {
            b = mate[a], c = nxt[b];
            if (F(c) != p) nxt[c] = b;
            if (mark[b] == 2) mark[b] = 1, q.push(b);
            if (mark[c] == 2) mark[c] = 1, q.push(c);
        }
    }
    void aug(int s, const vector<int> G[]) {
        for (int i = 0; i < n; ++i) {
            nxt[i] = vis[i] = -1;
            f[i] = i;
            mark[i] = 0;
        }
        while (!q.empty()) q.pop();
        q.push(s);
        mark[s] = 1;
        while (mate[s] == -1 && !q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0, y; i < int(G[x].size()); ++i) {
                if ((y = G[x][i]) != mate[x] && F(x) != F(y) && mark[y] != 2) {
                    if (mark[y] == 1) {
                        int p = lca(x, y);
                        if (F(x) != p) nxt[x] = y;
                        if (F(y) != p) nxt[y] = x;
                        group(x, p); group(y, p);
                    } else if (mate[y] == -1) {
                        nxt[y] = x;
                        for (int j = y, k, l; ~j; j = l) {
                            k = nxt[j];
                            l = mate[k];
                            mate[j] = k;
                            mate[k] = j;
                        }
                        break;
                    } else {
                        nxt[y] = x;
                        q.push(mate[y]);
                        mark[mate[y]] = 1;
                        mark[y] = 2;
                    }
                }
            }
        }
    }
    int solve(int _n, vector<int> G[]) {
        n = _n;
        memset(mate, -1, sizeof(mate));
        for (int i = t = 0; i < n; ++i) if (mate[i] == -1) aug(i, G);
        for (int i = ret = 0; i < n; ++i) ret += (mate[i] > i);
        printf("%d\n", ret);
        for (int i = 0; i < n; ++i) printf("%d ", mate[i] + 1);
        return ret;
    }
}

int main() {
	//for (int i = 0; i <= maxV; ++i)  G[i].clear();  //多组数据的话别忘了从 0~最大点数 清空一下vector
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        --x; --y;             //顶点0~(n-1)编号
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    Blossom::solve(n, G);  
    return 0;
}
