// 兔子的逆序对 https://ac.nowcoder.com/acm/problem/20861
// 每交换一对数字，就会改变数组逆序对个数的奇偶性
const int maxn = (int)1e5 + 100;
const int cst = (int)1e5;
int n, m, a[maxn], b[maxn], ft[maxn];

void init() {
    memset(ft, 0, sizeof(ft));
}
int query(int x) {
    ll res = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) res += ft[i];
    return res;
}
void update(int x, int val) {
    for (int i = x; i <= cst; i += lowbit(i)) ft[i] += val;
}

int main() {
    init();
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += query(cst) - query(a[i]);
        update(a[i], 1);
    }
    bool odd = (sum & 1);
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        len /= 2;
        if (len & 1) {
            if (odd) odd = false;
            else odd = true;
        }
        cout << (odd ? "dislike" : "like") << '\n';
    }
    return 0;
}

