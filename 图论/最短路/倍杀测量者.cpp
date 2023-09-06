倍杀测量者
题意：
第一行三个整数n,s,t,分别表示机房内选手人数，选手立下的flag总数和已知的选手分数的数量。n位选手从1开始编号至n，编号为k的选手被称为选手k。
接下来s行，每行四个整数o,A,B,k。其中 o=1 表示选手A立下了“我没k倍杀选手B就女装”的flag, o=2 表示选手A立下了“选手B把我k倍杀我就女装”的flag。
接下来t行，每行两个整数C,x,表示已知选手C的分数为x。
若存在能保证赛后有选手女装的最大的T，则输出T，只有当输出与答案的绝对误差不超过(1e-4)时才被视作正确输出。若不存在，输出"-1"
1<=n,s<=1000,1<=A,B,C,t<=n,1<=j<=10,1<=x<=1e9。 保证输入中的c两辆不同。
思路：
二分+拆分约束
我跑的最长路，最长路建边其实就是最短路建边，然后边调个头 && 边权取反就行。

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
const int N = 2000;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
int n,s,t;
struct node {
    int id,type;
	double w;
    node() {}
    node(int a, double b, int _type=-1) : id(a), w(b), type(_type) {}
};
vector<node> G[N];
double dis[N];
int cnt[N];
bool vis[N];

bool spfa(int s, int n, double now) { //s是起点,n是上界点数,点的编号从0开始
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
            double ew=to.w;
            if(to.type==1) ew=log2(ew-now);
            else if(to.type==2) ew=-log2(ew+now);
            if (dis[to.id] < dis[cur.id]+ew) {
                dis[to.id] = dis[cur.id]+ew;
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
    cout<<fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#endif
    cin>>n>>s>>t;
    double l=0,r=10,ans; //下面二分的准备
    int S=0;             //源点
    forn(i, s){
        int o,a,b;
        double k;
        cin>>o>>a>>b>>k;
        G[b].eb(node(a,k,o));
        if(o==1) uin(r,k); //K-T要>0
    }
    forn(i, t){
        int c,x;
        cin>>c>>x;
        G[c].eb(node(S,-log2(x),3));
        G[S].eb(node(c,log2(x),3));
    }
    for(int i=1; i<=n; ++i) G[S].eb(node(i,0,3));
    if(spfa(S,n,0)){  //不管k怎么取，都没人女装
        cout<<-1<<'\n';
        return 0;
    }
    forn(i,50){
        double mid=(l+r)*0.5;
        if(!spfa(S,n,mid)){ //有人立的flag假了，要女装
            l=mid;
            ans=mid;
        } else r=mid;
    }
    cout<<ans<<'\n';
#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
