/*KM by lbn O(n^3)
UOJ80 左nl 右nr 二分图最大权匹配
给定每两个点间权值，求一个匹配使权值和最大，不存在的边权开成 ?1，时间复杂度 O(n^3)。
用法：两个点间权值 wi;j， lxi 和 lyi 为顶标，随时满足 lxi + lyi ≥ wi;j， lki 为右部第 i 个点匹配的左部点。如果要求最小值全部取反即可。
#define INF 1e9 不存在的边权开到-n*(|maxv|+1),inf为3n*(|maxv|+1) （点数 最大边权）
lx左，ly右
点从1~n编号*/

#define ll long long

const int N = 410;   //二分图某一边的最大点数
const int INF = 0x3f3f3f3f;
int lx[N],ly[N],w[N][N],lk[N],slk[N],pre[N],vy[N],
    py,d,p;
int nl, nr, m, n, x, y, z;

int main() {

    /*初始化别忘了*/
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(lk, 0, sizeof(lk));
    memset(w, 0, sizeof(w));
    cin >> nl >> nr >> m;
    /*二分图的大小*/
    n = max(nl,nr);

    /* 负权图初始化要加 hdu2813 */
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) w[i][j] = -INF;
        ly[i] = -INF;
    }
    /* -----------------------*/

    for (int i = 1; i <= m; ++i)
    {
        cin >> x >> y >> z;
        w[y][x]=z;  //注意是[y][x]!!  负权的话z是负数！相应的最后的ans也是负数！
        lx[y]=max(lx[y],z); //负权可以不写？但我一直写的
    }
    /*  -----------KM----------  */
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j) slk[j]=INF,vy[j]=0;
        for(lk[py=0]=i;lk[py];py=p)
        {
            vy[py]=1; d=INF; x=lk[py];
            for (int y = 1; y <= n; ++y) {
             if(!vy[y])
             {
                 if(lx[x]+ly[y]-w[x][y]<slk[y]) slk[y]=lx[x]+ly[y]-w[x][y],pre[y]=py;
                 if(slk[y]<d) d=slk[y],p=y;
             }
            }
            for (int y = 0; y <= n; ++y) {
             if(vy[y]) lx[lk[y]]-=d,ly[y]+=d;
              else slk[y]-=d;
            }

        }
        for(;py;py=pre[py]) lk[py]=lk[pre[py]];
    }
    ll ans = 0;
    正权 :  for (int i = 1; i <= n; ++i) ans+=lx[i]+ly[i];
    负权 :  for (int i = 1; i <= n; ++i) if (w[lk[i]][i] != -INF) ans+=w[lk[i]][i];
    printf("%lld\n",ans);
    for (int i = 1; i <= nl; ++i) {
     if(w[lk[i]][i]) printf("%d ",lk[i]);
      else printf("0 ");
    }
	puts("");
        //输出方案
      /*----------------------------------*/
    return 0;
}
