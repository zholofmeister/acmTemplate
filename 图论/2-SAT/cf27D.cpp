cf 27D
问题：
给你一个环，然后给你m条边，表示要连这两条边，现在只能在里面连或者在外面连两种方式，问是否可行
关键要判环内两边是否一定规范相交(相交但不是端点相交)
环的编号是顺序的1~n,输入时已经保证每个seg的l < r。
4<=n<=100,1<=m<=100,1<=ai,bi<=n,ai!=bi
思路：
下面的是判线段相交的代码
bool within(int x,int y,int z){
    return (x<z && z<y);
}
bool intersect(int i1,int i2){
    if(seg[i1].l==seg[i2].l || seg[i1].l==seg[i2].r) return false;
    if(seg[i1].r==seg[i2].l || seg[i1].r==seg[i2].r) return false;
     return (within(seg[i2].l,seg[i2].r,seg[i1].l)!=within(seg[i2].l,seg[i2].r,seg[i1].r));
}

const int N = 2*(int)1000+100;     //点数*2
int n,m;
struct SE{
    int l,r;
    SE(){}
    SE(int _l,int _r){
        l=_l;
        r=_r;
    }
}seg[N];
int scc, top, tot;
vector<int> G[N];
int low[N], dfn[N], belong[N];
int stk[N], vis[N];
void init(int n) {
    for (int i = 0; i <= 2*n; ++i) {
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
        } else if (vis[to]) low[x] = min(low[x], dfn[to]);
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
void twoSat(int n) {
    for (int i=0; i<2*n; ++i) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i=0; i<2*n; i+=2) {
        if (belong[i] == belong[i^1]) {
            cout<<"Impossible"<<'\n';
            return;
        }
    }
    for (int i = 0; i < 2*n; i+=2) {   //因为强连通用了栈，所以强连通编号是反拓扑序
        if (belong[i] > belong[i^1]) { //false->true 也就是只能为真
            cout<<'i';
        } else cout<<'o';
    }
    cout<<'\n';
}
void addEdge(int a, int b) { //建双向边
    G[a].emplace_back(b);
    G[b].emplace_back(a);
}
bool within(int x,int y,int z){
    return (x<z && z<y);
}
bool intersect(int i1,int i2){
    if(seg[i1].l==seg[i2].l || seg[i1].l==seg[i2].r) return false;
    if(seg[i1].r==seg[i2].l || seg[i1].r==seg[i2].r) return false;
     return (within(seg[i2].l,seg[i2].r,seg[i1].l)!=within(seg[i2].l,seg[i2].r,seg[i1].r));
}
int main() {
    cin>>n>>m;
    forn(i, m){
        int u,v;
        cin>>u>>v;
        if(u>v) swap(u,v);
        seg[i]=SE(u,v);
    }
    init(1000);
    for(int i=0; i<m; ++i){
        for(int j=i+1; j<m; ++j){
            if(intersect(i,j)){
                addEdge(i*2,(j*2)^1);
                addEdge(j*2,(i*2)^1);
            }
        }
    }
    twoSat(m);
    return 0;
}
