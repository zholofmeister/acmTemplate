/* 
    别忘了给un赋值为左端点的个数  在主函数里赋值un=... 
    如果从0~（n-1)开始编号，就改①②处地方
	如果是多组数据别忘了清空G
*/
/**********hdu2389*********/
int tc, t, m, n;
struct coordinate {
    int x, y, speed;
}human[3100], umb[3100];
/**************************/
const int maxn = 6100;
const int INF = 0x3f3f3f3f;
vector< vector<int> > G(maxn);
int un; //un为左端的顶点数，编号1~(un)
int mx[maxn], my[maxn];
int dx[maxn], dy[maxn];
int dis;
bool vis[maxn];
bool SearchP() {
    queue<int> q;
    dis = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    for (int i = 1; i <= un; ++i) { //编号1~(un)  ①
        if(mx[i] == -1) {
            q.push(i);
            dx[i] = 0;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dx[u] > dis) break;
        int sz = int(G[u].size());
        for (int i = 0; i < sz; ++i) {
            int v = G[u][i];
            if (dy[v] == -1) {
                dy[v] = dx[u]+1;
                if (my[v] == -1) dis = dy[v];
                else {
                    dx[my[v]] = dy[v]+1;
                    q.push(my[v]);
                }
            }
        }
    }
    return (dis!=INF);
}
bool dfs(int u) {
    int sz = int(G[u].size());
    for (int i = 0; i < sz; ++i) {
        int v = G[u][i];
        if (!vis[v] && dy[v] == dx[u]+1) {
            vis[v] = true;
            if (my[v] != -1 && dy[v] == dis) continue;
            if (my[v] == -1 || dfs(my[v])) {
                my[v] = u;
                mx[u] = v;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch() {
    int res = 0;
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    while (SearchP()) {
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= un; ++i) { //②
            if (mx[i] == -1 && dfs(i)) res++;
        }
    }
    return res;
}
int main() {
    int kase = 1;
    cin >> tc;
    while (tc--) {
        cin >> t;
        cin >> m;
        un = m;  //!!!给un赋值左端点的个数
        for (int i = 0; i <= m; ++i) G[i].clear();  //多组数据，清空G
        for (int i = 1; i <= m; ++i) cin >> human[i].x >> human[i].y >> human[i].speed;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> umb[i].x >> umb[i].y;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (t * t * human[i].speed * human[i].speed >=
                    (umb[j].x - human[i].x) * (umb[j].x - human[i].x) +
                    (umb[j].y - human[i].y) * (umb[j].y - human[i].y)) {
                        G[i].emplace_back(j);  //加边
                    }
            }
        }
        cout << "Scenario #" << kase++ << ":" << '\n';
        cout << MaxMatch() << '\n';
        cout << '\n';
    }
    return 0;
}