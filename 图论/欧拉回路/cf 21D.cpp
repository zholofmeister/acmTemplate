cf 21D
题意：
给你n个点m条边的无向图，求从点1开始经过每条边至少一次最后回到点1的最小路程。
就是找** 一条路径可重复的欧拉回路 **。
input:
cin>>n>>m;
for(int i=0; i<m; ++i) cin>>x>>y>>z;
n是点数(这个图点的编号1~n)，m是边数，x,y,z表示x和y之间有一条长度为z的无向边
1<=n<=15,0<=m<=2000,1<=x,y<=n,1<=w<=10000
思路：
首先对于欧拉回路：所有点的度数都为偶数。因为所有点至少经过一次，那么可以把题意转换成最少加多少条边使得图满足以上结论。
而加边的目的是为了把奇度数转化为偶度数，先floyd一下得到全源最短路。dp[i]表示状态i下度数为偶数的最小花费，因为n<=15,想到状压dp，挑两个奇度数的点转移即可。详情可见代码。

const int N=100;
const int INF=0x3f3f3f3f;
int n,m,x,y,w,dis[N][N],deg[N],dp[(1<<20)];
int main() {
    cin>>n>>m;
    for(int i=0; i<=n+5; ++i){
        deg[i]=0;
        for(int j=0; j<=n+5; ++j) dis[i][j]=INF;
    }
    int sum=0;
    for(int i=0; i<m; ++i){
        cin>>x>>y>>w;
        uin(dis[x][y],w);
        uin(dis[y][x],w);
        ++deg[x]; ++deg[y];
        sum+=w;
    }
    for(int k=1; k<=n; ++k) for(int i=1; i<=n; ++i) for(int j=1; j<=n; ++j) uin(dis[i][j],dis[i][k]+dis[k][j]);
    for(int i=2; i<=n; ++i){
        if(deg[i]>0 && dis[i][1]==INF){ //条件一定要有deg[i]>0,因为这题要求的是经过所有边,不是所有点。
            cout<<-1<<'\n';
            return 0;
        }
    }
    int now=0;
    for(int i=1; i<=n; ++i) if(deg[i]&1) now|=(1<<(i-1));
    for(int i=0; i<now+10; ++i) dp[i]=INF;
    dp[now]=0;
    int ans=INT_MAX;
    for(int i=now; i>0; --i){
        for(int j=1; j<=n; ++j){
            if(i&(1<<(j-1))){
                for(int k=j+1; k<=n; ++k){
                    if(i&(1<<(k-1))){
                        uin(dp[i^(1<<(j-1))^(1<<(k-1))],dp[i]+dis[j][k]);
                    }
                }
            }
        }
    }
    cout<<sum+dp[0]<<'\n';
    return 0;
}
