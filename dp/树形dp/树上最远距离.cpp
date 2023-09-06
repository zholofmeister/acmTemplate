//hdu 2196
const int maxn = (int)1e4+100;
int n, f[maxn], g[maxn], fa[maxn];
vector< pair<int, int> > G[maxn];

void init(int n) {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(fa, 0, sizeof(fa));
    for (int i = 1; i <= n; ++i) G[i].clear();  //!!
}
void dfs(int x, int par) {
    fa[x] = par;
    for (pair<int, int> pii : G[x]) {
        int to = pii.first;
        if (to == par) continue;
        dfs(to, x);
        f[x] = max(f[x], f[to] + pii.second);
    }
}
void dfs2(int x, int par) {
    int temp = 0;
    g[x] = g[par];
    for (pair<int, int> pii : G[par]) {
        int to = pii.first;
        if (to == fa[par]) continue;
        if (to == x) temp = pii.second;
        else {
            g[x] = max(g[x], f[to] + pii.second);
        }
    }
    g[x] += temp;
    for (pair<int, int> pii : G[x]) {
        int to = pii.first;
        if (to == par) continue;
        dfs2(to, x);
    }
}

int main() {
    while (cin >> n) {
        init(n);
        for (int i = 2; i <= n; ++i) {
            int u, val;
            cin >> u >> val;
            G[i].emplace_back(make_pair(u, val));
            G[u].emplace_back(make_pair(i, val));
        }
        dfs(1, 0);
        dfs2(1, 0);
        for (int i = 1; i <= n; ++i) {
            cout << max(f[i], g[i]) << '\n';
        }
    }
    return 0;
}
