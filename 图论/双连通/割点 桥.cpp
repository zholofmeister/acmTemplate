//时间复杂度O(V+E)
//add_block[i]:割掉i以后会多产生的连通块数，即割掉后图中的连通块数为add_block[i]+1
const int N = edit+100; //点数
vector<int> E[N];
struct BCC {
    int n, bcc, top, tot;
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
                E[belong[i]].push_back(belong[t]);
                E[belong[t]].push_back(belong[i]);
            }
        }
    }
}bcc;
int n, m;

int main() {
    cin >> n >> m;
	//多组数据别忘情况E[i]
	for(int i=0; i<=n; ++i) E[i].clear(); //初始化
    forn(i, m) {
        int x, y;
        cin >> x >> y;  //顶点编号从1~n
        E[x].eb(y);
        E[y].eb(x);
    }
    bcc.solve(n, E);
    vi res;
    for1(i, n) if (bcc.cut[i]) res.eb(i);
    cout << SZ(res) << '\n';
    for (int x : res) cout << x << ' ';
    cout << '\n';
    return 0;
}
