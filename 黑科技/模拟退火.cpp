JSOI2004 平衡点
可以<del>优化</del>玄学的几点：
1. 初始温度T的值
2. 降温系数的范围0.985~0.999
3. 多做几次退火减小误差
4. T>... (终止温度)
最好只改一个值，比如T的初始值或多做几次退火,不然就是在瞎jb交
const int N=1100;
int n,i;
double anx,any,vx,vy,dis,nx,ny,T,nv,x[N],y[N],w[N];
double Rand() {return (double)(rand()%20000)/20000.0;}
double dist(double xx,double yy){
    nv=0;
    for(int i=1; i<=n; ++i) nv+=sqrt((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i]))*w[i];
    if(nv<dis) dis=nv,anx=xx,any=yy;
    return nv;
}
void SA(){
    T=8000; //初始温度
    for(;T>0.001;){//小于给定系数就退出
        nx=vx; ny=vy;
        nx=nx+T*(Rand()*2-1);//在当前位置的变化幅度内随机取一点
        ny=ny+T*(Rand()*2-1);
        nv=dist(vx,vy)-dist(nx,ny);//计算当前解
        if(nv>0 || exp(nv/T)>rand()){//如果当前解比之前的最优解好那么取当前解
            vx=nx;                   //否则以exp|当前解-最优解| / T的概率接受当前解
            vy=ny;
        }
        T*=0.996; //降低搜索范围（降温）
    }
}
signed main() {
    scanf("%d",&n);
    for(i=1; i<=n; ++i){
        scanf("%lf%lf%lf",&x[i],&y[i],&w[i]);
        anx+=x[i];
        any+=y[i];
    }
    anx/=(double)n; any/=(double)n;
    vx=anx=vy=any;//(vx,vy)当前位置，(anx,any)最优解位置
    dis=dist(anx,any);
    /*for(int i=0; i<10; ++i)*/ SA();
    printf("%.3f %.3f\n",anx,any);
    return 0;
}
