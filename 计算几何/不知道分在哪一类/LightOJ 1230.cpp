LightOJ 1230
题意：
t组数据，每次给你n个条，以及一个矩形的右上角坐标，左下角坐标是(0,0),保证这n条线两两不重合，现在问你依次添加这n条边，最后分成了多少块区域。
t<=100, 0<=n<=100, 5<=L,W<=100(矩形右上角), x1,y1,x2,y2都在矩形的边界上
思路：
每次加线时开始遍历之前加过线，和他们求交点，如果交点是端点或没有端点就对答案贡献+1,有交点就把交点放set里面，最后最答案的贡献就是SZ(set)+1。

const double eps=1e-8;
const int N=200;
int sgn(double x){
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    return 1;
}
struct vec{
    double x,y;
    vec(double _x=0,double _y=0){x=_x;y=_y;}

    vec operator * (double v) {return vec(x*v,y*v);}
    vec operator / (double v) {return vec(x/v,y/v);}
    vec operator + (vec v)    {return vec(x+v.x,y+v.y);}
    vec operator - (vec v)    {return vec(x-v.x,y-v.y);}

    double operator * (vec v)    {return x*v.x+y*v.y;}
}p11[N],p22[N];
double cross(vec a,vec b) {return a.x*b.y-a.y*b.x;}
bool point_on_segment(vec p,vec a,vec b){
    return sgn( cross(b-a,p-a) ) == 0 && sgn( (p-a)*(p-b) ) <= 0;
}
//判断线段ab,pq间是否有交点
int has_intersection(vec a,vec b,vec p,vec q){
    int d1 = sgn( cross(b-a,p-a) ),d2 = sgn( cross(b-a,q-a) );
    int d3 = sgn( cross(q-p,a-p) ),d4 = sgn( cross(q-p,b-p) );
    if( d1 * d2 < 0 && d3 * d4 < 0) return 1;//有交点，且交点不在端点
    if( ( d1 == 0 && point_on_segment(p,a,b) )||
       ( d2 == 0 && point_on_segment(q,a,b) ) ||
       ( d3 == 0 && point_on_segment(a,p,q) ) ||
       ( d4 == 0 && point_on_segment(b,p,q) ))
        return -1; //重合或交点在端点上
    return 0;
}
//直线求交点,需保证p!=a,a!=b
int line_intersection(vec a,vec b,vec p,vec q,vec &o,double *t=0){
    double U=cross(p-a,q-p);
    double D=cross(b-a,q-p);
    if(sgn(D) == 0) return sgn(U)==0 ? 2 : 0; //重叠|平行
    o = a + (b-a) * (U/D);
    if(t) *t = U/D;
    return 1;
}

int main() {
    int tc,n,kase=1;
    double l,w;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d%lf%lf",&n,&l,&w);
        int ans=1;
        forn(i, n){
            scanf("%lf%lf%lf%lf",&p11[i].x,&p11[i].y,&p22[i].x,&p22[i].y);
            int res=1;
            set< pair<double,double> > st;
            for(int j=0; j<i; ++j){
                int outcome=has_intersection(p11[i],p22[i],p11[j],p22[j]);
                if(!outcome) continue;    //没交点 贡献为1
                if(outcome==-1) continue; //交点是端点 贡献为1
                vec tmp;
                line_intersection(p11[i],p22[i],p11[j],p22[j],tmp);
                st.insert(mp(tmp.x,tmp.y));
            }
            ans+=SZ(st)+1;
        }
        printf("Case %d: %d\n",kase++,ans);
    }
    return 0;
}
