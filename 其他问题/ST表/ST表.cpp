//初始化O(logn) 询问O(1)
//hdu 5443
//询问最小，把两个max改成min就行
const int maxn = 2000;
int dp[maxn][35], LOG[maxn]; //2^30 == 1e9
int tc, n, m, a[maxn];

void initRMQ() {
    LOG[0] = -1;
    for (int i = 1; i <= n; ++i) {
        LOG[i] = ((i & (i-1)) == 0) ? LOG[i-1] + 1 : LOG[i-1];
        dp[i][0] = a[i];
    }
    for (int j = 1; j <= LOG[n]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            dp[i][j] = max(dp[i][j-1], dp[i + (1<<(j-1))][j-1]);
        }
    }
}
int rmqQuery(int x, int y) {
    int k = LOG[y-x+1];
    return max(dp[x][k], dp[y-(1<<k)+1][k]);
}