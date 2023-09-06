//不能求最长路，不能处理带负权的边 用spfa搞
// stl优先队列是O(eloge),手写二叉堆是O(elogv),斐波那契堆是O(vlogv + e)
//点的编号从0开始
#define i64 long long
const int N = EDIT+1000; //点数
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
struct node {
    int id;
	i64 w;
    node(){}
    node(int a, i64 b) : id(a), w(b) {} //hdu6805 美好的回忆:>
    friend bool operator < (node a, node b) {return a.w > b.w;}
};
vector<node> G[N];
bool vis[N];
i64 dis[N];

void dij(int s, int n) {
    priority_queue<node> q;
	while (!q.empty()) q.pop();
    node cur;
    for (int i = 0; i <= n; ++i) { //另外,memset比for快哦
		dis[i] = INF;              
		vis[i] = 0;
	}
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.top();
        q.pop();                  //另外,能return要的值就return哦(ccpcfinal 2016 G 枚举m条边跑dij那题),会快很多
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (node to : G[cur.id]) {
            if (!vis[to.id] && dis[to.id] > dis[cur.id] + to.w) {   //dis[to.id] > to.w 就变成了堆优化prim
                dis[to.id] = dis[cur.id] + to.w;                    //堆优化prim下面也要改成dis[to.id] = to.w;
                q.push(node(to.id, dis[to.id]));
            }
        }
    }
}
void init(int n) {
    for (int i = 0; i <= n; ++i) G[i].clear();
}
void addEdge(int a, int b, int c){
    G[a].eb(node(b,c));
    G[b].eb(node(a,c));
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;//输入
    init(n);                //初始化
    forn(i, m) {
        int u, v, w;
        cin >> u >> v >> w; //输入
        G[u].emplace_back(node(v, w));//建图
        G[v].emplace_back(node(u, w));
    }
    dij(s, n);              //跑dij
    cout << dis[t] << '\n';
    return 0;
}
