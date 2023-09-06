//时间复杂度 O(v^2*E)
const int maxn = "EDIT";   //点数
const int INF = 0x3f3f3f3f;
struct Edge{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f)
        : from(u), to(v), cap(c), flow(f) {}
};
struct ISAP {
    int n, m, s, t;       //节点数，边数（包括反向弧），原点编号和汇点编号
    vector<Edge> edges;   //边表。edges[e]和edges[e^1]互为反向弧
    vector<int> G[maxn];  //邻接表，G[i][j]表示节点i的第j条边在e数组中的序号
    bool vis[maxn];       //BFS使用
    int d[maxn];          //起点到i的距离
    int cur[maxn];        //当前弧下标
    int p[maxn];          //可增广路上的一条弧
    int num[maxn];        //距离标号计数
    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i) {
            d[i] = INF;
            num[i] = vis[i] = cur[i] = 0;
            G[i].clear();
        }
        edges.clear();
    }
    void addEdge(int from, int to, int cap) {
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        int m = int(edges.size());
        G[from].emplace_back(m - 2);
        G[to].emplace_back(m - 1);
    }
    int Augument() {
        int x = t, a = INF;
        while (x != s) {
            Edge &e = edges[p[x]];
            a = min(a, e.cap - e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while (x != s) {
            edges[p[x]].flow += a;
            edges[p[x] ^ 1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }
    void BFS() {
        queue<int> q;
        while (!q.empty()) q.pop();
        q.push(t);
        d[t] = 0;
        vis[t] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            int len = int(G[x].size());
            for (int i = 0; i < len; ++i) {
                Edge &e = edges[G[x][i] ^ 1];
                if (!vis[e.from] && e.cap > e.flow) {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    q.push(e.from);
                }
            }
        }
    }
    int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        if (d[s] >= n) return 0;
        for (int i = 1; i <= n; ++i)
            if (d[i] < INF) num[d[i]]++;
        int x = s;
        while (d[s] < n) {
            if (x == t) {
                flow += Augument();
                x = s;
            }
            int ok = 0;
            for (int i = cur[x]; i < int(G[x].size()); ++i) {
                Edge &e = edges[G[x][i]];
                if (e.cap > e.flow && d[x] == d[e.to] + 1) {
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i;
                    x = e.to;
                    break;
                }
            }
            if (!ok) { //Retreat
                int m = n - 1;
                for (int i = 0; i < int(G[x].size()); ++i) {
                    Edge &e = edges[G[x][i]];
                    if (e.cap > e.flow) m = min(m, d[e.to]);
                }
                if (--num[d[x]] == 0) break; //gap优化
                num[d[x] = m + 1]++;
                cur[x] = 0;
                if (x != s) x = edges[p[x]].from;
            }
        }
        return flow;
    }
}isap;

int main() {

    cin >> n >> m >> s >> t;
    isap.init(n);
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        isap.addEdge(u, v, w);
    }
    cout << isap.Maxflow(s, t) << '\n';

    return 0;
}