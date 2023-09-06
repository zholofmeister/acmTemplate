洛谷 p5490
给你n个矩形，每个矩形给你 左上 和 右下 两点

const int N=2*(int)1e5+100;
int n,v[N],maxNode;
struct LI{
    i64 x;
    int y11,y22,state;
    LI(i64 _x=0, int _y11=0, int _y22=0, int _state=0){
        x=_x;
        y11=_y11;
        y22=_y22;
        state=_state;
    }
    bool operator < (const LI &rhs) const{
        return x<rhs.x;
    }
}l[N];
struct SE{
    int l,r,cover;
    i64 len;
}seg[N*8];
void pushUp(int node){
    if(seg[node].cover>0) seg[node].len=seg[node].r-seg[node].l;
    else seg[node].len=seg[node<<1].len+seg[node<<1|1].len;
}
void build(int node, int l, int r){
    uax(maxNode,node);
    seg[node].l=v[l]; seg[node].r=v[r];
    seg[node].cover=seg[node].len=0;
    if(r-l<=1) return;
    int mid=(l+r)>>1;
    build(node<<1,l,mid);
    build(node<<1|1,mid,r);
}
void update(int node, int ul, int ur, int nowState){
    if(node>maxNode) return;
    int l=seg[node].l,r=seg[node].r;
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
    maxNode=-1;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i){
        i64 a,c;
        int b,d;
        scanf("%lld%d%lld%d",&a,&b,&c,&d);
        l[i]=LI(a,b,d,1);
        l[i+n]=LI(c,b,d,-1);
        v[i]=b;
        v[i+n]=d;
    }
    sort(l+1,l+1+2*n);
    sort(v+1,v+1+2*n);
    build(1,1,2*n);
    i64 ans=0;
    for(int i=1; i<=2*n; ++i){
        ans+=seg[1].len*(l[i].x-l[i-1].x);
        update(1,l[i].y11,l[i].y22,l[i].state);
    }
    printf("%lld\n",ans);
    return 0;
}
