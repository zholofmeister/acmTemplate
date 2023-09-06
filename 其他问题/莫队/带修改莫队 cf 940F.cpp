#include <bits/stdc++.h>

#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
 
using namespace std;
 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef pair<i64, i64> pi64;
typedef double ld;
 
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

const int maxn = (int)2 * 1e6 + 1000;
int a[maxn], b[maxn], c[maxn], n, m, qdx = 0, mdx = 0, bsz, res = 0;
int ans[maxn], times[maxn], cnt[maxn], rl[maxn], rr[maxn], d[maxn];
struct query {
	int l, r, md, id;
	void set(int _l, int _r, int _md, int _id) {
		l = _l, r = _r, md = _md, id = _id;
	}
	bool operator < (const query &b) const {
		if (l / bsz != b.l / bsz) return l < b.l;
		if (r / bsz != b.r / bsz) return r < b.r;
		return id < b.id;
	}
}que[maxn];
struct modify {
	int wz, x, y;
	void set(int _wz, int _x, int _y) {
		wz = _wz, x = _x, y = _y;
	}
}mod[maxn];

int read() {
	int ans = 0, f = 1; char c = getchar();
	for(;c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
	for(;c >= '0' && c <= '9'; c = getchar()) ans = ans * 10 + c - '0';
	return ans * f;
}
template <class T>
void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x >= 10) write(x / 10);
	putchar('0' + x % 10);
}
void add(int x) {
	--cnt[times[x]];
	++times[x];
	++cnt[times[x]];
}
void cut(int x) {
	--cnt[times[x]];
	--times[x];
	++cnt[times[x]];
}
void upd(int l, int r, int t) {
	if (l <= mod[t].wz && mod[t].wz <= r) {
		cut(mod[t].x), add(mod[t].y);
	}
	d[mod[t].wz] = mod[t].y;
}
void del(int l, int r, int t) {
	if (l <= mod[t].wz && mod[t].wz <= r) {
		add(mod[t].x), cut(mod[t].y);
	}
	d[mod[t].wz] = mod[t].x;
}
int find_ans() {
	int now = 1;
	while (cnt[now] != 0) {
		++now;
	}
	return now;
}
void work() {
	bsz = (int)pow(n, 2.0 / 3);
	sort(que + 1, que + 1 + qdx);
	int l = 1, r = 0, t = 0;
	res = 0;
	for1(i, qdx) {
		while (t < que[i].md) ++t, upd(l, r, t);
		while (t > que[i].md) del(l, r, t), --t;
		while (l < que[i].l) cut(d[l]), ++l;
		while (l > que[i].l) --l, add(d[l]);
		while (r < que[i].r) ++r, add(d[r]);
		while (r > que[i].r) cut(d[r]), --r;
		ans[que[i].id] = find_ans();
	}
}
 
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("in", "r", stdin);
#endif
	
	memset(times, 0, sizeof(times));
	memset(cnt, 0, sizeof(cnt));
	n = read(); m = read();
	for1(i, n) {
		a[i] = read();
		b[i] = a[i];
	}
	int tot = n;
	forn(i, m) {
		int op, l, r;
		op = read(); l = read(); r = read();
		if (op == 1) 
			++qdx, que[qdx].set(l, r, mdx, qdx);
		if (op == 2) {
			++mdx;
			rl[mdx] = l;
			++tot;
			rr[mdx] = a[tot] = b[tot] = r;
		}
	}
	sort(b + 1, b + 1 + tot);
	int dig = unique(b + 1, b + 1 + tot) - b - 1;
	for1(i, n) {
		d[i] = lower_bound(b + 1, b + 1 + dig, a[i]) - b;
		c[i] = d[i];
	}
	for1(i, mdx) {
		int tmp = lower_bound(b + 1, b + 1 + dig, rr[i]) - b;
		mod[i].set(rl[i], 0, tmp);
	}
	for1(i, mdx) {
		mod[i].x = c[mod[i].wz];
		c[mod[i].wz] = mod[i].y;
	}
	work();
	for1(i, qdx) {
		write(ans[i]);
		puts("");
	}
	

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
	return 0;
}