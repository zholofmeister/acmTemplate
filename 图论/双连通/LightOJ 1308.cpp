LightOJ 1308 割点+分类讨论
题意：
t组数据，每组数据给你一个n和一个m，表示有n个点和m条双向边，保证原图没有重边，没有自环，连通。现在规定要炸一个点，被炸以后每个点都要往地表冲，现在问你至少要加多少通往地表的通道，能达成无论炸什么点，所有点都有通往地表的通道。让你输出最少加的通道数和在加最少通道数这个前提下的方案数。
t<=30, 2<=n<=10000, 0<=m<=20000, 0<=u,v<n
思路：
如果原图没有割点，那就最少要加两条通道，如果被炸了一个点还可以走另一个点，方案数是Cn2 = n*(n-1)/2。
如果有割点，就开始O(n)走完每个点连通分量，如果一个点双里面有 >1 的割点那就不用加通道，因为如果炸了一边还有另一边可以走，所以对答案没贡献。如果一个点双里面只有一个割点，设这个点双里面除了割点有num个点，那就最少要加的通道+1,方案数*num。
坑点/技巧：
结果要求对 2^64 取模，其实就是要求结果开unsigned long long, 输出%llu。
用set存一个连通分量里的割点。

const int N=(int)1e4+100;
int tc,ans,vis[N];
int n,m;
i64 num;
set<int> meet_cut;
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
void dfs(int x){
	vis[x]=1;
	++num;
	for(int to:E[x]){
		if(bcc.cut[to]){
			meet_cut.insert(to);
			continue;
		}
		if(vis[to]) continue;
		
		dfs(to); 
	}
}
int main() {
    scanf("%d",&tc);
    int kase=1;
    while(tc--){
    	ans=1;
    	scanf("%d%d",&n,&m);
    	for(int i=0; i<=n+5; ++i){
    		E[i].clear();
    		sccv[i].clear();
    		vis[i]=0;
    	}
    	forn(i, m){
    		int u,v;
    		scanf("%d%d",&u,&v);
    		++u; ++v;
    		E[u].eb(v);
    		E[v].eb(u);
    	}
    	bcc.solve(n,E);
    	int cnt_shaft=0;
    	unsigned long long ans=1;
    	if(!bcc.cntCut){
    		printf("Case %d: %d %d\n",kase++,2,n*(n-1)/2);
    	} else{ 		
    		for1(i, n){
    			if(vis[i] || bcc.cut[i]) continue;
    			num=0;
    			meet_cut.clear();
    			dfs(i);
    			if(SZ(meet_cut)==1){
    				ans=ans*num;
    				++cnt_shaft;
    			}
    		}
    		printf("Case %d: %d %llu\n",kase++,cnt_shaft,ans);
    	}
    }
    return 0;
}