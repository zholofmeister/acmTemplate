const int N=(int)1e5+100;
int n,m,r,p;
int sz[N],f[N],son[N],d[N],st[N],en[N],top[N],dfn,pos[N];
vector<int> G[N];
void dfs(int x){
	sz[x]=1;
	for(int to:G[x]){
		if(to!=f[x]){
			f[to]=x;
			d[to]=d[x]+1;
			dfs(to);
			sz[x]+=sz[to];
			if(sz[to]>sz[son[x]]) son[x]=to;
		}
	}
}
void dfs2(int x,int y){
	st[x]=++dfn; top[x]=y;
	pos[dfn]=x; //新编号dfn位置的点对应原位置x的点，build线段树的时候要用(if(l==r) tv[node]=a[pos[l]]%p;)
	if(son[x]) dfs2(son[x],y);
	for(int to:G[x]){
		if(to!=son[x] && to!=f[x]) dfs2(to,to);
	}
	en[x]=dfn;
}
//查询x,y两点的lca
int lca(int x,int y){
	for(;top[x]!=top[y];x=f[top[x]]){
		if(d[top[x]]<d[top[y]]) swap(x,y);
	}
	return d[x]<d[y]?x:y;
}
//x是y的祖先,查询x到y方向的第一个点
int lca2(int x,int y){
	int t;
	while(top[x]!=top[y]){
		t=top[y];
		y=f[top[y]];
	}
	return x==y?t:son[x];
}
//对x到y路径上的点进行操作 
void chain(int x,int y){
 	for(;top[x]!=top[y];x=f[top[x]]){
 		if(d[top[x]]<d[top[y]]) swap(x,y);
 		change(st[top[x]],st[x]);
 	}
 	if(d[x]<d[y]) swap(x,y);
 	change(st[y],st[x]);
 }