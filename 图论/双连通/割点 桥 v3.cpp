const int N=(int)1e4+100;
int n,m;
vector<int> E[N],sccv[N];
struct BCC {
    int n, bcc, top, top2, tot, cntCut, sccIdx; //sccIdx:点双联通分量编号
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N], val[N], sz[N];
    //val[i]表示i点tarjan出去多少个**多的(懂得都懂)**点
    //sz[i]表示编号为i的点双里有多少条边
    int stk[N],stk2[N];
    int cut[N], final_block[N]; //final_block[i]表示割掉i以后图中有几个连通块
    int cntBlock; //一开始有几个连通块

    void dfs(int x, int pre) {
        stk[top++]=x; stk2[top2++]=x;
        low[x]=dfn[x]=++tot;
        fa[x]=pre;
        int son=0;
        for (int to:G[x]) {
            if (to==pre) continue;
            if (!dfn[to]) {
                ++son;
                dfs(to, x);
                low[x]=min(low[x],low[to]);
                if (x!=pre && low[to]>=dfn[x]) {
                	++cntCut;
                    cut[x]= 1;
                    final_block[x]++;
                }
                if(low[to]>=dfn[x]){
                    int temp;
                    ++sccIdx;
                    sccv[sccIdx].clear();
                    sz[sccIdx]=0;//记录当前点双里面的边数
                    do{ //记录当前点双里面的点
                        temp=stk[--top];
                        sccv[sccIdx].eb(temp);
                        sz[sccIdx]+=val[temp];
                    }while(temp!=to);
                    sccv[sccIdx].eb(x);
                    sz[sccIdx]+=int(sccv[sccIdx].size())-1;
                }
                if (low[to]>dfn[x]) bridge.emplace_back(make_pair(x, to));
            } else if(dfn[to]<dfn[x]){
                low[x]=min(low[x],dfn[to]);
                ++val[x]; //注意这里，用于后面处理点双连通里面有多少边
            }
        }
        if (x==pre) {
            final_block[x]=son-1;
            if(son>1){
            	++cntCut;
                cut[x]=1;//gym 102835
            }
        }
        if(low[x] == dfn[x]){
            ++bcc;
            int temp;
            do{
                temp=stk2[--top2];
                belong[temp]=bcc;
            }while(temp!=x);
        }
    }
    void solve(int _n, vector<int> E[]) {
        n=_n;
        for (int i=1; i<=n; ++i) {
            val[i]=sz[i]=0; //:)
            belong[i]=0;
            G[i]=E[i];
            low[i]=dfn[i]=stk[i]=fa[i] = 0;
            cut[i]=final_block[i]=0;
        }
        bcc=top=top2=tot=cntBlock=cntCut=sccIdx=0;
        bridge.clear();
        for (int i=1; i<=n; ++i){
            if (!dfn[i]){
                ++cntBlock;
                dfs(i, i);
            }
        }
        for(int i=1; i<=n; ++i) final_block[i]+=cntBlock;
    }
    void rebuild(vector<int> E[]) {
        for (int i=1; i<=n; ++i) E[i].clear();
        for (int i=1; i<=n; ++i){
            int t=fa[i];
            if (belong[i]!=belong[t]) {
                E[belong[i]].emplace_back(belong[t]);
                E[belong[t]].emplace_back(belong[i]);
            }
        }
    }
}bcc;
int main() {
    scanf("%d",&tc);
    while(tc--){
    	scanf("%d%d",&n,&m);
    	for(int i=0; i<=n+5; ++i){
    		E[i].clear();
    		sccv[i].clear();
    	}
    	forn(i, m){
    		int u,v;
    		scanf("%d%d",&u,&v);
    		++u; ++v; //如果下标从0开始计数的话
    		E[u].eb(v);
    		E[v].eb(u);
    	}
    	bcc.solve(n,E);
    }
    return 0;
}