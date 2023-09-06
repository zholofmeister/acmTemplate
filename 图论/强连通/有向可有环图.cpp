// hdu 3836 求最少加几条边使图变成强连通图
// 时间复杂度 O(V + E)
// 有向可有环图->有向无环图(DAG)    
const int N = EDIT+100;   //点数
int scc, top, tot;
vector<int> G[N];
int low[N], dfn[N], belong[N];
int stk[N], vis[N];
void init(int n) {
    for (int i = 0; i <= n; ++i) {
        G[i].clear();
        low[i] = 0;
        dfn[i] = 0;
        stk[i] = 0;
        vis[i] = 0;
    }
    scc = top = tot = 0;
}
void tarjan(int x) {
    stk[top++] = x;
    low[x] = dfn[x] = ++tot;
    vis[x] = 1;
    for (int to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to]) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (low[x] == dfn[x]) {
        ++scc;
        int temp;
        do {
            temp = stk[--top];
            belong[temp] = scc;
            vis[temp] = 0;
        } while (temp != x);
    }
}

int n, m;
vi in, out;

int main() {
    while (cin >> n >> m) {
        init(n);         //初始化别忘了
        forn(i, m) {
            int u, v;
            cin >> u >> v;
            G[u].eb(v);  //建图
        }
        for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);  //tarjan求强连通
        /*      solving     */
        if (scc == 1) {
            cout << 0 << '\n';
            continue;
        }
        in = vi(scc+1, 0);
        out = vi(scc+1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j : G[i]) {
                if (belong[i] == belong[j]) continue; //缩点，同一个强连通分量之间不用连边
                ++out[belong[i]];
                ++in[belong[j]];
            }
        }
        int in0 = 0, out0 = 0;
        for (int i = 1; i <= scc; ++i) {
            if (!in[i]) ++in0;
            if (!out[i]) ++out0;
        }
        cout << max(in0, out0) << '\n';
        /*      end of solving       */
    }
    return 0;
}