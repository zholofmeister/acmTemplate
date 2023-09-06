bool toposort(vvi &g, vi &inDeg) {
	queue<int> q;
	while (!q.empty()) q.pop();
	forn(i, n) {
		if (inDeg[i] == 0) {
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		++cnt;
		for (auto it : g[now]) {
			--inDeg[it];
			if (inDeg[it] == 0) q.push(it);
		}
	}
	if (cnt == n) return true;
	return false;
} 

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		vvi g(n);
		vi inDeg(n, 0);
		forn(i, m) {
			int e1, e2;
			cin >> e1 >> e2;
			--e1; --e2;
			g[e1].eb(e2);
			++inDeg[e2];
		}
		if (toposort(g, inDeg)) cout << "Correct" << '\n';
		else cout << "Wrong" << '\n';
	}
	return 0;
}