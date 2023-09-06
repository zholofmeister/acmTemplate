LightOJ 1108 Instant View of Big Bang
题意：
给你一张有向带权图，现在问你有哪些点可以走到负环，有的话就输出所有点，没的话就输出impossible
t<=125,1<=n<=1000,0<=m<=2000,0<=x,y<n,-1000<=t(权值)<=1000
思路：
1. 单纯用spfa搞，直接建反向图，然后跑负环，如果跑到负环就dfs那个点能到哪些点，然后存起来最后输出就行，注意spfa里和for里要判vv！不然会超时
别问为什么不能建正向图跑负环 + 跑反向图看能到哪些点，问就是毒瘤题。
2. 建反向图，先跑强连通，然后继续for所有点spfa，这里spfa能走边的前提是两个点属于同一个强连通分量，因为负环肯定是一个强连通里的嘛，如果发现是负环也就加入点集里。
最后对点集跑个bfs看能到哪些点就行

解法1：
const int N = 2000+100;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
int n,m;
int tc,x[N],y[N],vv[N];
i64 t[N];
set<int> st;
bool have_cycle;
struct node {
    int id;
	i64 w;
    node() {}
    node(int a, i64 b) : id(a), w(b) {}
};
vector<node> G[N],E[N];
i64 dis[N],cnt[N];
bool vis[N];

void dfs(int x){
	vv[x]=1;
	st.insert(x);
	for(node to:E[x]){
		if(vv[to.id]) continue;
		dfs(to.id);
	}
}
bool spfa(int s, int n) { //s是起点,n是上界点数,点的编号从0开始
    queue<node> q;
    node cur;
	for (int i = 0; i <= n; ++i){
        dis[i] = INF;
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
		if(cnt[cur.id]>n){
			have_cycle=true;
			dfs(cur.id);
			return false;
		}
        vis[cur.id] = 0;
        for (node to : E[cur.id]) {
            if (dis[to.id] > dis[cur.id]+to.w) {
            	if(vv[to.id]) continue;
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
	st.clear();
	have_cycle=false;
    for (int i = 0; i <= n; ++i){
    	G[i].clear();
    	E[i].clear();
    	vv[i]=0;
    }
}
int main() {
    int kase=1;
    scanf("%d",&tc);
    while(tc--){
    	scanf("%d%d",&n,&m);
    	init(n+5);
    	forn(i, m){
    		scanf("%d%d%lld",&x[i],&y[i],&t[i]);
    		G[x[i]].eb(node(y[i],t[i]));
    		E[y[i]].eb(node(x[i],t[i]));
    	}	
    	forn(i, n){
    		if(vv[i]) continue;
    		spfa(i, n);
    	}
    	printf("Case %d:",kase++);
    	if(!have_cycle) printf(" impossible\n");
    	else{
    		for(int x:st) printf(" %d",x);
    		puts("");
    	}
    }
    return 0;
}

解法2：
const int N = 3000+100;   //点数
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
vi neg,ans;
int final[N];
int tc,n,m;
int scc, top, tot;
int been[N];
vector<int> G[N];
int low[N], dfn[N], belong[N];
int stk[N], vis[N];
struct node {
    int id;
	i64 w;
    node() {}
    node(int a, i64 b) : id(a), w(b) {}
};
vector<node> G2[N];
i64 dis[N],cnt[N];
bool vv[N];
bool spfa(int s, int n) { //s是起点,n是上界点数,点的编号从0开始
    queue<node> q;
    node cur;
	for (int i = 0; i <= n; ++i){
        dis[i] = INF;
        vv[i] = cnt[i] = 0;
    }
    vv[s] = 1;
    dis[s] = 0;
    q.push(node(s, dis[s]));
    while (!q.empty()) {
        cur = q.front();
        q.pop();
		//判断负（正）环在这++ , 如果>n(n为这张图的点数，对应题目要求修改)就return false
		been[cur.id]=1;
		++cnt[cur.id];
		if(cnt[cur.id]>n){
			neg.eb(cur.id);
			return false; //一定要是>n
		}
        vv[cur.id] = 0;
        for (node to : G2[cur.id]) {
        	if(belong[to.id] != belong[cur.id]) continue;
            if (dis[to.id] > dis[cur.id]+to.w) {           
                dis[to.id] = dis[cur.id]+to.w;
                if (!vv[to.id]) {
                    q.push(node(to.id, dis[to.id]));
                    vv[to.id] = 1;
                }
            }
        }
    }
    return true;
}
void init2(int n) {
    for (int i = 0; i <= n; ++i){
    	G2[i].clear();
    	been[i]=0;
    	final[i]=0;
    }
}
void init(int n) {
    for (int i = 0; i <= n; ++i) {
        G[i].clear();
        low[i] = 0;
        dfn[i] = 0;
        stk[i] = 0;
        vis[i] = 0;
    }
    scc = top = tot = 0;
}
void tarjan(int x) {
    stk[top++] = x;
    low[x] = dfn[x] = ++tot;
    vis[x] = 1;
    for (int to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to]) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (low[x] == dfn[x]) {
        ++scc;
        int temp;
        do {
            temp = stk[--top];
            belong[temp] = scc;
            vis[temp] = 0;
        } while (temp != x);
    }
}
void bfs(){
	queue<int> q;
	for(int x:neg){
		q.push(x);
		final[x]=1;
		ans.eb(x);
	}
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int to:G[x]){
			if(!final[to]){
				final[to]=1;
				q.push(to);
				ans.eb(to);
			}
		}
	}
}
int main() {
	scanf("%d",&tc);
	int kase=1;
	while(tc--){
		scanf("%d%d",&n,&m);
		neg.clear();
		ans.clear();
		init(n+5);
		init2(n+5);
		forn(i, m){
			int x,y,t;
			scanf("%d%d%d",&x,&y,&t);
			++x; ++y;
			//printf("x:%d y:%d\n",x,y);
			G[y].eb(x);
			G2[y].eb(node(x,t));
		}
		for1(i, n) if(!dfn[i]) tarjan(i);
		for1(i, n){
			if(been[i]) continue;
			spfa(i, n);
		}
		bfs();
		printf("Case %d:",kase++);
		if(!SZ(ans)) printf(" impossible\n");
		else{
			sort(all(ans));
			for(int x:ans) printf(" %d",x-1);
			puts("");
		}
	}    
    return 0;
}
