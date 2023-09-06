//O(3^(n/3))
#include <bits/stdc++.h>
using namespace std;
int n;
const int maxn = 60;
int ma[maxn], g[maxn][maxn], f[maxn][maxn], ans;
int dfs(int cur, int tot) {
    if (!cur) {
        if (tot > ans) return ans = tot, 1;
        return 0;
    }
    for (int i = 0, j, u, nxt; i < cur; ++i) {
        if (cur - i + tot <= ans) return 0;
        u = f[tot][i], nxt = 0;
        if (ma[u] + tot <= ans) return 0;
        for (int j = i + 1; j < cur; ++j) if (g[u][f[tot][j]]) f[tot + 1][nxt++] = f[tot][j];
        if (dfs(nxt, tot + 1)) return 1;
    }
    return 0;
}
int main() {
    while (cin >> n) {
        if (!n) break;
        ans = 0; //初始化
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x;
                cin >> x;
                g[i][j] = g[j][i] = x;
            }
        }
        int k, j;
        for (int i = n - 1; ~i; dfs(k, 1), ma[i--] = ans) {
            for (k = 0, j = i + 1; j < n; ++j) {
                if (g[i][j]) f[1][k++] = j;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
