bzoj 1443 JSOI2009 
题意：
有一个(100*100)的矩形，现在矩形格子里的点有两种状态，一种是可以走，还有一种是不能走，现在yy先手，mm后手，问这个矩形中有哪些点让yy先手，结果是mm赢。
思路：
看清题意，规定yy先手，问你的是哪些点mm赢，也就是yy输。
yy输就是要找最大匹配的非必要点，所以这题就转化为了找出所有二分图最大匹配的非必要点。

const int N=(int)1e4+100;
vvi G(N);
int n,m,lk[N],vis[N],idx[110][110],dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
int chk[N]; //判断某个点是否为最大匹配的非必要点
int visNum=0; //用在匈牙利里判断这次找增光路时有没有访问过，不用每次初始化vis数组,实验证明也没快多少..快了100ms以内
char mat[110][110];
bool gao(int x){  //匈牙利
    for(int to:G[x]){
        if(vis[to]!=visNum){
            vis[to]=visNum;
            if(lk[to]==-1 || gao(lk[to])){
                lk[x]=to;
                lk[to]=x;
                return true;
            }
        }
    }
    return false;
}
void dfs(int x){ //找出哪些点不是最大匹配的必要点
    chk[x]=1;
    for(int to:G[x]){
       if(!chk[lk[to]]){//注意是lk[to]
            dfs(lk[to]);
       }
    }
}
int main() {
    ms(lk,-1); ms(idx,0); ms(chk,0);
    cin>>n>>m;
    int tot=0;//二分图中点的下标计数
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            cin>>mat[i][j];
            if(mat[i][j]=='.') idx[i][j]=++tot;
        }
    }
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            if(mat[i][j]!='.') continue;
            for(int k=0; k<4; ++k){
                int tx=i+dir[k][0];
                int ty=j+dir[k][1];
                if(tx<1 || tx>n || ty<1 || ty>m || mat[tx][ty]!='.') continue;
                G[idx[i][j]].eb(idx[tx][ty]);
                G[idx[tx][ty]].eb(idx[i][j]);
            }
        }
    }
    int hungary=0;
    for1(i, tot){
        ++visNum;
        if(lk[i]==-1 && gao(i)) ++hungary;
    }
    if(hungary*2==tot){
        cout<<"LOSE"<<'\n';
        return 0;
    }
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            //没被匹配并且没被确定不是必要点的那些点
            if(mat[i][j]=='.' && lk[idx[i][j]]==-1 && !chk[idx[i][j]]){
                dfs(idx[i][j]);
            }
        }
    }
    cout<<"WIN"<<'\n';
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            if(mat[i][j]=='.' && chk[idx[i][j]]){
                cout<<i<<' '<<j<<'\n';
            }
        }
    }
    return 0;
}