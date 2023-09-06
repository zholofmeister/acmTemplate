gym 102832 H 2020ccpc长春 
题意：
有一个最多5位数的密码锁，现在告诉你初始状态，以及有n个数不能达到，到达就输，现在Alice先手，Bob后手，每个人都是最优策略，问你最后谁能赢？
思路：
因为密码锁动一位，位的数字和的奇偶性就改变，就可以用二分图来表示之间的转换关系，想到二分图博弈。
因为Alice先手，如果Alice待在最大匹配的必要点，就是WIN。
注意建图过程，比较烦！

const int N = (int)1e6+100;   //点数
const int INF = 0x3f3f3f3f;           //ll const i64 INF =0x8个3fLL;  .1.
int tc,n,m,bg,ok[N],odd[N],maxx;
string st;
struct Edge{
};
struct Dicnic {
}dicnic;
void preWork(){
    for(int i=0; i<=(int)1e6+20; ++i){
        int sum=0;
        int ti=i;
        while(ti>0){
            sum+=ti%10;
            ti/=10;
        }
        odd[i]=(sum&1);
    }
}
int main() {
    memset(odd,0,sizeof(odd));
    preWork();
    cin>>tc;
    while(tc--){
        cin>>m>>n>>bg;
        maxx=1; for(int i=0; i<m; ++i) maxx*=10;
        int S=maxx+3,T=maxx+4;
        dicnic.init(maxx+5);
        memset(ok,0,sizeof(ok));
        for(int i=0; i<n; ++i){
            int num;
            cin>>num;
            ok[num]=-1; //不可行
        }
        for(int i=0; i<maxx; ++i){
            if(ok[i]==-1) continue;
            if(!odd[i]){
                if(i!=bg) dicnic.addEdge(S,i,1);
                for(int j=1; j<maxx; j*=10){
                    int rem=(i/j)%10,v1,v2; //对从右往左第i位操作，这个写法很牛逼
                    if(rem==9) v1=i-9*j;
                    else v1=i+j;
                    if(rem==0) v2=i+9*j;
                    else v2=i-j;
                    if(!ok[v1]) dicnic.addEdge(i,v1,1);//可行
                    if(!ok[v2]) dicnic.addEdge(i,v2,1);//可行
                }
            } else if(i!=bg) dicnic.addEdge(i,T,1); //这边也i!=bg
        }
        int pre=dicnic.Maxflow(S,T);
        if(!odd[bg]) dicnic.addEdge(S,bg,1);
        else dicnic.addEdge(bg,T,1);
        int aft=dicnic.Maxflow(S,T);
        if(!aft) cout<<"Bob"<<'\n';
        else cout<<"Alice"<<'\n'; //是最大匹配的必要点，选了那点必胜
    }
    return 0;
}
