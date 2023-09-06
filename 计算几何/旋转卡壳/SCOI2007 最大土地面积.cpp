1. SCOI 2007 最大土地面积 / cf gym102460 L
//给你n个点，让你取四个点形成一个四边形，问最大的四边形面积是多少？
//凸包后枚举对锺点O(n^2)，然后旋转卡壳，因为是在枚举对锺点里面卡壳，所以卡壳的复杂度是O(1),总复杂度O(n^2)
//n=2000, x,y是double，x,y<=1e5  0.2s
#define i64 long long
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 40100;
int n;
//Compares a double to zero
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    else return 1;
}
struct Point {
    double x, y;
    int idx;
    Point() {}
    Point(double _x, double _y, int _idx) {
        x = _x;
        y = _y;
        idx = _idx;
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    void output() {
        printf("%.8f %.8f\n", x, y);
    }
    bool operator == (Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (Point b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y, idx - b.idx);
    }
    //点积
    double operator * (const Point &b) const {
        return x * b.x + y * b.y;
    }
    //叉积
    double operator ^ (const Point &b) const {
        return x * b.y - y * b.x;
    }
    //返回两点的距离
    double distance(Point p) {
        return hypot(x - p.x, y - p.y);
    }
}fp;
struct polygon{
    int n;
    Point p[maxp];
    void input(int _n){
        n=_n;
        for(int i=0; i<n; ++i){
            p[i].input();
            p[i].idx=i;
        }
    }
    void add(Point q){
        p[n++]=q;
    }
    struct cmp{
        Point p;
        cmp(const Point &p0){p=p0;}
        bool operator()(const Point &aa,const Point &bb){
            Point a=aa,b=bb;
            int d=sgn((a-p)^(b-p));
            if(d==0){
                return sgn(a.distance(p)-b.distance(p))<0;
            }
            return d>0;
        }
    };
    //进行极角排序
    //首先需要找到最左下角的点
    //需要重载号好Point的<操作符（min函数要用）
    void norm(){
        Point mi=p[0];
        for(int i=1;i<n;++i) mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    //得到凸包
    //得到凸包里面的点编号是0~n-1的
    //两种凸包的方法
    //注意如果有影响，要特判下所有点共点，或者共线的特殊情况
    //测试 LightOJ1203 Light1239
    void getconvex(polygon &convex){
        sort(p,p+n);
        convex.n=n;
        for(int i=0; i<min(n,2); ++i) convex.p[i]=p[i];
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--; //特判
        if(n<=2) return;
        int &top=convex.n;
        top=1;
        for(int i=2; i<n; ++i){
            while(top && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) --top;
            convex.p[++top]=p[i];
        }
        int temp=top;
        convex.p[++top]=p[n-2];
        for(int i=n-3; i>=0; --i){
            while(top!=temp && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) top--;
            convex.p[++top]=p[i];
        }
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--;//特判
        convex.norm(); //原来的得到的是顺时针的点，排序后逆时针。
    }
    bool OK(Point a,Point b,Point c,Point d)
    {
        double A=fabs((b-a)^(c-a));
        double B=fabs((b-a)^(d-a));
        return A<B;
    }
    void Rotating_Calipers(polygon &plo)
    {
        double ans=0,now;
        if (n<=2) ans=0;
        else if (n==3)
        {
            now=~(1LL<<63); //LLONG_MAX
            ans=abs((p[0]-p[2])^(p[1]-p[2]));
            for (int i=0;i<plo.n;i++)
            {
                if (p[0].idx==plo.p[i].idx || p[1].idx==plo.p[i].idx || p[2].idx==plo.p[i].idx) continue;
                double s1=fabs((p[0]-plo.p[i])^(p[1]-plo.p[i]));
                double s2=fabs((p[1]-plo.p[i])^(p[2]-plo.p[i]));
                double s3=fabs((p[2]-plo.p[i])^(p[0]-plo.p[i]));
                now=min(min(now,s1),min(s2,s3));
            }
            if (now!=~(1LL<<63)) ans-=now;
            else ans=0;
        }
        else
        {
            for (int i=0;i<n;i++)
            {
                int x=(i+1)%n,y=(i+2)%n;
                for (int j=(i+2)%n;j!=i;(++j)%=n)
                {
                    while (x!=j && OK(p[i],p[j],p[x],p[x+1])) (++x)%=n;
                    while (y!=i && OK(p[i],p[j],p[y],p[y+1])) (++y)%=n;
                    now=fabs((p[x]-p[i])^(p[j]-p[i]))+fabs((p[y]-p[i])^(p[j]-p[i]));
                    if (now>ans) ans=now;
                }
            }
        }
        printf("%.3lf\n",ans/2.0);
        return ;
    }
}plo;
int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        plo.input(n);
        polygon cv; plo.getconvex(cv); //得到凸包
        cv.Rotating_Calipers(plo); //旋转卡壳
    }
    return 0;
}


//n<=4000, x,y是整数, x,y<=1e9  5s
#define i64 long long
const double eps = 1e-8;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 40100;
int n;
//Compares a double to zero
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    else return 1;
}
struct Point {
    i64 x, y;
    int idx;
    Point() {}
    Point(i64 _x, i64 _y, int _idx) {
        x = _x;
        y = _y;
        idx = _idx;
    }
    void input() {
        scanf("%lld%lld", &x, &y);
    }
    void output() {
        printf("%.8f %.8f\n", x, y);
    }
    bool operator == (Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (Point b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator - (const Point &b) const {
        return Point(x - b.x, y - b.y, idx - b.idx);
    }
    //点积
    //叉积
    i64 operator ^ (const Point &b) const {
        return x * b.y - y * b.x;
    }
    //返回两点的距离
    double distance(Point p) {
        return hypot(x - p.x, y - p.y);
    }
}fp;
struct polygon{
    int n;
    Point p[maxp];
    void input(int _n){
        n=_n;
        for(int i=0; i<n; ++i){
            p[i].input();
            p[i].idx=i;
        }
    }
    void add(Point q){
        p[n++]=q;
    }
    struct cmp{
        Point p;
        cmp(const Point &p0){p=p0;}
        bool operator()(const Point &aa,const Point &bb){
            Point a=aa,b=bb;
            int d=sgn((a-p)^(b-p));
            if(d==0){
                return sgn(a.distance(p)-b.distance(p))<0;
            }
            return d>0;
        }
    };
    //进行极角排序
    //首先需要找到最左下角的点
    //需要重载号好Point的<操作符（min函数要用）
    void norm(){
        Point mi=p[0];
        for(int i=1;i<n;++i) mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    //得到凸包
    //得到凸包里面的点编号是0~n-1的
    //两种凸包的方法
    //注意如果有影响，要特判下所有点共点，或者共线的特殊情况
    //测试 LightOJ1203 Light1239
    void getconvex(polygon &convex){
        sort(p,p+n);
        convex.n=n;
        for(int i=0; i<min(n,2); ++i) convex.p[i]=p[i];
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--; //特判
        if(n<=2) return;
        int &top=convex.n;
        top=1;
        for(int i=2; i<n; ++i){
            while(top && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) --top;
            convex.p[++top]=p[i];
        }
        int temp=top;
        convex.p[++top]=p[n-2];
        for(int i=n-3; i>=0; --i){
            while(top!=temp && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) top--;
            convex.p[++top]=p[i];
        }
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--;//特判
        convex.norm(); //原来的得到的是顺时针的点，排序后逆时针。
    }
    bool OK(Point a,Point b,Point c,Point d)
    {
        double A=fabs((b-a)^(c-a));
        double B=fabs((b-a)^(d-a));
        return A<B;
    }
    void Rotating_Calipers(polygon &plo)
    {
        i64 ans=0,now;
        if (n<=2) ans=0;
        else if (n==3)
        {
            now=~(1LL<<63); //LLONG_MAX
            ans=abs((p[0]-p[2])^(p[1]-p[2]));
            for (int i=0;i<plo.n;i++)
            {
                if (p[0].idx==plo.p[i].idx || p[1].idx==plo.p[i].idx || p[2].idx==plo.p[i].idx) continue;
                i64 s1=abs((p[0]-plo.p[i])^(p[1]-plo.p[i]));
                i64 s2=abs((p[1]-plo.p[i])^(p[2]-plo.p[i]));
                i64 s3=abs((p[2]-plo.p[i])^(p[0]-plo.p[i]));
                now=min(min(now,s1),min(s2,s3));
            }
            if (now!=~(1LL<<63)) ans-=now;
            else ans=0;
        }
        else
        {
            for (int i=0;i<n;i++)
            {
                int x=(i+1)%n,y=(i+2)%n;
                for (int j=(i+2)%n;j!=i;(++j)%=n)
                {
                    while (x!=j && OK(p[i],p[j],p[x],p[x+1])) (++x)%=n;
                    while (y!=i && OK(p[i],p[j],p[y],p[y+1])) (++y)%=n;
                    now=abs((p[x]-p[i])^(p[j]-p[i]))+fabs((p[y]-p[i])^(p[j]-p[i]));
                    if (now>ans) ans=now;
                }
            }
        }
        i64 temp=ans/2;
        if(ans%2==0) printf("%lld\n",temp);
        else printf("%lld.5\n",temp);
        return ;
    }
}plo;
int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        plo.input(n);
        polygon cv; plo.getconvex(cv); //得到凸包
        cv.Rotating_Calipers(plo); //旋转卡壳
    }
    return 0;
}
