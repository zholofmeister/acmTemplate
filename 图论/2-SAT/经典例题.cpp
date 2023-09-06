UVA 11930
题意：
给你n个矩形，每个矩形给你四个顶点(无序,所以要先排序),现在要求每个矩形都要选一个对角线，使得这些对角线都不相交。如果存在解的话就YES,不然NO。
1000ms n<=1000, -1e9<=xi,yi<=1e9
思路：
预处理出2*n条对角线，然后遍历。
1. 同一个矩形的对角线continue,
2. i与j不相交,i与j^1相交  -> 选i一定选j         ->i向j连边。
3. i与j相交,i与j^1不相交  -> 不可能选i,只能选i^1 -> i向i^1连边
sgn和叉积那边要开ll(490ms) or 直接#define int long long(430ms 还快一点??)

cf 27D
问题：
给你一个环，然后给你m条边，表示要连这两条边，现在只能在里面连或者在外面连两种方式，问是否可行
关键要判环内两边是否一定规范相交(相交但不是端点相交)
环的编号是顺序的1~n,输入时已经保证每个seg的l < r。
4<=n<=100,1<=m<=100,1<=ai,bi<=n,ai!=bi
思路：
下面的是判线段相交的代码
bool within(int x,int y,int z){
    return (x<z && z<y);
}
bool intersect(int i1,int i2){
    if(seg[i1].l==seg[i2].l || seg[i1].l==seg[i2].r) return false;
    if(seg[i1].r==seg[i2].l || seg[i1].r==seg[i2].r) return false;
     return (within(seg[i2].l,seg[i2].r,seg[i1].l)!=within(seg[i2].l,seg[i2].r,seg[i1].r));
}

POJ 3678
题意：
给你m个限制a,b,c(OR,AND,XOR)，表示a点和b点(操作)后的结果是c，点的值只能是0或1,问你有没有可行解。
思路：
如果操作是 OR
** c=0, a true -> a false, b true -> b false
   c=1, a false -> b true, b false -> a true
如果操作是 AND
   c=0, a true -> b false, b true -> a false
** c=1, a false -> a true, b false -> b true
如果操作是 XOR
   c=0, a false -> b false, b false -> a false
        a true -> b true, b true -> a true
   c=1, a false -> b true, b true -> a false
        a true -> b false, b false -> a true