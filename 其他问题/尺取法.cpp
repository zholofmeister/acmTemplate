//尺取法：反复推进区间的开头和末尾，来求满足条件的最小区间的方法被称作尺取法。
#include<bits/stdc++.h>
//题意：给你一个长度为n的数列，再给你一个数s，让你找出数列中连续元素和>=s的最短长度。
#define ll long long
using namespace std;
const ll maxn=(ll)1e5+100;
ll tc,n,s,a[maxn];
int main() {
    cin>>tc;
    while(tc--){
        cin>>n>>s;
        for(int i=1; i<=n; ++i) cin>>a[i];
        ll ans=LLONG_MAX;
        ll l=1,r=1,sum=0;
        for(;;){
            while(r<=n && sum<s){
                sum+=a[r++];
            }
            if(sum<s) break;
            ans=min(ans, r-l);
            sum-=a[l++];
        }
        if(ans==LLONG_MAX) ans=0;
        cout<<ans<<'\n';
    }
    return 0;
}

