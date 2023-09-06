#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, a, b) for (int i = (int)(a); i >= (int)b; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, r, l) for (int i = (r); i >= (l); i--)
#define ms(x, y) memset(x, y, sizeof(x))
#define SZ(x) int(x.size())
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef pair<i64, i64> pi64;
typedef double ld;
template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }
//1.integer overflow (1e5 * 1e5) (2e9 + 2e9)
//2.runtime error
//3.boundary condition
const int N = (int)1e5+100;
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
        dis[i] = -INF;
        vis[i]=cnt[i]=0;
    }
    vis[s] = 1;
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.front();
        q.pop();
		//判断负（正）环在这++ , 如果>n(n为这张图的点数，对应题目要求修改)就return true
		++cnt[cur.id];
		if(cnt[cur.id]>n+1) return false;
        vis[cur.id] = 0;
        for (node to : G[cur.id]) {
            if (dis[to.id] < dis[cur.id]+to.w) {
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
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#endif
    cin>>n>>m;
    init(n+5);
    int S=0;
    bool pre=false;
    forn(i, m){
        int op,a,b;
        cin>>op>>a>>b;
        if(a==b) if(op==2 || op==4) pre=true;
        if(op==1){
            G[a].eb(node(b,0));
            G[b].eb(node(a,0));
        } else if(op==2){
            G[a].eb(node(b,1));
        } else if(op==3){
            G[b].eb(node(a,0));
        } else if(op==4){
            G[b].eb(node(a,1));
        } else if(op==5){
            G[a].eb(node(b,0));
        }
    }
    if(pre){  //特判，自己不可能比自己多或者少
        cout<<-1<<'\n';
        return 0;
    }
    for1(i, n) G[S].eb(node(i,1)); //因为每个儿童至少要一个糖果，可以先连1的边，然后跑最长路
    if(spfa(S,n)){
        i64 sum=0;
        for1(i, n) sum+=dis[i];
        cout<<sum<<'\n';
    } else cout<<-1<<'\n';
#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
