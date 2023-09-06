//2020牛客多校第二场 F
#include <bits/stdc++.h>
using namespace std;
const int N=5050;
int n,m,k,a[N][N],b[N][N];
deque<int> dq;
int main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.precision(10);cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#endif
    cin>>n>>m>>k;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for(int i=1; i<=n; ++i){
        for(int j=1; j<=m; ++j){
            if(!a[i][j]){
                for(int k=1; k*i<=n && k*j<=m; ++k){
                    a[i*k][j*k]=k; b[i*k][j*k]=i*j*k;
                }
            }
        }
    }
	//维护队首最大的单调队列
    memset(a, 0, sizeof(a));
    for(int i=1; i<=n; ++i){
        while(!dq.empty()) dq.pop_front();
        dq.push_back(0);
        for(int j=1; j<=m; ++j){
            while(!dq.empty() && j-dq.front()>=k) dq.pop_front();
            while(!dq.empty() && b[i][j]>=b[i][dq.back()]) dq.pop_back(); //因为队首最大，所以>=
            dq.push_back(j);
            a[i][j]=b[i][dq.front()];
        }
    }
    long long ans=0;
    for(int j=1; j<=m; ++j){
        while(!dq.empty()) dq.pop_front();
        dq.push_back(0);
        for(int i=1; i<=n; ++i){
            while(!dq.empty() && i-dq.front()>=k) dq.pop_front();
            while(!dq.empty() && a[i][j]>=a[dq.back()][j]) dq.pop_back();
            dq.push_back(i);
            if(i>=k && j>=k) ans+=a[dq.front()][j];
        }
    }
    cout<<ans<<'\n';
#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
