//p2617
#define lowbit(x) (x&(-x))
const int maxn = (int)1e5+100;
int n, m, a[maxn], b[maxn<<1], len;                               //len：离散化后数组的长度
int t[maxn*60], lt[maxn*360], rt[maxn*360], tVal[maxn*360], tot;  //tot：动态开点
int n1, n2, t1[maxn], t2[maxn];
struct qq {
    int l, r, ra, val;
    char op;
}q[maxn];

void update(int &node, int l, int r, int p, int val) {
    if (!node) node = ++tot;
    tVal[node] += val;
    int mid = (l + r) >> 1;
    if (l == r) return;
    if (p <= mid) update(lt[node], l, mid, p, val);
    else update(rt[node], mid + 1, r, p, val);
}
void change(int idx, int val) {
    int p = lower_bound(b + 1, b + 1 + len, a[idx]) - b;
    for (int i = idx; i <= n; i += lowbit(i)) update(t[i], 1, len, p, val);
}
int kTh(int l, int r, int k) {
    if (l == r) return l;
    int sum = 0;
    for (int i = 0; i < n1; ++i) sum -= tVal[lt[t1[i]]];
    for (int i = 0; i < n2; ++i) sum += tVal[lt[t2[i]]];   //lt[t1[i]]!!
    int mid = (l + r) >> 1;
    if (sum >= k) {
        for (int i = 0; i < n1; ++i) t1[i] = lt[t1[i]];
        for (int i = 0; i < n2; ++i) t2[i] = lt[t2[i]];
        return kTh(l, mid, k);
    } else {
        for (int i = 0; i < n1; ++i) t1[i] = rt[t1[i]];
        for (int i = 0; i < n2; ++i) t2[i] = rt[t2[i]];
        return kTh(mid + 1, r, k - sum);
    }
}
int kPre(int l, int r, int k) {   //l, r
    n1 = 0, n2 = 0;
    for (int i = l - 1; i >= 1; i -= lowbit(i)) t1[n1++] = t[i];
    for (int i = r; i >= 1; i -= lowbit(i)) t2[n2++] = t[i];
    return kTh(1, len, k);        //1, len !!
}
void init() {
    memset(t, 0, sizeof(t));
    memset(lt, 0, sizeof(lt));
    memset(rt, 0, sizeof(rt));
    memset(tVal, 0, sizeof(tVal));
    tot = 0;     //这个0蛮有学问的，你后面查询logn棵树的时候，万一你要找的那个地方没有
                  //就变成空节点，对结果没影响, 你赋值成当前仅当-1的时候会有问题
                  //因为0节点并不是空节点，而是你开的第一个点 :>
}

int main() {
    init();    //初始化
    int cnt = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[++cnt] = a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> q[i].op;
        if (q[i].op == 'Q') cin >> q[i].l >> q[i].r >> q[i].ra;
        else {
            cin >> q[i].l >> q[i].val;
            b[++cnt] = q[i].val;
        }
    }
    sort(b + 1, b + 1 + cnt);
    len = unique(b + 1, b + 1 + cnt) - b - 1;
    for (int i = 1; i <= n; ++i) change(i, 1);

    for (int i = 0; i < m; ++i) {
        if (q[i].op == 'C') {
            change(q[i].l, -1);
            a[q[i].l] = q[i].val;
            change(q[i].l, 1);
        } else {
            cout << b[kPre(q[i].l, q[i].r, q[i].ra)] << '\n';
        }
    }
    return 0;
}
