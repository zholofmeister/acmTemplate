UVA 11930
题意：
给你n个矩形，每个矩形给你四个顶点(无序,所以要先排序),现在要求每个矩形都要选一个对角线，使得这些对角线都不相交。如果存在解的话就YES,不然NO。
1000ms n<=1000, -1e9<=xi,yi<=1e9
思路：
预处理出2*n条对角线，然后遍历。
1. 同一个矩形的对角线continue,
2. i与j不相交,i与j^1相交  -> 选i一定选j         ->i向j连边。
3. i与j相交,i与j^1不相交  -> 不可能选i,只能选i^1 -> i向i^1连边
sgn和叉积那边要开ll(490ms) or 直接#define int long long(430ms 还快一点??)

const int N=(int)1e5;
int scc, top, tot;
vector<int> G[N];
int low[N], dfn[N], belong[N];
int stk[N], vis[N];
void init(int n) {
    for (int i = 0; i <= 2*n; ++i) {
        G[i].clear();
        low[i] = 0;
        dfn[i] = 0;
        stk[i] = 0;
        vis[i] = 0;
    }
    scc = top = tot = 0;
}
void tarjan(int x) {
    stk[top++] = x;
    low[x] = dfn[x] = ++tot;
    vis[x] = 1;
    for (int to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to]) low[x] = min(low[x], dfn[to]);
    }
    if (low[x] == dfn[x]) {
        ++scc;
        int temp;
        do {
            temp = stk[--top];
            belong[temp] = scc;
            vis[temp] = 0;
        } while (temp != x);
    }
}
void twoSat(int n) {
    for (int i=0; i<2*n; ++i) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i=0; i<2*n; i+=2) {
        if (belong[i] == belong[i^1]) {
            cout<<"NO"<<'\n';
            return;
        }
    }
    cout<<"YES"<<'\n';
}
void addEdge(int a, int b) {
    G[a].emplace_back(b);
}
int n,x11,y11,x22,y22,x33,y33,x44,y44;
int sgn(i64 x){
    if(x==0LL) return 0;
    if(x>0LL) return 1;
    else return -1;
}
struct Point{
    i64 x,y;
    Point(){}
    Point(i64 _x,i64 _y){
        x=_x;
        y=_y;
    }
    bool operator < (Point b) const{
        return x==b.x?y<b.y:x<b.x;
    }
    Point operator - (const Point &b) const{
        return Point(x-b.x,y-b.y);
    }
    i64 operator * (const Point &b) const{
        return (x*b.x+y*b.y);
    }
    i64 operator ^ (const Point &b) const{
        return (x*b.y-y*b.x);
    }
};
struct Line{
    Point s,e;
    Line() {}
    Line(Point _s,Point _e){
        s=_s;
        e=_e;
    }
    int segcrossseg(Line v){
        int d1=sgn((e-s)^(v.s-s));
        int d2=sgn((e-s)^(v.e-s));
        int d3=sgn((v.e-v.s)^(s-v.s));
        int d4=sgn((v.e-v.s)^(e-v.s));
        if((d1^d2)==-2 && (d3^d4)==-2) return 2;
        return (d1==0 && sgn((v.s-s)*(v.s-e))<=0) ||
        (d2==0 && sgn((v.e-s)*(v.e-e))<=0) ||
        (d3==0 && sgn((s-v.s)*(s-v.e))<=0) ||
        (d4==0 && sgn((e-v.s)*(e-v.e))<=0);
    }
}l[N];
signed main() {
    while(cin>>n){
        if(!n) break;
        int tot=0;
        forn(i, n){
            vector<Point> temp;
            temp.clear();
            i64 a11,b11,a22,b22,a33,b33,a44,b44;
            cin>>a11>>b11>>a22>>b22>>a33>>b33>>a44>>b44;
            temp.eb(Point(a11,b11));
            temp.eb(Point(a22,b22));
            temp.eb(Point(a33,b33));
            temp.eb(Point(a44,b44));
            sort(all(temp));
            x11=temp[0].x; y11=temp[0].y;
            x22=temp[1].x; y22=temp[1].y;
            x33=temp[3].x; y33=temp[3].y;
            x44=temp[2].x; y44=temp[2].y;
            l[tot++]=Line(Point(x11,y11),Point(x33,y33));
            l[tot++]=Line(Point(x22,y22),Point(x44,y44));
        }
        init(2*n);
        for(int i=0; i<tot; ++i){
            for(int j=0; j<tot; ++j){
                if((i/2)==(j/2)) continue;
                if(l[i].segcrossseg(l[j])==0 && l[i].segcrossseg(l[j^1])!=0){
                    addEdge(i,j);
                }
                if(j%2==0 && l[i].segcrossseg(l[j])!=0 && l[i].segcrossseg(l[j^1])!=0){
                    addEdge(i,i^1);
                }
            }
        }
        twoSat(n);
    }
    return 0;
}