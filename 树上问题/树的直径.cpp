int n;
vvi g;
vi p;

pii dfs(int v, int par = -1, int dist = 0) {
    p[v] = par;
    pii res = mp(dist, v);
    for (auto to : g[v]) {
        if (to == par) continue;
        res = max(res, dfs(to, v, dist + 1));
    }
    return res;
}

int main() {

	cin >> n;
	g = vvi(n);
	p = vi(n);
	forn(i, n - 1) {
        int v1, v2;
        cin >> v1 >> v2;
        --v1; --v2;
        g[v1].eb(v2);
        g[v2].eb(v1);
	}
	pii da = dfs(0);
	pii db = dfs(da.se);
	vi diam;
	int v = db.se;
	while (v != -1) {
        diam.eb(v);
        v = p[v];
	}
	if (int(diam.size()) == n) { //直径就是整个图，也就是整个图就是一条链
        cout << n - 1 << '\n';
        cout << diam[0] + 1 << " " << diam[1] + 1 << " " << diam.back() + 1 << '\n';
        return 0;
	}
	queue<int> q;
	vi d(n, -1);
	for (int u : diam) {
        d[u] = 0;
        q.push(u);
	}
	while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto to : g[v]) {
            if (d[to] == -1) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
	}
	pii mx = mp(d[0], 0);
	forn(i, n) {
        mx = max(mx, mp(d[i], i));
	}
	cout << int(diam.size()) - 1 + mx.fi << '\n';
	cout << diam[0] + 1 << " " << diam.back() + 1 << " " << mx.se + 1 << '\n';
	return 0;
}

