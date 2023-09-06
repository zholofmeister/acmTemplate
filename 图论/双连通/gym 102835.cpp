The 2020 ICPC Asia Taipei-Hsinchu Site Programming Contest
cf gym 102835 
problem I Critical Structures
题意：
给你一个n个点，m条边的无向图，保证没有自环和重边，现在让你求四个值。
割点数目，桥数目，点双连通分量数目(设这个值为a),包含最多边的点双的边数(设这个值为b)，a和b要除以他们的gcd
思路：
tarjan，主要是求点双连通分量数目,包含最多边的点双的边数这两个之前没做过，更新了一波bcc模板，详情见代码
3<=n<=1000, n-1<=m<=n*(n-1)/2


const int N=(int)1e3+100;
vector<int> E[N],sccv[N];
int n,m;
struct BCC {
    int n, bcc, top, tot, cntCut, sccIdx; //sccIdx:点双联通分量编号
    vector<int> G[N];
    vector< pair<int, int> > bridge;
    int low[N], dfn[N], belong[N], fa[N], val[N], sz[N];
    //val[i]表示i点tarjan出去多少个点
    //sz[i]表示编号为i的点双里有多少条边
    int stk[N];
    int cut[N], final_block[N]; //final_block[i]表示割掉i以后图中有几个连通块
    int cntBlock; //一开始有几个连通块

    void dfs(int x, int pre) {
        stk[top++]=x;
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
                        sz[sccIdx]+=val[temp];    //操作1
                    }while(temp!=to);
                    sccv[sccIdx].eb(x);
                    sz[sccIdx]+=int(sccv[sccIdx].size())-1; //操作2
                }
                if (low[to]>dfn[x]) bridge.emplace_back(make_pair(x, to));
            } else if(dfn[to]<dfn[x]){
                low[x]=min(low[x],dfn[to]);
                ++val[x]; //注意这里，用于后面处理点双连通里面有多少边
				//val[x]用来储存x节点除了一个儿子还有多少个儿子
            }
        }
        if (x==pre) {
            final_block[x]=son-1;
            if(son>1){
                cut[x]=1;//gym 102835
            }
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
        bcc=top=tot=cntBlock=cntCut=sccIdx=0;
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
    int tc;
    cin>>tc;
    while(tc--){
        cin>>n>>m;
        for(int i=0; i<=n; ++i){
            E[i].clear();
            sccv[i].clear();//?
        }
        forn(i, m){
            int a,b;
            cin>>a>>b;
            E[a].eb(b);
            E[b].eb(a);
        }
        bcc.solve(n,E);
        for1(i, n) if(bcc.cut[i]) bcc.cntCut++;
        cout<<bcc.cntCut<<' '<<int(bcc.bridge.size())<<' ';
        int bb=-1; //最多边的那个点双的边数
        for(int i=1; i<=bcc.sccIdx; ++i) bb=max(bb, bcc.sz[i]);
        int aa=bcc.sccIdx; //有几个点双
        int temp=__gcd(aa,bb);
        aa/=temp;
        bb/=temp;
        cout<<aa<<' '<<bb<<'\n';
    }
    return 0;
}
