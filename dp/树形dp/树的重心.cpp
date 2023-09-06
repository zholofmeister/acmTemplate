//poj 1655
//树的重心：
//若树上的一个节点满足其所有的子树中最大的子树节点数最少，那么这个点就是这棵树的重心。
const int maxn = 20000+100;
int tc, n, sz[maxn], fa[maxn], res[maxn];
vector<int> G[maxn];

void init(int n) {
    memset(fa, 0, sizeof(fa));
    memset(sz, 0, sizeof(sz));
    for (int i = 1; i <= n; ++i) G[i].clear();
}
void dfs(int x, int par) {
    sz[x] = 1;
    fa[x] = par;
    for (int i = 0; i < int(G[x].size()); ++i) {
        int to = G[x][i];
        if (to == par) continue;
        dfs(to, x);
        sz[x] += sz[to];
    }
}

int main() {
	
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d", &n);
        init(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);

        for (int i = 1; i <= n; ++i) {
            int maxx = n - sz[i];
            for (int j = 0; j < int(G[i].size()); ++j) {
                int to = G[i][j];
                if (to == fa[i]) continue;    //!!
                maxx = max(maxx, sz[to]);
            }
            res[i] = maxx;
        }

        int ans = INT_MAX, node;
        for (int i = 1; i <= n; ++i) {
            if (res[i] < ans) {
                ans = res[i];
                node = i;
            }
        }

        printf("%d %d\n", node, ans);
    }

    return 0;
}
