#include <bits/stdc++.h>
using namespace std;
#define N 100111
typedef long double D;
typedef long long L;
#define INF 1e111
#define EPS 1e-11
#define BEPS 1e-6

bool between(D a, D b, D c) {
    return a-BEPS <= b && b <= c+BEPS || a+BEPS >= b && b >= c-BEPS;
}



template<class T>
struct pt {
    T x, y;
    pt() {}
    pt(T x, T y): x(x), y(y) {}
    pt operator+(const pt p) const {
        return pt(x + p.x, y + p.y);
    }
    pt operator-(const pt p) const {
        return pt(x - p.x, y - p.y);
    }
    pt scale(T s) const {
        return pt(x * s, y * s);
    }
    T dot(pt p) {
        return x * p.x + y * p.y;
    }
    T cross(pt p) {
        return x * p.y - y * p.x;
    }
    pt operator-() const {
        return scale(-1);
    }
    double mag() {
        return hypot(x, y);
    }
    bool operator==(const pt p) const {
        return (x == p.x && y == p.y);
    }
    bool operator!=(const pt p) const {
        return !(*this == p);
    }
    bool operator<(const pt p) const {
        return x < p.x || x == p.x && y < p.y;
    }
    int quad() {
        return  x > 0 ? (y > 0 ? 2 : y < 0 ? 8 : 1):
                x < 0 ? (y > 0 ? 4 : y < 0 ? 6 : 5):
                        (y > 0 ? 3 : y < 0 ? 7 : 0);
    }
};

typedef pt<D> ptD;
typedef pt<L> ptL;

ptD normalize(ptD p) {
    return p.scale(100./p.mag());
}

ptD normalize(ptL p) {
    return normalize(ptD(p.x, p.y));
}




template<class T>
struct seg {
    pt<T> a, b;
    seg() {}
    seg(pt<T> a, pt<T> b): a(a), b(b) {}

    seg operator-() const {
        return seg(-a, -b);
    }
    seg swap() {
        return seg(b, a);
    }
    pt<T> vec() {
        return b - a;
    }
    bool operator==(const seg p) const {
        return (a == p.a && b == p.b);
    }
    bool operator!=(const seg p) const {
        return !(*this == p);
    }
    bool operator<(const seg p) const {
        return a < p.a || a == p.a && b < p.b;
    }
    T area() {
        return a.cross(b);
    }
};

typedef seg<D> segD;
typedef seg<L> segL;

ptD line_intersect(segD a, segD b) {
    ptD p1 = a.a;
    ptD v1 = normalize(a.vec());
    ptD p2 = b.a;
    ptD v2 = normalize(b.vec());

    D den = v1.cross(v2);
    assert(fabs(den) > EPS);
    D num = (p2 - p1).cross(v2);
    D t = num / den;
    return p1 + v1.scale(t);
}




template<class T>
struct ray {
    seg<T> s;
    bool rayl, rayr;
    ray() {}
    ray(seg<T> s, bool rayl, bool rayr): s(s), rayl(rayl), rayr(rayr) {}
    ray operator-() const {
        return ray(-s, rayl, rayr);
    }
    ray swap() {
        return ray(s.swap(), rayr, rayl);
    }
    pt<T> vec() {
        return s.vec();
    }
};

typedef ray<D> rayD;

bool box_contains(rayD r, ptD p) {
    segD s = r.s;
    assert(s.a.x < s.b.x);
    if (r.rayl) {
        if (r.rayr) {
            return true;
        } else {
            return p.x <= s.b.x+BEPS && between(INF * (s.a.y - s.b.y), p.y, s.b.y);
        }
    } else {
        if (r.rayr) {
            return s.a.x-BEPS <= p.x && between(s.a.y, p.y, INF * (s.b.y - s.a.y));
        } else {
            return s.a.x-BEPS <= p.x && p.x <= s.b.x+BEPS && between(s.a.y, p.y, s.b.y);
        }
    }
}





bool slopecomp(segD& a, segD& b) {
    return a.vec().cross(b.vec()) < 0;
}
bool is_hill(segD a, segD b, segD c) {
    return line_intersect(a, b).x < line_intersect(b, c).x - EPS;
}
void hull(vector<segD>& s) {
    // lower hull
    sort(s.begin(), s.end(), slopecomp);
    vector<segD> hull;
    for (int i = 0; i < s.size(); i++) {
        while (hull.size() >= 2 && !is_hill(hull[hull.size()-2], hull.back(), s[i])) {
            hull.pop_back();
        }
        hull.push_back(s[i]);
    }

    // segmentify
    for (int i = 0, j = 1; j < hull.size(); i++, j++) {
        ptD p = line_intersect(hull[i], hull[j]);
        hull[i] = i == 0 ? segD(p - normalize(hull[i].vec()), p) : segD(hull[i].a, p);
        hull[j] = segD(p, p + normalize(hull[j].vec()));
    }

    // cleanse & replace
    s.clear();
    for (int i = 0; i < hull.size(); i++) {
        if (i == 0 || i == hull.size()-1 || hull[i].a.x < hull[i].b.x - BEPS) {
            s.push_back(hull[i]);
        }
    }
}




rayD res;
bool chip_to(rayD r, ptD p) {
    if (r.rayl) {
        res = rayD(segD(p - normalize(r.vec()), p), true, false);
        return true;
    }
    if (r.s.a.x < p.x) {
        res = rayD(segD(r.s.a, p), false, false);
        return true;
    }
    return false;
}

void tie(vector<rayD>& s, vector<rayD>& t) {
    for (int i = 0; i < s.size(); i++) assert(s[i].s.a.x < s[i].s.b.x);
    for (int i = 0; i < t.size(); i++) assert(t[i].s.a.x < t[i].s.b.x);
    while (!s.empty() && !t.empty()) {
        rayD sb = s.back(); s.pop_back();
        rayD tb = t.back(); t.pop_back();
        if (fabs(normalize(sb.vec()).cross(normalize(tb.vec()))) < EPS) continue; // parallel
        ptD p = line_intersect(sb.s, tb.s);
        bool scont = box_contains(sb, p);
        bool tcont = box_contains(tb, p);
        if (scont && tcont) {
            if (chip_to(sb, p)) s.push_back(res);
            if (chip_to(tb, p)) t.push_back(res);
            break;
        }
        if (scont) s.push_back(sb);
        if (tcont) t.push_back(tb);
    }
    if (s.empty() || t.empty()) {
        s.clear();
        t.clear();
    }
}



D area(vector<segD>& s) {
    D A = 0;
    for (int i = 0; i < s.size(); i++) A += s[i].area();
    return A;
}




int n;
ptL ptLs[N];
ptD ptDs[N];
segL segLs[N];
segD segDs[N];
L planecomp(segL a, segL b) {
    return a.vec().cross(b.a - a.a);
}
bool dircomp(segL a, segL b) {
    ptL da = a.vec();
    ptL db = b.vec();
    int qa = da.quad();
    int qb = db.quad();
    if (qa != qb) return qa < qb;
    return db.cross(da) < 0;
}
void compute_segs() {
    // removes unneeded half planes
    for (int i = 0, j = n-1; i < n; j = i++) {
        segL s = segL(ptLs[j], ptLs[i]);
        segLs[i] = s;
    }
    // bounds
    #define BOUND 10000000
    segLs[n++] = segL(ptL(-(BOUND+11),0),ptL(-BOUND,BOUND));
    segLs[n++] = segL(ptL(-BOUND,BOUND),ptL(BOUND,BOUND));
    segLs[n++] = segL(ptL(BOUND,BOUND),ptL((BOUND+11),0));
    segLs[n++] = segL(ptL((BOUND+11),0),ptL(BOUND,-BOUND));
    segLs[n++] = segL(ptL(BOUND,-BOUND),ptL(-BOUND,-BOUND));
    segLs[n++] = segL(ptL(-BOUND,-BOUND),ptL(-(BOUND+11),0));

    sort(segLs, segLs + n, dircomp);

    int m = 1;
    for (int i = 1; i < n; i++) {
        if (fabs(normalize(segLs[i].vec()).cross(normalize(segLs[m-1].vec()))) < 0.01) {
            L comp = planecomp(segLs[m-1], segLs[i]);
            if (comp < 0) {
                segLs[m-1] = segLs[i];
            }
        } else {
            segLs[m++] = segLs[i];
        }
    }
    n = m;
    if (fabs(normalize(segLs[0].vec()).cross(normalize(segLs[n-1].vec()))) < 0.01) {
        L comp = planecomp(segLs[0], segLs[n-1]);
        if (comp < 0) {
            segLs[0] = segLs[n-1];
        }
        n--;
    }
}
void rot() {
    // removes vertical lines
    D s = 1e-9;
    D c = sqrt(1 - s*s);
    for (int i = 0; i < n; i++) {
        segDs[i].a.x = segLs[i].a.x * c - segLs[i].a.y * s;
        segDs[i].a.y = segLs[i].a.x * s + segLs[i].a.y * c;
        segDs[i].b.x = segLs[i].b.x * c - segLs[i].b.y * s;
        segDs[i].b.y = segLs[i].b.x * s + segLs[i].b.y * c;
    }
}



D solve() {
    // preprocess
    compute_segs();
    rot();

    // split
    vector<segD> tops, bots;
    for (int i = 0; i < n; i++) {
        (segDs[i].a.x < segDs[i].b.x ? tops : bots).push_back(segDs[i]);
    }

    // hull
    #define negall(s) do { for (int i = 0; i < s.size(); i++) s[i] = -s[i]; } while (0)
    #define swapall(s) do { for (int i = 0; i < s.size(); i++) s[i] = s[i].swap(); } while (0)
    #define ROT(x) do { reverse((x).begin(), (x).end()); swapall(x); negall(x); } while (0)
    hull(tops);
    negall(bots);
    hull(bots);
    ROT(bots);

    // combine
    vector<rayD> rtops, rbots;
    for (int i = 0; i < tops.size(); i++) rtops.push_back(rayD(tops[i], i == 0, i == tops.size()-1));
    for (int i = 0; i < bots.size(); i++) rbots.push_back(rayD(bots[i], i == 0, i == bots.size()-1));
    tie(rtops, rbots); ROT(rtops); ROT(rbots);
    tie(rtops, rbots); ROT(rtops); ROT(rbots);
    tops.clear();
    bots.clear();
    for (int i = 0; i < rtops.size(); i++) tops.push_back(rtops[i].s);
    for (int i = 0; i < rbots.size(); i++) bots.push_back(rbots[i].s);

    // normalize
    ptD ave = ptD(0, 0);
    for (int i = 0; i < tops.size(); i++) ave = ave + tops[i].a + tops[i].b;
    for (int i = 0; i < bots.size(); i++) ave = ave + bots[i].a + bots[i].b;
    ave = ave.scale(1./(2*(tops.size() + bots.size())));
    for (int i = 0; i < tops.size(); i++) tops[i] = segD(tops[i].a - ave, tops[i].b - ave);
    for (int i = 0; i < bots.size(); i++) bots[i] = segD(bots[i].a - ave, bots[i].b - ave);

    // area & proportion
    return (area(bots) - area(tops)) * 0.5 / 4e14;
}



int main() {
    int z;
    scanf("%d", &z);
    while (z--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lld%lld", &ptLs[i].x, &ptLs[i].y);
        }
        printf("%.20Lf\n", solve());
    }
}