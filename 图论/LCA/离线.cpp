//P3379
//时间复杂度O(V + E)
const int maxn = 500000+1000;
int n, m, s, ans[maxn], vis[maxn], fa[maxn];
vvi g(maxn);
vector< vector< pair<int, int> > > q(maxn);

int find_root(int x) {
    if (x == fa[x]) return x;
    else {
        return (fa[x] = find_root(fa[x]));
    }
}
void uni_root(int a, int b) {
    int aa = find_root(a);
    int bb = find_root(b);
    if (aa != bb) fa[bb] = aa;
}
void LCA(int u, int par) {
    for (int to : g[u]) {
        if (to == par) continue;
        LCA(to, u);
        uni_root(u, to);
    }
    vis[u] = 1;
    for (auto it : q[u]) {
        if (vis[it.fi]) {
            ans[it.se] = find_root(it.fi);
        }
    }
}

int main() {
	
    cin >> n >> m >> s;
    forn(i, n-1) {
        int u, v;
        cin >> u >> v;
        g[u].eb(v);
        g[v].eb(u);
    }
    forn(i, m) {
        int u, v;
        cin >> u >> v;
        q[u].pb({v, i});
        q[v].pb({u, i});
    }
    ms(vis, 0);
    for1(i, n) fa[i] = i;
    LCA(s, 0);
    forn(i, m) cout << ans[i] << '\n';

    return 0;
}
