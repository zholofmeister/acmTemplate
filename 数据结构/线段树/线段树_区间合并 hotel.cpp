#include <bits/stdc++.h>
#define ms(x, n) memset(x,n,sizeof(x));
#define forn(i, n) for(int i = 0; i < (int)n; i++)
#define For(i, a, b) for(int i = (a); i <= (int)(b); i++)
#define INF 0x3f3f3f3f
#define PI acos(-1.0)
#define mod(x) (x % 1000003)
typedef long long int ll;
typedef unsigned long long int ull;
using namespace std;

#define maxn 51000
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
int n, m, a[maxn], sum[maxn << 2], lsum[maxn << 2], rsum[maxn << 2], cover[maxn << 2], op, o, p;

void build_tree(int l, int r, int rt) {
    sum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
    cover[rt] = -1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build_tree(lson);
    build_tree(rson);
}
void pushdown(int rt, int len) {
    if (cover[rt] != -1) {
        cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];
        lsum[rt << 1] = rsum[rt << 1] = sum[rt << 1] = cover[rt] ? 0 : len - (len >> 1);
        lsum[rt << 1 | 1] = rsum[rt << 1 | 1] = sum[rt << 1 | 1] = cover[rt] ? 0 : (len >> 1);
        cover[rt] = -1;
    }
}
void pushup(int rt, int len) {
    lsum[rt] = lsum[rt << 1];
    rsum[rt] = rsum[rt << 1 | 1];
    if (lsum[rt] == len - (len >> 1)) {
        lsum[rt] += lsum[rt << 1 | 1];
    }
    if (rsum[rt] == (len >> 1)) {
        rsum[rt] += rsum[rt << 1];
    }
    sum[rt] = max(lsum[rt << 1 | 1] + rsum[rt << 1], max(sum[rt << 1], sum[rt << 1 | 1]));
}
void update_tree(int l, int r, int rt, int sig, int L, int R) {
    if (L <= l && r <= R) {
        sum[rt] = lsum[rt] = rsum[rt] = sig ? 0 : r - l + 1;
        cover[rt] = sig;
        return;
    }
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    if (L <= mid) {
        update_tree(lson, sig, L, R);
    }
    if (mid < R) {
        update_tree(rson, sig, L, R);
    }
    pushup(rt, r - l + 1);
}
int query_tree(int l, int r, int rt, int w) {
    if (l == r) return l;
    pushdown(rt, r - l + 1);
    int mid = (l + r) >> 1;
    if (sum[rt << 1] >= w) {
        return query_tree(lson, w);
    } else if (rsum[rt << 1] + lsum[rt << 1 | 1] >= w) {
        return mid - rsum[rt << 1] + 1;
    } else {
        return query_tree(rson, w);
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    build_tree(1, n, 1);
    while (m--) {
        cin >> op;
        if (op == 1) { //check in
            cin >> o;
            if (o > sum[1]) {
                cout << 0 << endl;
            } else {
                int pos = query_tree(1, n, 1, o);
                cout << pos << endl;
                update_tree(1, n, 1, 1, pos, pos + o - 1);
            }
        } else if (op == 2) { //check out
            cin >> o >> p;
            update_tree(1, n, 1, 0, o, o + p - 1);
        }
    }
    return 0;
}
