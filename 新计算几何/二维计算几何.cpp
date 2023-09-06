const double eps=1e-8;
int sgn(double x){
    if(fabs(x) < eps) return 0;
	if(x < 0) return -1;
	return 1
}
//二次方程
bool Quadratic(double A,double B,double C,double *t0,double *t1){
    double discrim = B * B - 4.f * A * C;
    if(discrim < 0.){return false;}
    double rootDiscrim = sqrt(discrim);
    double q;
    if(B < 0) q = -.5f * (B - rootDiscrim);
    else      q = -.5f * (B + rootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if (*t0 > *t1) swap(*t0, *t1);
    return true;
}
struct vec{
    double x,y;
    vec(double _x=0,double _y=0){x=_x,y=_y;}

    vec operator + (vec v) {return vec(x+v.x,y+v.y);}
    vec operator - (vec v) {return vec(x-v.x,y-v.y);}
    vec operator * (double v) {return vec(x*v,y*v);}
    vec operator / (double v) {return vec(x/v,y/v);}

    double operator * (vec v) {return x*v.x + y*v.y;}

    double len()     {return hypot(x,y);}
    double len_sqr() {return x*x + y*y;}

    //逆时针旋转
    vec rot(double c)   {return vec(x*cos(c)-y*sin(c),x*sin(c)+y*cos(c));}
    vec trunc(double l) {return (*this) * l / len();}
    vec rot90()         {return vec(-y,x);}
};
double cross(vec a,vec b) {return a.x*b.y - a.y*b.x;}
//判断点是否在线段上(包含端点)
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
//计算 a,b 间的角度
double get_angle(vec a,vec b) {return fabs(atan2(fabs(cross(a,b)),a*b));}
//直线插值
vec lerp(vec a,vec b,double t) {return a * (1-t) + b * t;}
//点p到直线ab距离
double dist_point_to_line(vec p,vec a,vec b){
    return fabs(cross(p-a,b-a))/(b-a).len();
}
//点p到线段ab距离
double dist_point_to_segment(vec p,vec a,vec b){
    if( (b-a).len()>eps && sgn( (p-a)*(b-a) ) >= 0 && sgn( (p-b)*(a-b) ) >= 0)
        return fabs(cross(p-a,b-a))/(b-a).len();
    return min( (p-a).len(), (p-b).len() );
}


struct circle{
    vec c; double r;
    circle(vec _c=vec(0,0),double _r=0.0){c=_c,r=_r;}
};
//圆直线交点，焦点是lerp(a,b,*t0)和lerp(a,b,*t1)
bool circle_line_intersection(circle c,vec a,vec b,double *t0,double *t1){
    vec d = b - a;
    double A = d * d;
    double B = d * (a-c.c) * 2.0;
    double C = (a-c.c).len_sqr() - c.r * c.r;
    return Quadratic(A,B,C,t0,t1);
}
//圆和三角形abo交的面积，o是圆心
double circle_triangle_intersection_area(circle c,vec a,vec b){
    if( sgn(cross(a-c.c,b-c.c)) == 0 ) return 0;
    vec q[5];
    int len = 0;
    double t0,t1;
    q[len++] = a;
    if( circle_line_intersection(c,a,b,&t0,&t1) ){
        if( 0<=t0 && t0<=1) q[len++]=lerp(a,b,t0);
        if( 0<=t1 && t1<=1) q[len++]=lerp(a,b,t1);
    }
    q[len++] = b;
    double s = 0;
    for(int i=1; i<len; ++i){
        vec z = (q[i-1] + q[i])/2;
        if( (z-c.c).len_sqr() <= c.r*c.r )
            s += fabs( cross(q[i-1]-c.c,q[i]-c.c) )/2;
        else
            s += c.r*c.r*get_angle(q[i-1]-c.c,q[i]-c.c) / 2;
    }
    return s;
}

//求圆和多边形交的面积
double circle_polygon_intersection_area(circle c,vec *v,int n){
	//vec里的点顺时针输入或者逆时针输入
    double s=0;
    for(int i=0; i<n; ++i){
        int j = (i+1) % n;
        vec v11=v[i]-c.c,v22=v[j]-c.c;
        s += circle_triangle_intersection_area(c,v[i],v[j]) 
           * sgn( cross(v[i]-c.c, v[j]-c.c) );
    }
    return fabs(s);
}
//判点是否在多边形内或边上
bool point_in_polygon(vec *a,int n,vec p){
    int ret=0;
    for(int i=0; i<n; ++i){
        vec u=a[i],v=a[(i+1)%n];
        if(point_on_segment(p,u,v)) return 1;
        if(sgn(u.y-v.y)<=0) swap(u,v);
        if(sgn(p.y-u.y)>0 || sgn(p.y-v.y)<=0) continue;
        ret+=sgn(cross(v-p,u-p))>0;
    }
    return ret&1;
}