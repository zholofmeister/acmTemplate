hdu 1255
多组数据输入,n<=1000, x,y是浮点数, 范围[0,1e5]

const int N=2100;
const double eps=1e-5;
int n,maxNode;
double v[N];
int sgn(double x){
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    else return -1;
}
struct LI{
    double x,y11,y22;
    int state;
    LI(double _x=0, double _y11=0, double _y22=0, int _state=0){
        x=_x;
        y11=_y11;
        y22=_y22;
        state=_state;
    }
    bool operator < (const LI &rhs) const{
        return sgn(x-rhs.x)==-1;
    }
}l[N];
struct SE{
    double l,r,len,more;
    int cover;
}seg[N*8];
bool cmp(double a,double b){
    return sgn(a-b)==-1;
}
void pushUp(int node){
    if(seg[node].cover>=2){
        seg[node].more=seg[node].r-seg[node].l;
    } else if(seg[node].cover==1){
        seg[node].more=seg[node<<1].len+seg[node<<1|1].len;
        seg[node].len=seg[node].r-seg[node].l;
    } else{
        seg[node].more=seg[node<<1].more+seg[node<<1|1].more;
        seg[node].len=seg[node<<1].len+seg[node<<1|1].len;
    }
}
void build(int node,int l,int r){
    uax(maxNode,node);
    seg[node].l=v[l]; seg[node].r=v[r];
    seg[node].cover=0;
    seg[node].len=seg[node].more=0;
    if(r-l<=1) return;
    int mid=(l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid,r);
}
void update(int node,double ul,double ur,int nowState){ //注意这两个double!
    if(node>maxNode) return;
    double l=seg[node].l,r=seg[node].r;  //注意这两个double!
    if(ul<=l && r<=ur){
        seg[node].cover+=nowState;
        pushUp(node);
        return;
    }
    if(ul<seg[node<<1].r) update(node<<1,ul,ur,nowState);
    if(ur>seg[node<<1|1].l) update(node<<1|1,ul,ur,nowState);
    pushUp(node);
}
int main() {
    int tc;
    scanf("%d",&tc);
    while(tc--){
        maxNode=-1;
        scanf("%d",&n);
        for(int i=1; i<=n; ++i){
            double a,b,c,d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            l[i]=LI(a,b,d,1);
            l[i+n]=LI(c,b,d,-1);
            v[i]=b;
            v[i+n]=d;
        }
        sort(l+1,l+1+2*n);
        sort(v+1,v+1+2*n,cmp);
        build(1,1,2*n);
        double sum=0;
        for(int i=1; i<=2*n; ++i){
            sum+=seg[1].more*(l[i].x-l[i-1].x);
            update(1,l[i].y11,l[i].y22,l[i].state);
        }
        printf("%.2f\n",sum);
    }
    return 0;
}
