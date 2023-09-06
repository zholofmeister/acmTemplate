//不能求最长路 最长路用spfa搞
//时间复杂度 O(e*log(e))
#define i64 long long

const int maxn = ; //点数
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
struct node {
    int id;
	i64 w; 
    node(){}
    node(int a, int b) : id(a), w(b) {}
    friend bool operator < (node a, node b) {return a.w > b.w;}
};
vector<node> G[maxn];
bool vis[maxn];
i64 dis[maxn];

void dij(int s, int n) {
    priority_queue<node> q;
	while (!q.empty()) q.pop();
    node cur;
    for (int i = 1; i <= n; ++i) {
		dis[i] = INF;
		vis[i] = 0;
	}
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.top();
        q.pop();
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (node to : G[cur.id]) {
            if (!vis[to.id] && dis[to.id] > dis[cur.id]+to.w) {   //dis[to.id] > to.w 就变成了堆优化prim
                dis[to.id] = dis[cur.id]+to.w;
                q.push(node(to.id, dis[to.id]));
            }
        }
    }
}
void init(int n) {
    for (int i = 0; i <= n; ++i) G[i].clear();
}

int main() {

    int n, m, s, t;
    cin >> n >> m >> s >> t;//输入
    init(n);                //初始化
    forn(i, m) {
        int u, v, w;
        cin >> u >> v >> w; //输入
        G[u].eb(node(v, w));//建图
        G[v].eb(node(u, w));
    }
    dij(s, n);              //跑dij
    cout << dis[t] << '\n';

    return 0;
}
