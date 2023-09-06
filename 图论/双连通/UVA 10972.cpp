const int N = 1000+100; //点数
int n,m;
vector<int> E[N];
struct BCC {
    int n, bcc, top, tot;
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N];
    int stk[N];
    int cut[N], add_block[N];
    int deg[N];

    void dfs(int x, int pre) {
        stk[top++] = x;
        low[x] = dfn[x] = ++tot;
        fa[x] = pre;
        int son = 0;
        for (int to : G[x]) {
            if (to == pre) continue;
            if (!dfn[to]) {
                ++son;
                dfs(to, x);
                low[x] = min(low[x], low[to]);
                if (x != pre && low[to] >= dfn[x]) {
                    cut[x] = 1;
                    add_block[x]++;
                }
                if (low[to] > dfn[x]) bridge.push_back(make_pair(x, to));
            }
            else if(dfn[to] < dfn[x]) low[x] = min(low[x], dfn[to]);
        }
        if (x == pre && son > 1) {
            cut[x] = 1;
            add_block[x] = son-1;
        }
        if (low[x] == dfn[x]) {
            ++bcc;
            int temp;
            do {
                temp = stk[--top];
                belong[temp] = bcc;
            } while (temp != x);
        }
    }
    void solve(int _n, vector<int> E[]) {
        n = _n;
        for (int i = 1; i <= n; ++i) {
			belong[i]=0;
            G[i] = E[i];
            low[i] = dfn[i] = stk[i] = fa[i] = 0;
            cut[i] = add_block[i] = 0;
            deg[i]=0;
        }
        bcc = top = tot = 0;
        bridge.clear();
        for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, i);
    }
    void rebuild(vector<int> E[]) {
        for (int i = 1; i <= n; ++i) E[i].clear();
        for (int i = 1; i <= n; ++i) {
            int t = fa[i];
            if (belong[i] != belong[t]) {
                ++deg[belong[i]]; ++deg[belong[t]];
                E[belong[i]].push_back(belong[t]);
                E[belong[t]].push_back(belong[i]);
            }
        }
    }
    int gao(){
        if(bcc==1) return 0;
        int ans=0;
        for(int i=1; i<=bcc; ++i){
            if(deg[i]<2) ans+=2-deg[i];
        }
        return (ans+1)/2;
    }
}bcc;
signed main() {
    while(cin>>n>>m){
        for(int i=0; i<=n; ++i) E[i].clear();
        for(int i=0; i<m; ++i){
            int u,v;
            cin>>u>>v;
            E[u].eb(v);
            E[v].eb(u);
        }
        bcc.solve(n,E);
        bcc.rebuild(E);
        cout<<bcc.gao()<<'\n';
    }
    return 0;
}
