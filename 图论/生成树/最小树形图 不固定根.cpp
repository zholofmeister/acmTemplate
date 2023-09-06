hdu 2121
给你一个n个点，m条边的有向图，让你选一个点作为首都，这个首都到其他点的权值和最小，如果有的话就输出权值和以及作为首都的那个点，不存在的话就输出impossible

const int N=10050,M=50050,inf=0x7ffffff; //N顶点数，M边数
int n,m;
int ROOT,st,tot;
struct DMST{
    int n,sz,pre[N],id[N],vis[N],in[N];
    struct EDGE{
        int u,v,cost;
        EDGE(){}
        EDGE(int a,int b,int c):u(a),v(b),cost(c){}
    }E[M];
    void init(int _n){
        n=_n;
        sz=0;
    }
    void add(int u,int v,int w){
        E[sz++]=EDGE(u,v,w);
    }
    int dmst(int root){
        int u,v,cnt,ret=0;
        while(1){
            for(int i=0; i<n; ++i) in[i]=inf;
            for(int i=0; i<sz; ++i){
                u=E[i].u,v=E[i].v;
                if(E[i].cost<in[v] && u!=v){
                    pre[v]=u;
                    in[v]=E[i].cost;
                    if(u==root) ROOT=i;
                }
            }
            for(int i=0; i<n; ++i){
                if(i!=root && in[i]==inf) return -1;
            }
            cnt=in[root]=0;
            for(int i=0; i<n; ++i) id[i]=vis[i]=-1;
            for(int i=0; i<n; ++i){
                ret+=in[i],v=i;
                while(vis[v]!=i && id[v]==-1 && v!=root) {
                    vis[v]=i;
                    v=pre[v];
                }
                if(v!=root && id[v]==-1){
                    for(u=pre[v]; u!=v; u=pre[u]) id[u]=cnt;
                    id[v]=cnt++;
                }
            }
            if(!cnt) break;
            for(int i=0; i<n; ++i) if(id[i]==-1) id[i]=cnt++;
            for(int i=0; v=E[i].v,i<sz; ++i){
                E[i].u=id[E[i].u],E[i].v=id[E[i].v];
                if(E[i].u!=E[i].v) E[i].cost-=in[v];
            }
            n=cnt,root=id[root];
        }
        return ret;
    }
}G;
void variable(int &cost, int &root){ //Variable Root
    for(int i=0; i<n; ++i) G.add(st,i,tot); //st=n,tot=sum of Edge Wight+1
    int ans=G.dmst(st);
    if(ans==-1 || ans-tot>=tot){
        cout<<"impossible"<<'\n';
        cout<<'\n';
        return;
    }
    cost=ans-tot,root=ROOT-m;
    cout<<cost<<' '<<root<<'\n';
    cout<<'\n';
    return;
}
int main() {
    while(cin>>n>>m){
        G.init(n+1); //+1是给虚点准备的,fk cls
        tot=1;
        for(int i=0; i<m; ++i){
            int a,b,c;
            cin>>a>>b>>c;
            tot+=c;
            G.add(a,b,c);
        }
        st=n;
        int cost=0,root=0;
        variable(cost,root);
    }
    return 0;
}
