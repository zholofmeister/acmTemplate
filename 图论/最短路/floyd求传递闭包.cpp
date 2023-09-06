// hdu 1704
const int maxn = 600;
int tc, n, m, G[maxn][maxn];

void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (G[i][k]) {
                for (int j = 1; j <= n; ++j) {
                    if (G[k][j]) {
                        G[i][j] = 1;
                    }
                }
            }
        }
    }
}

int main() {

    cin >> tc;
    while (tc--) {
        ms(G, 0);
        cin >> n >> m;
        forn(i, m) {
            int a, b;
            cin >> a >> b;
            G[a][b] = 1;
        }
        floyd();
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i+1; j <= n; ++j) {
                if (!G[i][j] && !G[j][i]) ++cnt;
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}