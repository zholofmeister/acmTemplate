https://judge.yosupo.jp/problem/directedmst
题意：
给你一个n个点，m条边的图，固定根s，现在让你求出这张图的最小树形图，让你输出最小花费以及每个点的父亲节点。
节点编号0~n-1, 1<=n<=2e5, n-1<=m<=2e5, 0<=w(边权)<=1e9

#include<bits/stdc++.h>
using namespace std;
const int SZ = 200100;
struct DSU{
	int p[SZ+1],sz[SZ+1];
	stack<pair<int,int> > st;
	DSU(){I(SZ);}
	void I(int n){for(int i=0;i<=n;i++)	sz[p[i]=i]=1;}
	int F(int x){return x==p[x]?x:F(p[x]);}
	bool U(int x,int y){
		x=F(x),y=F(y);
		if(x==y)	return	st.emplace(-1,-1), false;
		if(sz[x]<sz[y])	swap(x,y);
		return p[y]=x,sz[x]+=sz[y],st.emplace(x,y),true;
	}
	void R(){
		if(st.empty())	return;
		auto [x,y]=st.top();st.pop();
		if(x==-1)	return;
		sz[x]-=sz[y],p[y]=y;
	}
};
typedef long long int T;
struct E{int a,b;T w;};
struct Node{
	E key;Node *l,*r;T d;E top(){return push(),key;}
	void push(){key.w+=d;if(l)	l->d+=d;if(r)	r->d+=d;d=0;}
};
Node* merge(Node *a,Node *b){
	if(!a||!b)	return a?a:b;
	a->push(),b->push();if(a->key.w>b->key.w)	swap(a,b);
	return swap(a->l,(a->r=merge(b,a->r))),a;
}
void pop(Node *&a){a->push(),a=merge(a->l,a->r);}
pair<T,vector<int> > DMST(int n,int r,const vector<E>& g){
	DSU D;vector<Node*> heap(n);vector<pair<int,int> > in(n,{-1,-1});
	T res=0;vector<int> used(n,-1);used[r]=r;
	vector<pair<int,vector<E> > > cycs;
	for(auto &e:g)	heap[e.b]=merge(heap[e.b],new Node{e});
	for(int s=0,u=s,w;s<n;s++,u=s){
		vector<pair<int,E> > path;
		while(used[u]==-1){
			if(!heap[u])	return {-1,{}};
			used[u]=s;auto e=heap[u]->top();path.emplace_back(u,e);
			heap[u]->d-=e.w,pop(heap[u]),res+=e.w;u=D.F(e.a);
			if(used[u]==s){
				Node *o=0;cycs.emplace_back();
				do{
					o=merge(o,heap[w=path.back().first]);
					cycs.back().second.emplace_back(path.back().second);
					path.pop_back();
				}while(D.U(u,w));
				u=D.F(u),heap[u]=o,used[u]=-1,cycs.back().first=u;
			}
		}
		for(auto &t:path)	in[D.F(t.second.b)]={t.second.a,t.second.b};
	}
	while(!cycs.empty()){
		auto c=cycs.back();cycs.pop_back();
		pair<int,int> inedge = in[c.first];
		for(auto &t:c.second)	D.R();
		for(auto &t:c.second)	in[D.F(t.b)]={t.a,t.b};
		in[D.F(inedge.second)]=inedge;
	}
	vector<int> inv;for(int i=0;i<n;i++)	inv.emplace_back(in[i].first);
	return {res,inv};
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,s;
	cin>>n>>m>>s;
	vector<E> e(m);
	for(auto &it:e)
		cin>>it.a>>it.b>>it.w;
	auto res=DMST(n,s,e);
	cout<<res.first<<endl;
	for(int i=0;i<n;i++)
		if(res.second[i]==-1)
			cout<<i<<' ';
		else
			cout<<res.second[i]<<' ';
	cout<<endl;
}
