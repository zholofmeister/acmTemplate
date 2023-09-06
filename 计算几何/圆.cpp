struct circle{
    Point p;
    double r;
    circle(){}
    circle(Point _p,double _r){
        p=_p;
        r=_r;
    }
    circle(double x,double y,double _r){
        p=Point(x,y);
        r=_r;
    }
    //面积
    double area(){
        return pi*r*r;
    }
    //周长
    double circumference(){
        return 2*pi*r;
    }
    //两圆的关系
    //5 相离
    //4 外切
    //3 相交
    //2 内切
    //1 内含
    //需要Point的distance
    //测试：UVA12304
    int relationcircle(circle v){
        double d=p.distance(v.p);
        if(sgn(d-r-v.r)>0) return 5;
        if(sgn(d-r-v.r)==0) return 4;
        double l=fabs(r-v.r);
        if(sgn(d-r-v.r)<0 && sgn(d-l)>0) return 3;
        if(sgn(d-l)==0) return 2;
        if(sgn(d-l)<0) return 1;
    }
    //求两圆相交的面积
	//cf 600D 毒瘤题，要开long double
    double areacircle(circle v){
        int rel=relationcircle(v);
        if(rel>=4) return 0.0;
        if(rel<=2) return min(area(),v.area());
        double d=p.distance(v.p);
        double a1=2*acos((1.0*r*r+d*d-1.0*v.r*v.r)/(2.0*r*d));
        double a2=2*acos((1.0*v.r*v.r+d*d-1.0*r*r)/(2.0*v.r*d));
        double ans=1.0*r*r*a1/2.0 + 1.0*v.r*v.r*a2/2.0 - 1.0*r*r*sin(a1)/2.0 - 1.0*v.r*v.r*sin(a2)/2.0;
        return ans;
    }
};