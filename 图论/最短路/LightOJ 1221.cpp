LightOJ 1221 Travel Company
题意：
现在给你一张有向图（没写保证连通就是不连通），每条边都有收入和支出，现在要找到一个环让 环内总收入/环内总支出 > p,问你存不存在。
t<=100,2<=n(点数)<=100,0<=r(边数)<=9900,1<=p(要求的比例)<=100, 0<=a,b(顶点)<n, 0<=l(收入)<=5000,1<=e(支出)<=5000
思路：
总收入/总支出 > p 可以转换成 p*总支出 - 总收入 < 0,所以设a到b有一条收入l，支出e的边，那就a到b建一条 p*e-l 的边就行。
然后因为起点不知道，并且也不知道是不是连通，所以就对每个点跑spfa，没跑过的就跑，可以看代码里的vv数组，没了。

const int N = 100+100;
const i64 INF = 0x3f3f3f3f3f3f3f3fLL;
int tc,r,p;
int a,b,l,e;
int n,m,vv[N];
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
        vv[cur.id]=1;  //这个点跑过spfa咯 1.
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
    for (int i = 0; i <= n; ++i){
    	G[i].clear();
    	vv[i] = 0;
    }
}

int main() {
    int kase=1;
    scanf("%d",&tc);
    while(tc--){
    	scanf("%d%d%d",&n,&r,&p);
    	init(n+10);
    	forn(i, r){
    		scanf("%d%d%d%d",&a,&b,&l,&e);
    		G[a].eb(node(b,p*e-l));
    	}
    	bool ok=false;
    	forn(i, n){
    		if(vv[i]) continue; //这个点跑过spfa咯 2.
    		if(!spfa(i, n)){
    			ok=true;
    			break;
    		}
    	}
    	printf("Case %d: ",kase++);
    	printf("%s\n",ok?"YES":"NO");
    }
    return 0;
}
