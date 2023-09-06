洛谷 P3128
题意：
给你n个点，有k个操作，每次操作把这条路上的所有点权值都+1,现在问你最大的点权值是多少。
n<=5e4,k<=1e5
思路：
树上差分之点差分.
如果u到v这段路+1,那就++val[u],++val[v],--val[lca(u,v)],--val[fa[lca(u,v)]]，根的父亲节点为0（节点编号1~n）
最后从下往上回溯代码如下：
void gao(int now,int par){
	for(int to:E[now]){
		if(to==par) continue;
		gao(to,now);
		val[now] += val[to];
	}
	uax(maxx,val[now]);
}