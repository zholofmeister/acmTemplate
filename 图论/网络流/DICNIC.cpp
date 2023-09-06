/*
网络流dinic复杂度
上届O((n^2)m)
若所有边容量为1,O(min(n^(1/3),m^(1/2))m)
二分图O(n^(1/2)m)
*/
//如果是无向图，加的反向边流量也为w，而不是0
//要开long long不如直接#define int long long,注意要把int()改成(int)()
const int N = EDIT+100;   //点数
const int INF = 0x3f3f3f3f;           //ll const i64 INF =0x8个3fLL;  .1.
struct Edge{
    int from, to, cap, flow;          //如果要开ll的话，这边也要开ll      .2.
    Edge(int u, int v, int c, int f)  //如果要开ll的话，这边也要开ll      .3.
        : from(u), to(v), cap(c), flow(f) {}
};
struct Dicnic {
    #define Type int
    int n, m, s, t;        //节点数，边数（包括反向弧），源点编号和汇点编号
    vector<Edge> edges;    //边表。edge[e]和edge[e^1]互为反向弧
    vector<int> G[N];   //邻接表，G[i][j]表示节点i的第j条边在e数组中的编号
    bool vis[N];        //BFS使用
    Type d[N];           //从起点到i的距离
    int cur[N];         //当前弧下标
    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; ++i) G[i].clear();
        edges.clear();
    }
    void addEdge(int from, int to, Type cap) {
        edges.emplace_back(Edge(from, to, cap, 0));
        edges.emplace_back(Edge(to, from, 0, 0));
        m = int(edges.size());
        G[from].emplace_back(m-2);
        G[to].emplace_back(m-1);
    }
    bool BFS() {
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        queue<int> q;
		while (!q.empty()) q.pop();
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < int(G[x].size()); ++i) {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    Type DFS(int x, Type a) {
        if (x == t || a == 0) return a;
        Type flow = 0, f;
        for (int &i = cur[x]; i < int(G[x].size()); ++i) { //从上次考虑的弧
            Edge &e = edges[G[x][i]];
            if (d[x]+1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    Type Maxflow(int s, int t) {
        this->s = s; this->t = t;
        Type flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
    #undef Type
}dicnic;

int main() {
    cin >> n >> m >> s >> t;              //V, E, 原点, 汇点
    dicnic.init(n);                       //初始化
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        dicnic.addEdge(u, v, w);          //建图
    }
    cout << dicnic.Maxflow(s, t) << '\n'; //跑最大流
    return 0;
}