https://ac.nowcoder.com/acm/contest/7501/D
牛客小米icpc邀请赛第一场 D
upd:完善了上一个版本求add_block不适用于一开始不连通的图的情况。
//时间复杂度O(V+E)
//建边建双向边
//顶点编号1~n
//add_block[i]表示割掉i后图中的连通块数

const int N = EDIT+100; //点数
vector<int> E[N];
struct BCC {
    int n, bcc, top, tot, sum;
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N];
    int stk[N];
    int cut[N], add_block[N];

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
                if (x != pre && low[to] >= dfn[x]) cut[x] = 1;
                if(low[to]>=dfn[x]) ++add_block[x];
                if (low[to]>dfn[x]) bridge.push_back(make_pair(x, to));
            }
            else if(dfn[to] < dfn[x]) low[x] = min(low[x], dfn[to]);
        }
        if (x == pre && son > 1) cut[x] = 1;
        if (low[x] == dfn[x]) {
            ++bcc;
            int temp;
            do {
                temp = stk[--top];
                belong[temp] = bcc;
            } while (temp != x);
        }
        if(x!=pre) ++add_block[x];
    }
    void solve(int _n, vector<int> E[]) {
        n = _n;
        for (int i = 0; i <= n; ++i) {  //0~n-1
            G[i] = E[i];
            low[i] = dfn[i] = stk[i] = fa[i] = 0;
            cut[i] = add_block[i] = 0;
        }
        bcc = top = tot = sum = 0;
        bridge.clear();
        for (int i = 1; i <= n; ++i){
            if (!dfn[i]){
                dfs(i, i); //0~n-1
                ++sum;
            }
        }
        for (int i=1; i<=n; ++i) add_block[i]+=sum-1;
//        for(int i=1; i<=n; ++i) cout<<add_block[i]<<' ';
//        cout<<'\n';
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