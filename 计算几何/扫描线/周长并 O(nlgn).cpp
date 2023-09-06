const int maxn = 2*(int)1e5+1000;
int n;
int v[maxn];
struct Line {
    int x_;
    int y_, y__;
    int state;
    bool operator < (const Line &oth) const {return x_<oth.x_;}
}line[maxn];
struct s1 {
    int l, r;
    int cover;
    i64 len;
    int lcover, rcover;
    int diff;
}sgt[maxn<<3]; //注意这个大小
void pushUp(int node) {
    if (sgt[node].cover) {
        sgt[node].len = sgt[node].r-sgt[node].l;
        sgt[node].lcover = sgt[node].rcover = 1;
        sgt[node].diff = 1;
    } else {
        sgt[node].len = sgt[node<<1].len+sgt[node<<1|1].len;
        sgt[node].lcover = sgt[node<<1].lcover;
        sgt[node].rcover = sgt[node<<1|1].rcover;
        sgt[node].diff = sgt[node<<1].diff+sgt[node<<1|1].diff-(sgt[node<<1].rcover&sgt[node<<1|1].lcover);
    }
}
void build(int node, int l, int r) {
    sgt[node].l = v[l]; sgt[node].r = v[r];
    sgt[node].cover = 0;
    sgt[node].len = 0;
    sgt[node].lcover = sgt[node].rcover = 0;
    sgt[node].diff = 0;
    if (r-l <= 1) return;
    int mid = (l+r)>>1;
    build(node<<1, l, mid);
    build(node<<1|1, mid, r);
}
void update(int node, int ul, int ur, int val) {
    int l = sgt[node].l, r = sgt[node].r;
    if (ul <= l && r <= ur) {
        sgt[node].cover += val;
        pushUp(node);
        return;
    }
    if (ul < sgt[node<<1].r) update(node<<1, ul, ur, val);
    if (ur > sgt[node<<1|1].l) update(node<<1|1, ul, ur, val);  //或者ur>sgt[node<<1].r  因为sgt[node<<1].r==sgt[node<<1|1].l
    pushUp(node);
}
i64 myabs(i64 a) {return (a>0?a:-a);}

int main() {

    cin >> n;
    for1(i, n) {
        int x_, y_, x__, y__;
        cin >> x_ >> y_ >> x__ >> y__; //左下角坐标 右上角坐标
        v[i] = y_; v[i+n] = y__;
        line[i] = (Line){x_, y_, y__, 1};
        line[i+n] = (Line){x__, y_, y__, -1};
    }
    sort(v+1, v+1+(n<<1));
    sort(line+1, line+1+(n<<1));
    build(1, 1, n<<1);
    i64 ans = 0;
    i64 lst = 0;
    for (int i = 1; i <= (n<<1); ++i) {
        ans += (line[i].x_-line[i-1].x_)*2*sgt[1].diff; //vertical
        update(1, line[i].y_, line[i].y__, line[i].state);
        ans += myabs(sgt[1].len-lst);                   //horizontal
        lst = sgt[1].len;
    }
    cout << ans << '\n';
    
    return 0;
}