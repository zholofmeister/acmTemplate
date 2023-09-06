洛谷 P3384
题意：
已知一棵包含n个节点的树(连通且无环)，每个节点上包含一个数值，需要支持以下操作。
第一行包含4个正整数n,m,r,p,分别表示树的节点个数，操作个数，节点序号和取模数(即所有的输出结果均对此取模)。
接下来包含n个非负整数，分别依次表示各个节点上初始的数值。
接下来(n-1)行每行包含两个整数x,y表示点x和y之间连有一条边(保证无环且连通)。
接下来m行每行包含若干个正整数，每行表示一个操作，格式如下：
操作1: 1 x y z    表示将树从x到y节点最短路径上所有节点的值都加上z。
操作2: 2 x y       表示求从树x到y节点最大路径上所有节点的值之和。
操作3: 3 x z       表示将以x为根节点的子树内所有节点值都加上z。
操作4: 4 x          表示求以x为根节点的子树内所有节点值之和。
1<=n<=1e5,1<=m<=1e5,1<=p<=2^31-1。

#define int long long
const int N=(int)1e5+100;
int n,m,r,p;
int size[N],f[N],son[N],d[N],st[N],en[N],top[N],dfn,pos[N];
vector<int> G[N];
int tv[N*4],laz[N*4],a[N];
void dfs(int x){
	size[x]=1;
	for(int to:G[x]){
		if(to!=f[x]){
			f[to]=x;
			d[to]=d[x]+1;
			dfs(to);
			size[x]+=size[to];
			if(size[to]>size[son[x]]) son[x]=to;
		}
	}
}
void dfs2(int x,int y){
	st[x]=++dfn; top[x]=y;
	pos[dfn]=x;
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
void pushdown(int node,int l,int r){
	if(laz[node]!=0){
		int mid=(l+r)>>1;
		tv[node<<1]=(tv[node<<1]+laz[node]*(mid-l+1)%p)%p;   //fuck
		tv[node<<1|1]=(tv[node<<1|1]+laz[node]*(r-mid)%p)%p; //me
		laz[node<<1]=(laz[node<<1]+laz[node])%p;
		laz[node<<1|1]=(laz[node<<1|1]+laz[node])%p;
		laz[node]=0;
	}
}
void build(int node,int l,int r){
	laz[node]=0;
	if(l==r){
		tv[node]=a[pos[l]]%p;
		return;
	}
	int mid=(l+r)>>1;
	build(node<<1,l,mid);
	build(node<<1|1,mid+1,r);
	tv[node]=(tv[node<<1]+tv[node<<1|1])%p;
}
void modify(int node,int l,int r,int ml,int mr,int mval){
	if(ml<=l && r<=mr){
		tv[node]=(tv[node]+mval%p*(r-l+1)%p)%p;
		laz[node]=(laz[node]+mval%p)%p;
		return;
	}
	pushdown(node,l,r);
	int mid=(l+r)>>1;
	if(ml<=mid) modify(node<<1,l,mid,ml,mr,mval);
	if(mr>mid) modify(node<<1|1,mid+1,r,ml,mr,mval);
	tv[node]=(tv[node<<1]+tv[node<<1|1])%p;
}
int query(int node,int l,int r,int ql,int qr){
	if(ql<=l && r<=qr){
		return tv[node]%p;
	}
	pushdown(node,l,r);
	int mid=(l+r)>>1;
	int sum=0;
	if(ql<=mid) sum=(sum+query(node<<1,l,mid,ql,qr))%p;
	if(qr>mid)  sum=(sum+query(node<<1|1,mid+1,r,ql,qr))%p;
	return sum%p;
}
int qu(int x,int y){
	int sum=0;
	for(;top[x]!=top[y];x=f[top[x]]){
		if(d[top[x]]<d[top[y]]) swap(x,y);
		sum=(sum+query(1,1,n,st[top[x]],st[x]))%p;
	}
	if(d[x]<d[y]) swap(x,y);
	sum=(sum+query(1,1,n,st[y],st[x]))%p;
	return sum;
}
void modi(int x,int y,int z){
	for(;top[x]!=top[y];x=f[top[x]]){
		if(d[top[x]]<d[top[y]]) swap(x,y);
		modify(1,1,n,st[top[x]],st[x],z);
	}
	if(d[x]<d[y]) swap(x,y);
	modify(1,1,n,st[y],st[x],z);
}
signed main() {
    cin>>n>>m>>r>>p;
    for1(i, n) cin>>a[i];
    forn(i, n-1){
    	int a,b;
    	cin>>a>>b;
    	G[a].eb(b);
    	G[b].eb(a);
    }
    dfs(r);
    dfs2(r,r);
    build(1,1,n);
    forn(i, m){
    	int op,x,y,z;
    	cin>>op;
    	if(op==1){
    		cin>>x>>y>>z;
    		modi(x,y,z);
    	} else if(op==2){
    		cin>>x>>y;
    		cout<<qu(x,y)<<'\n';
    	} else if(op==3){
    		cin>>x>>z;
    		modify(1,1,n,st[x],en[x],z);
    	} else{
    		cin>>x;
    		cout<<query(1,1,n,st[x],en[x])<<'\n';
    	}
    }
    return 0;
}
