const int maxn =  1000000 + 1000;
int t, nxt[maxn];
char x[maxn], y[maxn];

//ps:2019ccpc秦皇岛的那题爆longlong了 XD

void kmp_pre(char x[], int m, int nxt[]) {
	int i, j;
	j = nxt[0] = -1;
	i = 0;
	while (i <= m) { //求最小循环节:i <= m   最小循环节:m - nxt[m] 周期性字符串m % (m - nxt[m]) == 0
		while (-1 != j && x[i] != x[j]) j = nxt[j];
		nxt[++i] = ++j;
	}
}
// x是子串,y是主串
int kmp_count(char x[], int m, char y[], int n) {
	int i, j;
	int ans = 0;
	kmp_pre(x, m, nxt);
	i = j = 0;
	while (i < n) {
		while (-1 != j && y[i] != x[j]) j = nxt[j];
		++i;
		++j;
		if (j >= m) {
			++ans;
			j = nxt[j];
		}
	}
	return ans;
}

int main() {

	cin >> t;
	while (t--) {
		cin >> x;
		cin >> y;
		cout << kmp_count(x, strlen(x), y, strlen(y)) << '\n';
	}

	return 0;
}
