https://codeforces.com/gym/102770
题意：
在二维平面上给定n个点m条线段，定义在x轴上一个点u，如果存在一个点u和某个给定点v的连线和所有给定线段都不相交（包括端点），则u不在阴影中。问x轴上阴影的长度（>1e9则输出-1）。
n<=500, m<=500, -1e4<=x<=1e4, 1<=y<=1e4
思路：
首先O(n^2)对每个点预处理出被线段遮挡的范围,产生的阴影是一条线段或者一个射线，因为题目规定超过1e9就输出-1，所以我们可以把射线的边界设为+-INF,一个点被遮挡的范围就是它所有线段遮挡产生的线段和射线的并。
求出每个点遮挡范围之后，对所有点的遮挡范围取交集，交集中的长度就是答案，关键就是如何求线段并和线段集合的交

#include <bits/stdc++.h>
using namespace std;
const int N=510;
const double eps = 1e-3;
const double INF=1e15;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    return 1;
}
struct Point {
    double x,y;
    Point() {}
    Point(double _x,double _y) {
        x = _x;
        y = _y;
    }
    Point operator -(const Point &b)const {
        return Point(x - b.x,y - b.y);
    }
    Point operator +(const Point &b)const {
        return Point(x + b.x,y +b.y);
    }
    double operator ^(const Point &b)const {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const {
        return x*b.x + y*b.y;
    }
}p[N];
struct Line{
	Point s,e;
	Line(){}
	Line(Point _s, Point _e) {
        s = _s;
        e = _e;
    }
	bool pointonseg(Point p) {
        return sgn((p - s) ^ (e-s)) == 0 && sgn((p - s) * (p - e)) <= 0;
    }
    Point crosspoint(Line v) {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1),
                     (s.y * a2 - e.y * a1) / (a2 - a1));
    }
    int relation(Point p) {
        int c = sgn((p - s) ^ (e - s));
        if (c < 0) return 1;
        else if (c > 0) return 2;
        else return 3;
    }
}l[N];
struct seg{
    double l,r;
};
seg getShadow(Point a,Line b){
    if(b.pointonseg(a)) return {-INF,INF}; //因为这里要看的是点和线段的关系，不能用看点和直线关系的relation函数
    if(b.s.y>=a.y && b.e.y>=a.y) return {0,0};
    Point pp[2];
    pp[0]=b.s; pp[1]=b.e;
    if(pp[0].y>pp[1].y) swap(pp[0],pp[1]);
    if(a.y>pp[1].y){
        Line lONE=Line(a,pp[0]);
        Line lTWO=Line(a,pp[1]);
        Line lTHREE=Line(Point(-1,0),Point(1,0));
        Point pONE=lONE.crosspoint(lTHREE);
        Point pTWO=lTWO.crosspoint(lTHREE);
        if(pONE.x>pTWO.x) return {pTWO.x,pONE.x};
        else return {pONE.x,pTWO.x};
    }
    if(a.y>pp[0].y){
        Line lONE=Line(a,pp[0]);
        Line lTHREE=Line(Point(0,0),Point(1000,0));
        Point pONE=lONE.crosspoint(lTHREE);
        if(b.s.y<b.e.y) swap(b.s,b.e);
        if(b.relation(a)==1){
            return {-INF,pONE.x};
        } else if(b.relation(a)==2){
            return {pONE.x,INF};
        }
    }
}
bool cmp(seg a,seg b){
    return a.l<b.l;
}
int main () {
    int tc;
    scanf("%d",&tc);
    while(tc--){
        int n,m;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%lf%lf",&p[i].x,&p[i].y);
        }
        for(int i=1;i<=m;i++){
            scanf("%lf%lf%lf%lf",&l[i].s.x,&l[i].s.y,&l[i].e.x,&l[i].e.y);
        }
        map<double,int>m2;
        for(int i=1;i<=n;i++){
            map<double,int>m1;
            for(int j=1;j<=m;j++){
                seg temp=getShadow(p[i],l[j]);
                m1[temp.l]++;
                m1[temp.r]--;
            }
            int temp=0,flag=0;
            double pre=0;
            for(auto x:m1){ //差分求线段并
                temp+=x.second;
                if(temp>0 && !flag){
                    pre=x.first;
                    flag=1;
                }
                else if(temp==0 && flag){
                    m2[pre]++;
                    m2[x.first]--;
                    flag=0;
                }
            }
        }
        int temp=0,flag=0;
        double pre=0,ans=0;
        for(auto x:m2){  //差分求线段集合的交
            temp+=x.second;
            if(temp==n && !flag){
                pre=x.first;
                flag=1;
            }
            else if(temp<n && flag){
                ans+=x.first-pre;
                flag=0;
            }
        }
        if(ans>1e9) puts("-1");
        else printf("%.5f\n",ans);
    }
}
