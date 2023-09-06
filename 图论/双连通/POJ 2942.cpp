#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <queue>
#include <math.h>
#include <map>
#include <stack>
#include <sstream>
#include <set>
#include <iterator>
#include <list>
#include <cstdio>
#include <iomanip>
#include <climits>
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
const int N = 1000+100; //点数
int n,m,mep[N][N];
vector<int> E[N];
struct BCC {
    int n, bcc, top, tot;
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N];
    int stk[N];
    int cut[N], add_block[N];
    int col[N], vis[N];

    bool findOddCircle(int now,int c){ //找奇环
        col[now]=c;
        for(int i=0; i<int(G[now].size()); ++i){
            int to=G[now][i];
            if(belong[now]!=belong[to]) continue;
            if(col[to]==-1){
                if(findOddCircle(to,c^1)) return true;
            }
            if(col[to]==col[now]) return true;
        }
        return false;
    }
    void dfs(int x, int pre) {
        stk[top++] = x;
        low[x] = dfn[x] = ++tot;
        fa[x] = pre;
        int son = 0;
        for (int i=0; i<int(G[x].size()); ++i) {
            int to=int(G[x][i]);
            if (to == pre) continue;
            if (!dfn[to]) {
                ++son;
                dfs(to, x);
                low[x] = min(low[x], low[to]);
                if (low[to] >= dfn[x]) {
                    cut[x] = 1;
                    add_block[x]++;
                    ++bcc;
                    int temp;
                    vector<int> p; p.clear();
                    do {
                        temp = stk[--top];
                        p.pb(temp);
                        belong[ temp] = bcc;
                    } while (temp != to); //魔改bcc，得出所有的bcc(包括大bcc包含的小的bcc)
                    belong[x]=bcc;
                    p.pb(x);
                    if(int(p.size())>=3){
                        ms(col,-1);
                        if(findOddCircle(temp,0)) for(int j=0; j<int(p.size()); ++j) vis[p[j]]=1;
                    }
                }
                if (low[to] > dfn[x]) bridge.push_back(make_pair(x, to));
            }
            else low[x] = min(low[x], dfn[to]);
        }
        if (x == pre && son > 1) {
            cut[x] = 1;
            add_block[x] = son-1;
        }
    }
    void solve(int _n, vector<int> E[]) {
        n = _n;
        for (int i = 1; i <= n; ++i) {
            belong[i]=0;
            G[i] = E[i];
            low[i] = dfn[i] = stk[i] = fa[i] = 0;
            cut[i] = add_block[i] = 0;
            vis[i]=0;
        }
        bcc = top = tot = 0;
        bridge.clear();
        for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i, i);
    }
    void rebuild(vector<int> E[]) {
        for (int i = 1; i <= n; ++i) E[i].clear();
        for (int i = 1; i <= n; ++i) {
            int t = fa[i];
            if (belong[i] != belong[t]) {
                E[belong[i]].push_back(belong[t]);
                E[belong[t]].push_back(belong[i]);
            }
        }
    }
}bcc;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#endif
    while(~scanf("%d%d",&n,&m)){
        if(!n && !m) break;
        for(int i=0; i<=n; ++i){
            E[i].clear();
            for(int j=0; j<=n; ++j) mep[i][j]=0;
        }
        forn(i, m){
            int u,v;
            scanf("%d%d",&u,&v);
            mep[u][v]=mep[v][u]=1;
        }
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if(i==j) continue; //别tm建自环
                if(!mep[i][j]){
                    E[i].pb(j);
                }
            }
        }
        bcc.solve(n,E);
        int sum=n;
        for(int i=1; i<=n; ++i) if(bcc.vis[i]) --sum;
        printf("%d\n",sum);
    }
#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
