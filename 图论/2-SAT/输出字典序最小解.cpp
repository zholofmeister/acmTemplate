// hdu 1814
1<=n<=8000,0<=m<=20000,1<=a<b<=2n
// O(N*(N+M))
// 有1~2*n个人，第i个和第i+1个是同一对的，现在有m对不喜欢关系，现在要每个队选一个人出来，相互之间不会不喜欢，问最小字典序解。
// 从0开始的偶数为false，从1开始的奇数为true
const int N=2*EDIT+100;
vector< vector<int> > G(N);
int n,m;
bool vis[N];     //染色标记，true表示选择
int stk[N],top;  //栈
void init(int n){
    for(int i=0; i<=2*n; ++i){
		vis[i]=false;
		G[i].clear();
	}
}
void addEdge(int u,int v){
    G[u].emplace_back(v);
}
bool dfs(int now){
    if(vis[now^1]) return false;
    if(vis[now]) return true;
    vis[now]=true;
    stk[top++]=now;
    for(int to:G[now]){
        if(!dfs(to)) return false;
    }
    return true;
}
bool twoSat(int n){
  //  memset(vis,false,sizeof(vis));
    for(int i=0; i<2*n; i+=2){
        if(vis[i] || vis[i^1]) continue;
        top=0;
        if(!dfs(i)){
            while(top){
                vis[stk[--top]]=false;
            }
            if(!dfs(i^1)) return false;
        }
    }
    return true;
}
int main() {
    while(cin>>n>>m){
        init(n);      //多组数据要清空
        for(int i=0; i<m; ++i){
            int u,v;
            cin>>u>>v;
            --u; --v;
            addEdge(u,v^1);
            addEdge(v,u^1);
        }
        if(twoSat(n)){
            for(int i=0; i<2*n; ++i) if(vis[i]) cout<<i+1<<'\n';
        } else{
            cout<<"NIE"<<'\n';
        }
    }
    return 0;
}
