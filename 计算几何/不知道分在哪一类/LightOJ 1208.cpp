题目：
给你n个pair<点，点>，表示某个pair里这两个点可以连边，代价是长度*2,现在给你一头野猪的坐标，问你能不能用最小花费把野猪围起来，并且围栏是一个凸多边形，如果可以就输出最小花费，不可以就输出-1。
t<=125,1<=n<=100,-1e4<=x,y<=1e4
思路：
先处理输出边，让野猪在边的右边，然后n^2建边，然后floyd。

const int N=1000;
double mat[N][N];
int tc,n,x,y;
double l[N],dp[N][N];
struct vec{
    int x,y;
    vec(int _x=0,int _y=0){x=_x,y=_y;}
    vec operator - (vec v) {return vec(x-v.x,y-v.y);}
};
struct node{
    int ix1,iy1,ix2,iy2;
}nd[N];
map< pii,vector<int> > G;
double len(vec v){return hypot(v.x,v.y);}
int cross(vec a,vec b,vec c){return (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x);}
bool is_right(vec a,vec b,vec c){return cross(a,b,c)>=0;}
int main() {
    int kase=1;
    scanf("%d",&tc);
    while(tc--){
        G.clear();
        scanf("%d%d%d",&n,&x,&y);
        for(int i=0; i<=n; ++i)
            for(int j=0; j<=n; ++j)
                dp[i][j]=1e9;
        forn(i, n){
            scanf("%d%d%d%d",&nd[i].ix1,&nd[i].iy1,&nd[i].ix2,&nd[i].iy2);
            if(!is_right(vec(x,y),vec(nd[i].ix2,nd[i].iy2),vec(nd[i].ix1,nd[i].iy1))){
                swap(nd[i].ix1,nd[i].ix2);
                swap(nd[i].iy1,nd[i].iy2);
            }
            G[mp(nd[i].ix1,nd[i].iy1)].eb(i);
            l[i]=len(vec(nd[i].ix2-nd[i].ix1,nd[i].iy2-nd[i].iy1));
        }
        for(int i=0; i<n; ++i){
            for(int j:G[mp(nd[i].ix2,nd[i].iy2)]){
                if(is_right(vec(nd[j].ix2,nd[j].iy2),vec(nd[i].ix2,nd[i].iy2),vec(nd[i].ix1,nd[i].iy1))){ //因为最后围成的是一个凸多边形
                    dp[i][j]=l[i]+l[j];
                }
            }
        }
        for(int k=0; k<n; ++k){
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    uin(dp[i][j],dp[i][k]+dp[k][j]);
                }
            }
        }
        printf("Case %d: ",kase++);
        double ans=1e9;
        forn(i, n) uin(ans,dp[i][i]);
        if(ans==1e9) puts("-1");
        else printf("%.7f\n",ans);
    }
    return 0;
}
