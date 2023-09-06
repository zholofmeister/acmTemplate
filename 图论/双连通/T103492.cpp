题意：
给你一个n个点，m条边的无向图，让你输出共pbccCnt行，pbccCnt为点双连通分量数量。对于第i行，输出第i个点双连通分量的每个点。（顺序不分前后）
n<=5e4, m<=3e5
思路：
无，直接看代码。

const int N = 5*(int)1e4+100; //点数
int n,m;
vector<int> E[N];
struct BCC {
    int n, bcc, pbcc, top, ptop, tot;
    vector<int> G[N];
    vector<int> ans[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N], pbelong[N];
    int stk[N], pstk[N];
    int cut[N], add_block[N];

    void dfs(int x, int pre) {
        stk[top++] = x;
        pstk[ptop++] = x;
        low[x] = dfn[x] = ++tot;
        fa[x] = pre;
        int son = 0;
        if(SZ(E[x])==0){
            ans[++pbcc].eb(x);
            //pbelong[x]=pbcc;
            return;
        }
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
                if(low[to]>=dfn[x]){
                    ++pbcc;
                    int temp;
                    do{
                        temp=pstk[--ptop];
                        ans[pbcc].eb(temp);
                //        pbelong[temp]=pbcc;
                    } while(temp!=to);
                    ans[pbcc].eb(x);
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
            ans[i].clear();;
			belong[i]=pbelong[i]=0;
            G[i] = E[i];
            low[i] = dfn[i] = stk[i] = pstk[i] = fa[i] = 0;
            cut[i] = add_block[i] = 0;
        }
        bcc = pbcc = top = ptop = tot = 0;
        bridge.clear();
        for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, i);
        for1(i, pbcc){
            for(int x:ans[i]) cout<<x<<' ';
            cout<<'\n';
        }
    }
    void rebuild(vector<int> E[]) {
        for (int i = 1; i <= n; ++i) E[i].clear();
        for (int i = 1; i <= n; ++i) {
            int t = fa[i];
            if (belong[i] != belong[t]) {
                E[belong[i]].push_back(belong[t]);
                E[belong[t]].push_back(belong[i]);
            }
        }
    }
}bcc;
int main() {
    cin>>n>>m;
    forn(i, m){
        int a,b;
        cin>>a>>b;
        E[a].eb(b);
        E[b].eb(a);
    }
    //for(int i=1; i<=n; ++i) reverse(all(E[i])); 傻逼题没加spj
    bcc.solve(n,E);
    return 0;
}
