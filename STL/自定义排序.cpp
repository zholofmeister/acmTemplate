//区间长度由大到小排序，若长度相同，则按左端点坐标由小到大排序
//(multi)set和priority_queue都有empty()函数
struct node {
    int l, r;
    node(int _l, int _r) : l(_l), r(_r) {}
};
struct cmp {
    bool operator () (node n1, node n2) const {
        int l1 = n1.r - n1.l + 1;
        int l2 = n2.r - n2.l + 1;
        if (l1 == l2) return n1.l < n2.l;
        return l1 > l2;
    }
};
(multi)set<node, cmp> st;
/**********************************************/
struct node {
    int l, r;
    node(int _l, int _r) : l(_l), r(_r) {}
    friend bool operator < (node n1, node n2) {  //一个堆，越在顶端(队顶)的越大
        int l1 = n1.r - n1.l + 1;                //优先队列只能重载 < 号
        int l2 = n2.r - n2.l + 1;
        if (l1 == l2) return n1.l > n2.l;
        return l1 < l2;
    }
};
priority_queue<node> pp;

