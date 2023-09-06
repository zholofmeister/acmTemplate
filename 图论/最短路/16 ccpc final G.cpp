16 ccpc final G Pandaland  
时限:3000ms
题意：
给你一张图(不一定连通),求最小环。给你m行x1,y1,x2,y2,w,表示点(x1,y1)和点(x2,y2)之间有一条w的边。
1<=T<=50,1<=m<=4000,-10000<=xi,yi<=10000,1<=w<=1e5
思路：
n^3的floyd最小环肯定不行。
解法一： 
枚举删每条边，删除这条边，然后跑最短路，这两点的距离+这个删掉边的权值就是最小环,维护答案。
堆优化dij里面还要剪两次支，就很玄学。
时间复杂度 O(m*m*log(m))    result: 900ms
解法2：
**最短的环除去一条边后一定是在这个图的最小生成树上**。先kruskal求最短路，然后可以通过枚举不在树上的边，求树上这条边的两点间距离，并加上边的权值维护答案即可。
注意:题目给的图可能有多个联通块。
时间复杂度O(m*log(m))       result: 200ms

堆优化dij写法：
#define i64 long long
const int N=1*(int)1e4+100;
const i64 INF=0x3f3f3f3f3f3f3f3fLL;
int tc,m,head[N],tot;
i64 ans;
vector< pair<int, int> > b;
struct ED{
    int to,nxt,flag;
    i64 val;
}star[N];
struct Edge{
    int x11,y11,x22,y22;
    i64 w;
}e[N];
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
void addEdge(int a,int b,int c){
    star[tot].to=b;
    star[tot].val=c;
    star[tot].flag=0;
    star[tot].nxt=head[a];
    head[a]=tot++;
}
i64 dij(int s,int n,int ed){
    priority_queue<node> q;
    while(!q.empty()) q.pop();
    node cur;
    memset(dis,INF,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[s]=0;
    q.push(node(s,dis[s]));
    while(!q.empty()){
        cur=q.top();
		if(cur.id == ed) return dis[ed]; //剪枝1
		if(cur.w>ans) return INF;        //剪枝2
        q.pop();
        if(vis[cur.id]) continue;
        vis[cur.id]=1;
        for(int i=head[cur.id]; ~i; i=star[i].nxt){
            if(star[i].flag){
                continue;
            }
            if(!vis[star[i].to] && dis[star[i].to]>dis[cur.id]+star[i].val){
                dis[star[i].to]=dis[cur.id]+star[i].val;
                q.push(node(star[i].to,dis[star[i].to]));
            }
        }
    }
    return dis[ed];
}
void init(int n){
    for(int i=0; i<=n; ++i) G[i].clear();
}
unordered_map<int,int> idx;
int main(){
    int kase=1;
    cin>>tc;
    while(tc--){
        b.clear();
        tot=0;
        memset(head,-1,sizeof(head));
        cin>>m;
        for(int i=0; i<m; ++i){
            cin>>e[i].x11>>e[i].y11>>e[i].x22>>e[i].y22>>e[i].w;
            b.emplace_back(make_pair(e[i].x11,e[i].y11));
            b.emplace_back(make_pair(e[i].x22,e[i].y22));
        }
        sort(b.begin(),b.end());
        b.resize(unique(b.begin(),b.end())-b.begin());
        for(int i=0; i<m; ++i){
            int u=lower_bound(b.begin(),b.end(),make_pair(e[i].x11,e[i].y11))-b.begin();
            int v=lower_bound(b.begin(),b.end(),make_pair(e[i].x22,e[i].y22))-b.begin();
            addEdge(u,v,e[i].w);
            addEdge(v,u,e[i].w);
        }
        ans=(i64)1e10;
        for(int i=0; i<m; ++i){
            int st=lower_bound(b.begin(),b.end(),make_pair(e[i].x11,e[i].y11))-b.begin();
            int ed=lower_bound(b.begin(),b.end(),make_pair(e[i].x22,e[i].y22))-b.begin();
            star[i*2+1].flag=1;
            star[i*2].flag=1;
            i64 temp=e[i].w+dij(st,2*m+5,ed);
            ans=min(ans,temp);
            star[i*2+1].flag=0;
            star[i*2].flag=0;
        }
        if(ans==(i64)1e10) cout<<"Case #"<<kase++<<": "<<0<<'\n';
        else cout<<"Case #"<<kase++<<": "<<ans<<'\n';
    }
    return 0;
}




LCA写法：
#define i64 long long
const int N = 2*(int)10000+100; //要开两倍点数量的大小（欧拉序长度）
vector< pair<int,int> > b;
int n,fa[N];
int x11[N],y11[N],x22[N],y22[N],w11[N],chklca[N];
struct node{
    int a,b,used;
    i64 w;
    node() {
        used=0;
    }
    node(int _a,int _b,i64 _w){
        a=_a;
        b=_b;
        w=_w;
        used=0;
    }
    bool operator < (const node &b) const{
        return w<b.w;
    }
}nd[N];
struct LCA
{
	#define type long long
	struct node{int to;type w;node(){}node(int _to,type _w):to(_to),w(_w){}};
	type dist[N];
	int path[N],dep[N],loc[N],len[N],LOG[N],all,n;
	int dp[25][N], point[25][N];  //2^20 == 1e6  2^25 == 3e7
	vector<node> G[N];
	void dfs(int u, int now) {
        chklca[u]=1;   //因为有多棵不连通的树
		path[++all] = u;
		loc[u] = all;
		dep[all] = now;
		for (node cur : G[u]) {
            int v = cur.to;
			if (loc[v]) continue;
			len[v] = now+1;
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
int findRoot(int x){return (x==fa[x]?x:fa[x]=findRoot(fa[x]));}
int main() {
    int tc,kase=1;
    cin>>tc;
    while(tc--){
        b.clear();
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>x11[i]>>y11[i]>>x22[i]>>y22[i]>>w11[i];
            b.eb(mp(x11[i],y11[i]));
            b.eb(mp(x22[i],y22[i]));
        }
        sort(all(b));
        b.resize(unique(all(b))-b.begin());
        for(int i=0; i<n; ++i){
            int ai=lower_bound(all(b),mp(x11[i],y11[i]))-b.begin();
            int bi=lower_bound(all(b),mp(x22[i],y22[i]))-b.begin();
            nd[i]=node(ai,bi,w11[i]);
        }
        lca.init(SZ(b)+5);
        for(int i=0; i<SZ(b)+5; ++i){
            chklca[i]=0;
            fa[i]=i;
        }
        sort(nd,nd+n);
        int rt=-1;
        for(int i=0; i<n; ++i){
            int aa=findRoot(nd[i].a);
            int bb=findRoot(nd[i].b);
            if(aa!=bb){
                fa[bb]=aa;
                lca.addEdge(nd[i].a,nd[i].b,nd[i].w);
                nd[i].used=1;
            }
        }
        for(int i=0; i<SZ(b); ++i){
            if(!chklca[i]){
                lca.solve(i);
            }
        }
        i64 ans=(i64)1e10;
        for(int i=0; i<n; ++i){
            if(nd[i].used) continue;
            ans=min(ans,lca.getDist(nd[i].a,nd[i].b)+nd[i].w);
        }
        if(ans==(i64)1e10) ans=0; //cannot find cycle
        cout<<"Case #"<<kase++<<": "<<ans<<'\n';
    }
    return 0;
}
