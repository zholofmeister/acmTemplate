// cf 1364D
#include <bits/stdc++.h>

using namespace std;

const int maxn = (int)1e5+100;
int n, m, k, h[maxn], fa[maxn];
vector< vector<int> > G(maxn);

void dfs(int x, int par) {
    fa[x] = par;
    for (int to : G[x]) {
        if (to == par) continue;
        if (!h[to]) {
            h[to] = h[x] + 1;
            dfs(to, x);
        } else {
            vector<int> ans = {x}; //找到了环
            int now = x;
            while (now != to) {
                now = fa[now];
                ans.emplace_back(now);
            }
            cout << 2 << '\n';
            cout << int(ans.size()) << '\n';
            for (int x : ans) cout << x << ' ';
            cout << '\n';
            exit(0);
        }
    }
}

int main() {

    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > k || v > k) continue;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    memset(h, 0, sizeof(h));
    for (int i = 1; i <= k; ++i) {
        if (!h[i]) {
            h[i] = 1;
            dfs(i, -1);
        }
    }
    vector<int> team[2];
    for (int i = 1; i <= k; ++i) { //是一棵树，找符合条件1的点
        team[h[i] & 1].emplace_back(i);
    }
    if (int(team[0].size()) < int(team[1].size())) swap(team[0], team[1]);
    cout << 1 << '\n';
    for (int i = 0; i < (k + 1) / 2; ++i) { //注意这里是输出到(k+1)/2为止
	                                        //不能输出全部，比如有6个点但没有边的情况
        cout << team[0][i] << ' ';
    } cout <<'\n';
    return 0;
}