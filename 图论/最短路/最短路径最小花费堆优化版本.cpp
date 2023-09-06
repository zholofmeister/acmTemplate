//hdu 3790
#define i64 long long

const int maxn = 1000 + 100; //点数
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
struct node {
    int id;
	i64 w, p;
    node(){}
    node(int a, i64 b, i64 c) : id(a), w(b), p(c) {}
    friend bool operator < (node a, node b) {
        if (a.w == b.w) return a.p > b.p;
        return a.w > b.w;
    }
};
vector<node> G[maxn];
bool vis[maxn];
i64 dis[maxn], cost[maxn];
int n, m, s, t;

void dij(int s, int n) {
    priority_queue<node> q;
	while (!q.empty()) q.pop();
    node cur;
    for (int i = 1; i <= n; ++i) {
		dis[i] = INF;
		cost[i] = INF;
		vis[i] = 0;
	}
    dis[s] = cost[s] = 0;
    q.push(node(s, dis[s], 0));
    while (!q.empty()) {
        cur = q.top();
        q.pop();
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (node to : G[cur.id]) {
            if (!vis[to.id] && (dis[to.id] > dis[cur.id] + to.w
            || (dis[to.id] == dis[cur.id] + to.w && cost[to.id] > cost[cur.id] + cur.p))) {   //dis[to.id] > to.w 就变成了堆优化prim
                dis[to.id] = dis[cur.id] + to.w;
                cost[to.id] = cost[cur.id] + to.p;
                q.push(node(to.id, dis[to.id], cost[to.id]));
            }
        }
    }
}
void init(int n) {
    for (int i = 0; i <= n; ++i) G[i].clear();
}

int main() {

    while (cin >> n >> m) {
        if (!n && !m) break;
        init(n);
        int a, b, c, d;
        for (int i = 0; i < m; ++i) {
            cin >> a >> b >> c >> d;
            G[a].emplace_back(node(b, c, d));
            G[b].emplace_back(node(a, c, d));
        }
        cin >> s >> t;
        dij(s, n);
        cout << dis[t] << ' ' << cost[t] << '\n';
    }

    return 0;
}