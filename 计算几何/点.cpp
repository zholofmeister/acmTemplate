const double eps = 1e-5;
const double inf = 1e20;
const double pi = acos(-1.0);
const int maxp = 1010;
//Compares a double to zero
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    else return 1;
}
//square of a double
inline double sqr(double x) {return x * x;}
struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) {
        x = _x;
        y = _y;
    }
    void input() {scanf("%lf%lf", &x, &y);}
    void output() {printf("%.8f %.8f\n", x, y);}
    bool operator == (Point b) const {return sgn(x-b.x)==0 && sgn(y-b.y)==0;}
    bool operator < (Point b) const {return sgn(x-b.x)==0 ? sgn(y-b.y)<0:x<b.x;}
    Point operator - (const Point &b) const {return Point(x-b.x, y-b.y);}
	Point operator + (const Point &b) const {return Point(x+b.x, y+b.y);}
    Point operator * (const double &k) const {return Point(x*k, y*k);}
    Point operator / (const double &k) const {return Point(x/k, y/k);}
    double operator * (const Point &b) const {return x*b.x+y*b.y;}//点积
    double operator ^ (const Point &b) const {return x*b.y-y*b.x;}//叉积
    double len() {return hypot(x, y);}//返回长度
    double len2() {return x*x + y*y;}//返回长度的平方
    double distance(Point p) {return hypot(x - p.x, y - p.y);}//返回两点的距离
	double distance2(Point p) {return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);}//返回两点距离的平方
    
    //计算 pa 和 pb 的夹角
    //就是求这个点看a，b的夹角
    //测试LightOJ 1203
    double rad(Point a, Point b) {
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)), (a - p) * (b - p)));
    }
    //化为长度为r的向量
    Point trunc(double r) {
        double l = len();
        if (!sgn(l)) return *this;
        r /= l;
        return Point(x * r, y * r);
    } 
    Point rotleft() {return Point(-y, x);}//逆时针旋转 90 度
    Point rotright() {return Point(y, -x);}//顺时针旋转 90 度
    //绕着 p 点逆时针旋转 angle
    Point rotat(Point p, double angle) {
        Point v = (*this) - p;
        double c = cos(angle), s = sin(angle);
        return Point(p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c);
    }
};
double cross(Point A,Point B,Point C){return (B-A)^(C-A);}//叉积
double dot(Point A,Point B,Point C){return (B-A)*(C-A);}//点积