//半平面交 O(nlogn)
//测试 POJ3335 POJ1474 POJ1279
struct halfplane:public Line{
    double angle;
    halfplane(){}
    //表示向量s->e逆时针(左侧)的半平面
    //所以要把所有点都变为逆时针排序
    halfplane(Point _s,Point _e){
        s=_s;
        e=_e;
    }
    halfplane(Line v){
        s=v.s;
        e=v.e;
    }
    void calcangle(){
        angle=atan2(e.y-s.y,e.x-s.x);
    }
    bool operator <(const halfplane &b) const{
        return angle<b.angle;
    }
};
struct halfplanes{
    int n;        //别忘了给n赋值！
    halfplane hp[maxp];
    Point p[maxp];
    int que[maxp];
    int st,ed;
    void push(halfplane tmp){
        hp[n++]=tmp;
    }
    //去重
    void unik(){
        int m=1;
        for(int i=1; i<n; ++i){
            if(sgn(hp[i].angle-hp[i-1].angle)!=0){
                hp[m++]=hp[i];
            } else if(sgn((hp[m-1].e-hp[m-1].s)^(hp[i].s-hp[m-1].s))>0){
                hp[m-1]=hp[i];
            }
        }
        n=m;
    }
    bool halfplaneinsert(){
        for(int i=0; i<n; ++i) hp[i].calcangle();
        sort(hp,hp+n);
        unik();
        que[st=0]=0;
        que[ed=1]=1;
        p[1]=hp[0].crosspoint(hp[1]);
        for(int i=2; i<n; ++i){
            while(st<ed && sgn((hp[i].e-hp[i].s)^(p[ed]-hp[i].s))<0) --ed;
            while(st<ed && sgn((hp[i].e-hp[i].s)^(p[st+1]-hp[i].s))<0) ++st;
            que[++ed]=i;
            if(hp[i].parallel(hp[que[ed-1]])) return false;
            p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
        }
        while(st<ed && sgn((hp[que[st]].e-hp[que[st]].s)^
              (p[ed]-hp[que[st]].s))<0) --ed;
        while(st<ed && sgn((hp[que[ed]].e-hp[que[ed]].s)^
                           (p[st+1]-hp[que[ed]].s))<0) ++st;
        if(st+1>=ed) return false;
        return true;
    }
    //得到最后半平面交得到的凸多边形
    //需要先调用halfplaneinsert()且返回true
    void getconvex(polygon &con){
        p[st]=hp[que[st]].crosspoint(hp[que[ed]]);
        con.n=ed-st+1;
        for(int j=st,i=0; j<=ed; ++i,++j)
            con.p[i]=p[j];
    }
};

scanf("%d",&n);
plo.input(n);
plo.getline();
hfp.n=n;
for(int i=0; i<n; ++i){
	hfp.hp[i]=plo.l[i];  
}
if(hfp.halfplaneinsert()) puts("YES");
else puts("NO");