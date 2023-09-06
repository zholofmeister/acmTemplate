const int maxn = 2*(int)1e6+1000;
int n;
double v[maxn];
struct Line {
    double x_;
    double y_, y__;
    int state;
    bool operator < (const Line &oth) const {return x_<oth.x_;}
}line[maxn];
struct s1 {
    double l, r;
    int cover;
    double len;
}sgt[maxn<<3];

void pushUp(int node) {
    if (sgt[node].cover) sgt[node].len = sgt[node].r-sgt[node].l;
    else sgt[node].len = sgt[node<<1].len+sgt[node<<1|1].len;
}
void build(int node, int l, int r) {
    sgt[node].l = v[l]; sgt[node].r = v[r];
    sgt[node].cover = 0;
    sgt[node].len = 0;
    if (r-l <= 1) return;
    int mid = (l+r)>>1;
    build(node<<1, l, mid);
    build(node<<1|1, mid, r);
}
void update(int node, double ul, double ur, int val) {
    double l = sgt[node].l, r = sgt[node].r;
    if (ul <= l && r <= ur) {
        sgt[node].cover += val;
        pushUp(node);
        return;
    }
    if (ul < sgt[node<<1].r) update(node<<1, ul, ur, val);
    if (ur > sgt[node<<1|1].l) update(node<<1|1, ul, ur, val);
    pushUp(node);
}

int main() {
    
    while (cin >> n) {
        if (!n) break;
        for1(i, n) {
            double x_, y_, x__, y__;
            cin >> x_ >> y_ >> x__ >> y__;
            v[i] = y_; v[i+n] = y__;
            line[i] = (Line){x_, y_, y__, 1};
            line[i+n] = (Line){x__, y_, y__, -1};
        }
        sort(v+1, v+1+(n<<1));
        sort(line+1, line+1+(n<<1));
        build(1, 1, n<<1);
        double ans = 0;
        for (int i = 1; i <= (n<<1); ++i) {
            ans += sgt[1].len*(line[i].x_-line[i-1].x_);
            update(1, line[i].y_, line[i].y__, line[i].state);
        }
        cout << ans << '\n';
    }

    return 0;
}