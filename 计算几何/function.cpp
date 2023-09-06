bool sameline(Point a, Point b, Point c){ //判断三点是否共线 
    double ax=c.x-a.x, ay=c.y-a.y;
    double bx=c.x-b.x, by=c.y-b.y;
    if(sgn(ax*by-ay*bx)==0)return true;
    return false;
}
bool squ(Point a,Point b,Point c,Point d){  //判断正方形 cf136D
    vector<double> temp;
    double l11=a.distance(b); temp.eb(l11);
    double l22=b.distance(c); temp.eb(l22);
    double l33=c.distance(d); temp.eb(l33);
    double l44=d.distance(a); temp.eb(l44);
    double l55=a.distance(c); temp.eb(l55);
    double l66=b.distance(d); temp.eb(l66);
    sort(all(temp));
    if(!sgn(temp[0]-temp[1]) && !sgn(temp[1]-temp[2]) && !sgn(temp[2]-temp[3]) && !sgn(temp[4]-temp[5]) && sgn(temp[3]-temp[4])==-1) return true;
    return false;
}
bool rec(Point a,Point b,Point c,Point d){  //判断矩形 cf136D
    Point ct=Point((a.x+b.x+c.x+d.x)/4,(a.y+b.y+c.y+d.y)/4); //求质心
    double l11=ct.distance(a);
    double l22=ct.distance(b);
    double l33=ct.distance(c);
    double l44=ct.distance(d);
    if(!sgn(l11-l22) && !sgn(l11-l33) && !sgn(l11-l44)) return true;
    return false;
}