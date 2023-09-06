//复杂度O(根号n * q) 
#include <bits/stdc++.h>

using namespace std;

const int maxn = (int)1e5 + 1000;
int t, n, qu, cnt[maxn], res, a[maxn], blo, ans[maxn];
struct node {
	int l, r, id;
}q[maxn];

int read() {
	int ans = 0, f = 1; char c = getchar();
	for (;c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
	for (;c >= '0' && c <= '9'; c = getchar()) ans = ans * 10 + c - '0';
	return ans * f;
}
bool cmp(node a, node b) {
	return (a.l / blo == b.l / blo ? (a.l / blo) & 1 ? a.r < b.r : a.r > b.r : a.l < b.l);
}
void add(int pos) {
	int num = a[pos];
	if (cnt[num] == 0) ++res;
	++cnt[num];
}
void cut(int pos) {
	int num = a[pos];
	--cnt[num];
	if (cnt[num] == 0) --res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	t = read();
	for (int kase = 1; kase <= t; ++kase) {
		memset(cnt, 0, sizeof(cnt));
		n = read();
		qu = read();
		blo = sqrt(n * 1.0 * 2 / 3);
		for (int i = 1; i <= n; ++i) {
			a[i] = read();
		}
		for (int i = 0; i < qu; ++i) {
			q[i].l = read();
			q[i].r = read();
			q[i].id = i;
		}
		sort(q, q + qu, cmp);
		int l = 1, r = 0;
		res = 0;
		for (int i = 0; i < qu; ++i) {
			while (r < q[i].r) add(++r);
			while (l > q[i].l) add(--l);
			while (r > q[i].r) cut(r--);
			while (l < q[i].l) cut(l++);
			ans[q[i].id] = res;
		}
		printf("Case %d:\n", kase);
		for (int i = 0; i < qu; ++i) {
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}