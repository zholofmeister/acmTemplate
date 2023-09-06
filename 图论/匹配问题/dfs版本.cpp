//hdu 2255 点和点之间都有边
//hdu 2426 点和点之间有可能没有边
//n <= m

const int maxn = 510;
const int INF = INT_MAX;
int n, m, link[maxn][maxn], num_a[maxn], num_b[maxn];
int match[maxn], slack[maxn], vis_a[maxn], vis_b[maxn];

bool dfs(int x) {
    vis_a[x] = 1;
    for (int i = 0; i < m; ++i) {
        if (link[x][i] != -1) { //if写外面比里面写continue快？(hdu2426)
        //两点之间不一定有边的情况要加这句
            if (vis_b[i]) continue;
            int diff = num_a[x]+num_b[i]-link[x][i];
            if (!diff) {
                vis_b[i] = 1;
                if (match[i] == -1 || dfs(match[i])) {
                    match[i] = x;
                    return true;
                }
            } else {
                slack[i] = min(slack[i], diff);
            }
        }
    }
    return false;
}
int KM() {
    ms(match, -1); ms(num_b, 0);
    for (int i = 0; i < n; ++i) {
        num_a[i] = INT_MIN;
        for (int j = 0; j < m; ++j) {
            num_a[i] = max(num_a[i], link[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        fill(slack, slack+m, INF);
        int flag = 0;
        for (int j = 0; j < m; ++j) if (link[i][j] != -1) flag = 1;
                       or
        if (num_a[i] != -1) flag = 1;
        //两点之间不一定有边的要加这句
        //如果两点之间都有边的上面那句可以不写，flag=1，这样快一点？(hdu2255)
        while (flag) {
            ms(vis_a, 0); ms(vis_b, 0);
            if (dfs(i)) break;
            int d = INF;
            for (int j = 0; j < m; ++j) if (!vis_b[j]) d = min(d, slack[j]);
            if (d == INF) break;
            for (int j = 0; j < max(n, m); ++j) {
                if (j < n) {
                    if (vis_a[j]) num_a[j] -= d;
                }
                if (j < m) {
                    if (vis_b[j]) num_b[j] += d;
                    else slack[j] -= d;
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i < m; ++i) {
        if (match[i] != -1) {
            res += link[match[i]][i];
        }
    }
    return res;
}

int main() {

    int e;
    while (cin >> n >> m >> e) {
        ms(link, -1);
        forn(i, e) {
            int s, r, v;
            cin >> s >> r >> v;
            if (v >= 0) link[s][r] = v;
        }
        int ans = KM();
        cout << ans << '\n';
    }

    return 0;
}
