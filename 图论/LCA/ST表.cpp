// 洛谷P3379
// LCA模板题，查询两个节点的最近公共祖先 (节点编号1~n)

#include <bits/stdc++.h>

using namespace std;

//预处理O(nlogn) 在线查询O(1)
const int maxn = 2*500000+100; //要开两倍点数量的大小（欧拉序长度）
struct LCA
{
	#define type int
	struct node{int to;type w;node(){}node(int _to,type _w):to(_to),w(_w){}};
	type dist[maxn];
	int path[maxn],dep[maxn],loc[maxn],len[maxn],LOG[maxn],all,n;
	int dp[25][maxn], point[25][maxn];  //2^20 == 1e6  2^25 == 3e7
	vector<node> G[maxn];
	void dfs(int u, int now) {
		path[++all] = u;
		loc[u] = all;
		dep[all] = now;
		len[u] = now;
		for (node cur : G[u]) {
			int v = cur.to;
			if (loc[v]) continue;
			dist[v] = dist[u]+cur.w;
			dfs(v, now+1);
			path[++all] = u;
			dep[all] = now;
		}
	}
	void initRMQ(int n)
	{
		LOG[0] = -1;
		for (int i = 1; i <= all; ++i) {
			dp[0][i] = dep[i];
			point[0][i] = path[i];
			LOG[i] = ((i&(i-1)) == 0 ? LOG[i-1]+1 : LOG[i-1]);
		}
        for (int i = 1; (1<<i) <= all; ++i) {
            for (int j = 1; j+(1<<i)-1 <= all; ++j) {
              if (dp[i-1][j] < dp[i-1][j+(1<<(i-1))]) {
                dp[i][j] = dp[i-1][j];
                point[i][j] = point[i-1][j];
              } else {
                dp[i][j] = dp[i-1][j+(1<<(i-1))];
                point[i][j] = point[i-1][j+(1<<(i-1))];
              }
            }
        }
	}
	int queryLCA(int l,int r)
	{
		l = loc[l]; r = loc[r];
		if(l>r) swap(l,r);
		int k = LOG[r-l+1];
		/*
		貌似下面这种写法对于某些数据情况更快，对于某些数据也更慢- -
		记得把上面预处理的LOG删了
		 P 3379
		int k=0;
		while((1<<k)<=r-l+1) k++;
		k--;
		*/
		if(dp[k][l] < dp[k][r-(1<<k)+1]) return point[k][l];
		else return point[k][r-(1<<k)+1];
	}

	type getDist(int a,int b){return dist[a]+dist[b]-2*dist[queryLCA(a,b)];}
	int getLen(int a,int b){return len[a]+len[b]-2*len[queryLCA(a,b)];}
	void init(int _n)
	{
		n = _n;
		all = 0;
		for(int i = 0;i <= n; i++)
		{
			loc[i] = 0;
			dist[i] = 0;
			len[i] = 0;
			G[i].clear();
		}
	}
	void addEdge(int a,int b,type w=1)
	{
		G[a].emplace_back(node(b,w));
		G[b].emplace_back(node(a,w));
	}
	void solve(int root)
	{
		dfs(root, 1);
		initRMQ(all);
	}
	#undef type
}lca;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m, s;
    // n个点，m个询问，s是根节点
    cin >> n >> m >> s;  
    lca.init(n); // 预处理所有节点
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        lca.addEdge(a, b, 1);
    }
    lca.solve(s); // 从根节点出发
    for(int i = 0; i < m; i++) {
      	int a, b;
        cin >> a >> b;
        cout << lca.queryLCA(a, b) << '\n';
		// printf("%d\n", lca.queryLCA(a, b));
		// printf("%d\n", lca.getLen(a, b));  //深度 1
		// printf("%d\n", lca.getDist(a, b)); //长度 w 
    }

    return 0;
}