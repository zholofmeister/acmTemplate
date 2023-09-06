//洛谷 P4782
//从0开始的偶数为false，从1开始的奇数为true
//O(n+m)
const int N = 2*(int)EDIT+100;     //点数*2
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
            cout<<"IMPOSSIBLE"<<'\n';
            return;
        }
    }
    cout<<"POSSIBLE"<<'\n';
    for (int i = 0; i < 2*n; i+=2) {   //因为强连通用了栈，所以强连通编号是反拓扑序
        if (belong[i] > belong[i^1]) { //false->true 也就是只能为真
            cout<<1<<' ';
        } else cout<<0<<' ';
    }
    cout<<'\n';
}
void addEdge(int a, int b) {
    G[a].emplace_back(b);
}

int n,m,a,ai,b,bi;
int main() {
    cin>>n>>m;
    init(n+5);
    for(int i=0; i<m; ++i){
        cin>>a>>ai>>b>>bi;
        --a;--b;
        a*=2;b*=2; //*2!!
        if(ai==0 && bi==0){
            addEdge(a^1,b);
            addEdge(b^1,a);
        } else if(ai==0 && bi==1){
            addEdge(a^1,b^1);
            addEdge(b,a);
        } else if(ai==1 && bi==0){
            addEdge(a,b);
            addEdge(b^1,a^1);
        } else{
            addEdge(a,b^1);
            addEdge(b,a^1);
        }
    }
    twoSat(n);
    return 0;
}

