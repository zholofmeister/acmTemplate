//AcWing 344 floyd求最小环并且按顺序输出最小环中的点
//hdu 1599
const int maxn = 110;
const i64 INF = 0x3f3f3f3f;
i64 G[maxn][maxn], dis[maxn][maxn], road[maxn][maxn], ans;
vi res;

void floyd(int n) {
    int i, j, k;
    for (k = 1; k <= n; ++k) {
        for (i = 1; i < k; ++i) {
            if (G[k][i] == INF) continue;
            for (j = i+1; j < k; ++j) {
                if (G[k][j] == INF) continue;
                if (G[k][i]+G[k][j]+dis[i][j] < ans) {
                    ans = G[k][i]+G[k][j]+dis[i][j];
					/* -----记录路径部分----- */
                    res.clear();
                    for (int temp = i; temp != j; temp = road[temp][j]) res.eb(temp);
                    res.eb(j);
                    res.eb(k);
					/* ------------------ */
                }
            }
        }
        for (i = 1; i <= n; ++i) {
            if (dis[i][k] == INF) continue;
            for (j = 1; j <= n; ++j) {
                if (dis[k][j] == INF) continue;
                if (dis[i][k]+dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k]+dis[k][j];
					/* -----记录路径部分----- */
                    road[i][j] = road[i][k];
					/* ------------------- */
                }
            }
        }
    }
}
void init(int n) {
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) G[i][j] = INF;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) dis[i][j] = INF;
    ans = INF;
}
int n, m;

int main() {
	cin >> n >> m;
    init(n);
    forn(i, m) {
        i64 u, v, val;
        cin >> u >> v >> val;
        G[u][v] = G[v][u] = dis[u][v] = dis[v][u] = min(dis[u][v], val);
        road[u][v] = v; road[v][u] = u;
    }
    floyd(n);
    if (ans == INF) cout << "No solution." << '\n';
    else {
        cout << ans << endl;
        for (int x : res) cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
