//P 3834
const int maxn = 2*(int)1e5+1000;
int n, m, a[maxn], b[maxn], tVal[maxn*40], t[maxn*40], lt[maxn*40], rt[maxn*40], tot;

int build(int l, int r) {
    int node = ++tot;
    tVal[node] = 0;
    int mid = (l + r) >> 1;
    if (l < r) {
        lt[node] = build(l, mid);
        rt[node] = build(mid + 1, r);
    }
    return node;
}
int update(int l, int r, int par, int p) {
    int node = ++tot;
    lt[node] = lt[par]; rt[node] = rt[par]; tVal[node] = tVal[par] + 1;
    int mid = (l + r) >> 1;
    if (l < r) {
        if (p <= mid) lt[node] = update(l, mid, lt[par], p);   //lt[par]!!
        else rt[node] = update(mid + 1, r, rt[par], p);        //rt[par]!!
    }
    return node;                                               //node!!
}
int query(int n1, int n2, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int sum = tVal[lt[n2]] - tVal[lt[n1]];
    if (sum >= k) return query(lt[n1], lt[n2], l, mid, k);
    else return query(rt[n1], rt[n2], mid + 1, r, k - sum);
}
void init() {
    tot = 0;
}

int main() {
	
    init();                                                      //初始化
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    t[0] = build(1, len);
    for (int i = 1; i <= n; ++i) {
        int p = lower_bound(b + 1, b + 1 + len, a[i]) - b;
        t[i] = update(1, len, t[i - 1], p);
    }
    for (int i = 0; i < m; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        int p = query(t[l - 1], t[r], 1, len, k);
        cout << b[p] << '\n';
    }
    return 0;
}
