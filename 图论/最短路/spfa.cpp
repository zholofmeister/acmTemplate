//最长路 or 判断正环: dis变成-INF，松弛改成< 
//判负环跑最短路，判正环跑最长路
//一般时间复杂度O(k(常数) * E)  最差复杂度O(V * E)
//SPFA总的期望时间复杂度为O(n*logn*log(m/n) + m)
#define i64 long long
const int N = EDIT+100;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
int n,m;
struct node {
    int id;
	i64 w;
    node() {}
    node(int a, i64 b) : id(a), w(b) {}
};
vector<node> G[N];
i64 dis[N],cnt[N];
bool vis[N];

bool spfa(int s, int n) { //s是起点,n是上界点数,点的编号从0开始
    queue<node> q;
    node cur;
	for (int i = 0; i <= n; ++i){
        dis[i] = INF;
        vis[i] = cnt[i] = 0;
    }
    vis[s] = 1;
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.front();
        q.pop();
		//判断负（正）环在这++ , 如果>n(n为这张图的点数，对应题目要求修改)就return false
		++cnt[cur.id];
		if(cnt[cur.id]>n) return false; //一定要是>n
        vis[cur.id] = 0;
        for (node to : G[cur.id]) {
            if (dis[to.id] > dis[cur.id]+to.w) {           
                dis[to.id] = dis[cur.id]+to.w;
                if (!vis[to.id]) {
                    q.push(node(to.id, dis[to.id]));
                    vis[to.id] = 1;
                }
            }
        }
    }
    return true;
}
void init(int n) {
    for (int i = 0; i <= n; ++i) G[i].clear();
}

int main() {

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    init(n);
    forn(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].pb(node(v, w));
        G[v].pb(node(u, w));
    }
    spfa(s, n); //s是起点，n是点数
    cout << dis[t] << '\n';

    return 0;
}