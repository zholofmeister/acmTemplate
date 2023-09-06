const int N = EDIT+100; //点数
vector<int> E[N];
int n,m;
struct BCC {
    int n, bcc, top, tot;
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N];
    int stk[N];
    int cut[N], final_block[N]; //final_block[i]表示割掉i以后图中有几个连通块
    int cntBlock; //一开始有几个连通块

    void dfs(int x, int pre) {
        stk[top++]=x;
        low[x]=dfn[x]=++tot;
        fa[x]=pre;
        int son=0;
        for (int to:G[x]) {
            if (to==pre) continue;
            if (!dfn[to]) {
                ++son;
                dfs(to, x);
                low[x]=min(low[x],low[to]);
                if (x!=pre && low[to]>=dfn[x]) {
                    cut[x]= 1;
                    final_block[x]++;
                }
                if (low[to]>dfn[x]) bridge.emplace_back(make_pair(x, to));
            }
            else if(dfn[to]<dfn[x]) low[x]=min(low[x],dfn[to]);
        }
        if (x==pre) {
            cut[x]=1;
            final_block[x]=son-1;
        }
        if (low[x]==dfn[x]) {
            ++bcc;
            int temp;
            do {
                temp=stk[--top];
                belong[temp]=bcc;
            } while (temp!=x);
        }
    }
    void solve(int _n, vector<int> E[]) {
        n=_n;
        for (int i=1; i<=n; ++i) {
			belong[i]=0;
            G[i]=E[i];
            low[i]=dfn[i]=stk[i]=fa[i] = 0;
            cut[i]=final_block[i]=0;
        }
        bcc=top=tot=cntBlock= 0;
        bridge.clear();
        for (int i=1; i<=n; ++i){
            if (!dfn[i]){
                ++cntBlock;
                dfs(i, i);
            }
        }
        for(int i=1; i<=n; ++i) final_block[i]+=cntBlock;
    }
    void rebuild(vector<int> E[]) {
        for (int i=1; i<=n; ++i) E[i].clear();
        for (int i=1; i<=n; ++i){
            int t=fa[i];
            if (belong[i]!=belong[t]) {
                E[belong[i]].emplace_back(belong[t]);
                E[belong[t]].emplace_back(belong[i]);
            }
        }
    }
}bcc;
int main() {
    cin>>n>>m;
    forn(i, m){
        int u,v;
        cin>>u>>v;
        E[u].eb(v);
        E[v].eb(u);
    }
    bcc.solve(n,E);
    for1(i, n) cout<<bcc.final_block[i]<<' ';
    cout<<'\n';
    return 0;
}
