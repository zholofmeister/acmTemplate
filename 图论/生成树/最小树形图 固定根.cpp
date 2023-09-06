洛谷模板题 复杂度O(n*m)?? 朱刘
点编号从0~n-1
题意：
给你n个点，m条边，指定一个根r，问你最小树形图的权值和是多少
1<=n<=100, 1<=m<=1e4, 1<=w<=1e6

const int N=200;
const int INF=0x3f3f3f3f;
int n,m,r;
//固定根的最小树形图，邻接矩阵写法
struct DMST{
    int n;
    int w[N][N];   // 边权
    int vis[N];    // 访问标记，仅用来判断无解
    int ans;       // 计算答案
    int removed[N];// 每个点是否被删除
    int cid[N];    // 所在圈编号
    int pre[N];    // 最小入边的起点
    int iw[N];     // 最小入边的权值
    int max_cid;   // 最大圈编号
    void init(int n){
        this->n=n;
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j) w[i][j]=INF;
    }
    void addEdge(int u, int v, int cost){
        w[u][v]=min(w[u][v],cost); //重边取边权最小的
    }
    //从S出发能到达多少个节点
    int dfs(int s){
        vis[s]=1;
        int ans=1;
        for(int i=0; i<n; ++i)
            if(!vis[i] && w[s][i]<INF) ans+=dfs(i);
        return ans;
    }
    //从u除法沿着pre指针找环
    bool cycle(int u){
        ++max_cid;
        int v=u;
        while(cid[v]!=max_cid){
            cid[v]=max_cid;
            v=pre[v];
        }
        return v==u;
    }
    //计算u的最小入弧，入弧起点不得在圈C中
    void update(int u){
        iw[u]=INF;
        for(int i=0; i<n; ++i){
            if(!removed[i] && w[i][u]<iw[u]){
                iw[u]=w[i][u];
                pre[u]=i;
            }
        }
    }
    //根节点为S，如果失败则返回false
    bool solve(int s){
        memset(vis,0,sizeof(vis));
        if(dfs(s)!=n) return false;
        memset(removed,0,sizeof(removed));
        memset(cid,0,sizeof(cid));
        for(int u=0; u<n; ++u) update(u);
        pre[s]=s;
        iw[s]=0;
        ans=max_cid=0;
        for(;;){
            bool have_cycle=false;
            for(int u=0; u<n; ++u){
                if(u!=s && !removed[u] && cycle(u)){
                    have_cycle=true;
                    //以下代码缩环，环上除了u之外的节点均删除
                    int v=u;
                    do{
                        if(v!=u) removed[v]=1;
                        ans+=iw[v];
                        //对于圈外点i,把i->v改成i->u(并调整权值);v->i改为u->i
                        //注意圈上可能还有一个v'使得i->v'或者v'->i存在
                        //因此只保留权值最小的i->u和u->i
                        for(int i=0; i<n; ++i){
                            if(cid[i]!=cid[u] && !removed[i]){
                                if(cid[i]!=cid[u] && !removed[i]){
                                    if(w[i][v]<INF) w[i][u]=min(w[i][u],w[i][v]-iw[v]);
                                    w[u][i]=min(w[u][i],w[v][i]);
                                    if(pre[i]==v) pre[i]=u;
                                }
                            }
                        }
                        v=pre[v];
                    }while(v!=u);
                    update(u);
                    break;
                }
            }
            if(!have_cycle) break;
        }
        for(int i=0; i<n; ++i) if(!removed[i]) ans+=iw[i];
        return true;
    }
}dmst;
signed main() {
    cin>>n>>m>>r;
    dmst.init(n);//别忘初始化，只能赋值n(点数)，因为这个n是给到mdst里的n
    forn(i, m){
        int a,b,c;
        cin>>a>>b>>c;
        --a; --b;
        dmst.addEdge(a,b,c);
    }
    if(!dmst.solve(--r)) cout<<-1<<'\n';
    else cout<<dmst.ans<<'\n';
    return 0;
}

