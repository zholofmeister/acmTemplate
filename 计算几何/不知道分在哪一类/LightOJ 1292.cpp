sol1:
const double eps=1e-8;
int sgn(double x){
    if(fabs(x) < eps) return 0;
	if(x < 0) return -1;
	return 1;
}
const int N=710;
int tc,n,m,vis[N][N];
struct vec{
    double x,y;
    vec(double _x=0,double _y=0){x=_x,y=_y;}
    vec operator + (vec v) {return vec(x+v.x,y+v.y);}
    vec operator - (vec v) {return vec(x-v.x,y-v.y);}
    vec operator * (double v) {return vec(x*v,y*v);}
    vec operator / (double v) {return vec(x/v,y/v);}

    double len() {return hypot(x,y);}
    double operator * (vec v) {return x*v.x+y*v.y;}
}po[1000];
double cross(vec a,vec b) {return a.x*b.y - a.y*b.x;}
int main() {
    int kase=1;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        forn(i, n){
            int tx,ty;
            scanf("%d%d",&tx,&ty);
            po[i]=vec(tx,ty);
        }
        int ans;
        if(n<3){
            printf("Case %d: %d\n",kase++,n);
            continue;
        }

        ms(vis,0);
        ans=0;
        for(int i=0; i<n; ++i){
            for(int j=i+1; j<n; ++j){
                if(vis[i][j]) continue;
                int res=2;
                for(int k=j+1; k<n; ++k){
                    if(!sgn(cross(po[i]-po[k],po[j]-po[k]))){
                        ++res;
                        vis[k][i]=vis[k][j]=1;
                        vis[i][j]=vis[i][k]=1;
                        vis[j][i]=vis[j][k]=1;
                    }
                }
                uax(ans,res);
            }
        }
        printf("Case %d: %d\n",kase++,ans);
    }
    return 0;
}

sol2:
const int N=710;
int tc,n,m,vis[N][N];
struct vec{
    double x,y;
    vec(double _x=0,double _y=0){x=_x,y=_y;}
}po[1000];
int main() {
    int kase=1;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        map< pair<int,int>,int > cnt;
        forn(i, n){
            scanf("%lf%lf",&po[i],&po[i].y);
        }
        if(n<3){
            printf("Case %d: %d\n",kase++,n);
            continue;
        }
        int ans=0;
        for(int i=0; i<n; ++i){
            cnt.clear();
            for(int j=0; j<n; ++j){
                if(i==j) continue;
                int ty=po[j].y-po[i].y;
                int tx=po[j].x-po[i].x;
                if(tx<0) {tx=-tx; ty=-ty;}
                int tgcd=__gcd(abs(tx),abs(ty));
                tx/=tgcd; ty/=tgcd;
                ++cnt[mp(tx,ty)];
                uax(ans,cnt[mp(tx,ty)]+1);
            }
        }
        printf("Case %d: %d\n",kase++,ans);
    }
    return 0;
}
