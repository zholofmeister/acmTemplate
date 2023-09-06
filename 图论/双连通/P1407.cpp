题意：
先输入一个n，下面n对正房之间的关系(先女后男)，再输一个m，表示m对二奶(保证二奶都在正房里出现过)之间的关系(先女后男)。如果一对婚姻破裂后，通过婚外情能再次组成n对婚姻，这对婚姻就是不稳定的。求出每对婚姻稳定与否。
n<=4000, m<=20000.
思路：
强连通分量。
先连正房之间的关系，女->男。
再连二奶之间的关系，男->女。
最后看每对情侣关系是否稳定，那就看这两人是不是在同一个强连通分量中。
在同一个强连通分量中，就说明不稳定。否则稳定。

const int N = 8000+100;   //点数
//有n对，每对有两个，所以要乘2
int n,m,idx=0;
map<string,int> hs;
int scc, top, tot;
vector<int> G[N];
int low[N], dfn[N], belong[N];
int stk[N], vis[N];
void init(int n) {
    for (int i = 0; i <= 2*n; ++i) {
        G[i].clear();
        low[i] = 0;
        dfn[i] = 0;
        stk[i] = 0;
        vis[i] = 0;
    }
    scc = top = tot = 0;
}
void tarjan(int x) {
    stk[top++] = x;
    low[x] = dfn[x] = ++tot;
    vis[x] = 1;
    for (int to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to]) {
            low[x] = min(low[x], dfn[to]);
        }
    }
    if (low[x] == dfn[x]) {
        ++scc;
        int temp;
        do {
            temp = stk[--top];
            belong[temp] = scc;
            vis[temp] = 0;
        } while (temp != x);
    }
}

int main() {
    cin>>n;
    init(2*n+5); //有n对，每对有两个，所以要乘2
    string s1,s2;
    for(int i=0; i<n; ++i){
        cin>>s1>>s2;
        if(!hs[s1]) hs[s1]=idx++;
        if(!hs[s2]) hs[s2]=idx++;
        G[hs[s1]].eb(hs[s2]);
    }
    cin>>m;
    forn(i,m){
        cin>>s1>>s2;
        G[hs[s2]].eb(hs[s1]);
    }
    for(int i=0; i<idx; ++i) if(!dfn[i]) tarjan(i);
    bool ok=true;
    for(int i=0; i<idx; i+=2){
        if(belong[i]!=belong[i+1]){
            cout<<"Safe"<<'\n';
        } else{
            cout<<"Unsafe"<<'\n';
        }
    }
    return 0;
}