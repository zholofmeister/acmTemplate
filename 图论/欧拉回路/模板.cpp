//下面O(n+m)求欧拉回路的代码中，n为点数，m为边数。
//若有解则一次输出经过的边的编号。
//若是无向图，则正数表示x到y，负数表示y到x。
const int N=点数;
const int M=边数;
namespace UndirectedGraph{
    int n,m,i,x[M],y[M],d[N],g[N],v[M<<1],w[M<<1],vis[M<<1],nxt[M<<1],ed;
    int ans[M],cnt;
    void addEdge(int x,int y,int z){
        d[x]++;
        v[++ed]=y; w[ed]=z; nxt[ed]=g[x]; g[x]=ed;
    }
    void dfs(int x){
        for(int &i=g[x];i;){
            if(vis[i]){i=nxt[i];continue;}
            vis[i]=vis[i^1]=1;
            int j=w[i];
            dfs(v[i]);
            ans[++cnt]=j;
        }
    }
    void solve(){
        scanf("%d%d",&n,&m);
        ed=1;
        for(int i=0; i<=n; ++i) cnt=d[i]=g[i]=0;
        for(int i=m+1; i<=2*m+10; ++i) vis[i]=0;
        for(int i=0; i<=m; ++i) vis[i]=ans[i]=0;
        for(i=1; i<=m; ++i) scanf("%d%d",&x[i],&y[i]),addEdge(x[i],y[i],i),addEdge(y[i],x[i],-i);
        for(i=1; i<=n; ++i) if(d[i]&1) {puts("NO");return;}
        for(i=1; i<=n; ++i) if(g[i]) {dfs(i);break;}
        for(i=1; i<=n; ++i) if(g[i]) {puts("NO");return;}
        puts("YES");
        for(i=m; i; i--) printf("%d ",ans[i]);
    }
}
namespace DirectedGraph{
    int n,m,i,x,y,d[N],g[N],v[M],vis[M],nxt[M],ed;
    int ans[M],cnt;
    void addEdge(int x,int y){
        d[x]++; d[y]--;
        v[++ed]=y; nxt[ed]=g[x]; g[x]=ed;
    }
    void dfs(int x){
        for(int &i=g[x];i;){
            if(vis[i]){i=nxt[i];continue;}
            vis[i]=1;
            int j=i;
            dfs(v[i]);
            ans[++cnt]=j;
        }
    }
    void solve(){
        scanf("%d%d",&n,&m);
		ed=0;
        for(int i=0; i<=n; ++i) cnt=d[i]=g[i]=0;
        for(int i=0; i<=m+10; ++i) vis[i]=ans[i]=0;
        for(i=1; i<=m; ++i) scanf("%d%d",&x,&y),addEdge(x,y);
        for(i=1; i<=n; ++i) if(d[i]) {puts("NO");return;}
        for(i=1; i<=n; ++i) if(g[i]) {dfs(i);break;}
        for(i=1; i<=n; ++i) if(g[i]) {puts("NO");return;}
        puts("YES");
        for(i=m; i; i--) printf("%d ",ans[i]);
    }
}