//洛谷 johnson全源最短路模板题
Johnson 算法则通过另外一种方法来给每条边重新标注边权。
我们新建一个虚拟节点（在这里我们就设它的编号为0）。从这个点向其他所有点连一条边权为 0 的边。
接下来用 Bellman-Ford 算法求出从 0 号点到其他所有点的最短路，记为dis[i]
假如存在一条从 u 点到 v 点，边权为 w 的边，则我们将该边的边权重新设置为 w+dis[u]-dis[v] 
接下来以每个点为起点，跑 n 轮 Dijkstra 算法即可求出任意两点间的最短路了(要把偏移量dis[v]-dis[u]加上)。

const int N = 3100;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
int n,m,u[6100],v[6100],w[6100];
struct node {
    int id;
	i64 w;
    node(){}
    node(int a, i64 b) : id(a), w(b) {} //hdu6805 美好的回忆:>
    friend bool operator < (node a, node b) {return a.w > b.w;}
};
vector<node> G[N];
i64 dis[N],cnt[N],d2[N];
bool vis[N];
bool spfa(int s, int n) { //s是起点,n是点数,点的编号从0开始
    queue<node> q;
    node cur;
    ms(vis,0);
    ms(cnt,0);
    for (int i = 0; i <= n; ++i) dis[i] = INF;
    vis[s] = 1;
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        vis[cur.id] = 0;
        //判断负（正）环在这++ , 如果>n(n为这张图的点数，对应题目要求修改)就return true
        ++cnt[cur.id];
        if(cnt[cur.id]>n) return false;
        for (node to : G[cur.id]) {
            if (dis[to.id] > dis[cur.id]+to.w) {
                dis[to.id] = dis[cur.id]+to.w;
                if (!v  is[to.id]) {
                    q.push(node(to.id, dis[to.id]));
                    vis[to.id] = 1;
                }
            }
        }
    }
    return true;
}
void dij(int s, int n) {
    priority_queue<node> q;
	while (!q.empty()) q.pop();
    node cur;
    for (int i = 0; i <= n; ++i) {
		d2[i] = INF;
		vis[i] = 0;
	}
    d2[s] = 0;
    q.push(node(s, d2[s]));
    while (!q.empty()) {
        cur = q.top();
        q.pop();
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (node to : G[cur.id]) {
            if (!vis[to.id] && d2[to.id] > d2[cur.id] + to.w) {   //dis[to.id] > to.w 就变成了堆优化prim
                d2[to.id] = d2[cur.id] + to.w;
                q.push(node(to.id, d2[to.id]));
            }
        }
    }
}
void init(int n) {
    for (int i = 0; i <= n; ++i) G[i].clear();
}
signed main() {
    cin>>n>>m;
    init(n+5);
    for(int i=0; i<m; ++i){
        cin>>u[i]>>v[i]>>w[i];
        G[u[i]].eb(node(v[i],w[i]));
    }
    for(int i=1; i<=n; ++i) G[0].eb(node(i,0));
    if(!spfa(0,n)){
        cout<<-1<<'\n';
        return 0;
    }
    for(int i=1; i<=n; ++i){
        for(node &now:G[i]){
            now.w+=dis[i]-dis[now.id];
        }
    for(int i=1; i<=n; ++i){
        dij(i,n);
        i64 ans=0;
        for(i64 j=1; j<=n; ++j){
            if(d2[j]==INF) ans+=j*1000000000LL; //1e9
            else ans+=j*(d2[j]+dis[j]-dis[i]);
        }
        cout<<ans<<'\n';
    }
    return 0;
}

