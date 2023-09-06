//建议放 >= 2阶数量的表到vector中
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define pb push_back
typedef long long i64;
#define SZ(x) ((i64)(x).size())
typedef vector<i64> vi64;
typedef pair<i64,i64> PII;
const i64 mod=(i64)1e9 + 7;
i64 powmod(i64 a,i64 b) {
    i64 res=1;
    a%=mod;
    assert(b>=0);
    for(; b; b>>=1) {
        if(b&1)res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}
i64 _,n;
namespace linear_seq {
    const i64 N=10010;
    i64 res[N],base[N],_c[N],_md[N];

    vector<i64> Md;
    void mul(i64 *a,i64 *b,i64 k) {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (i64 i=k+k-1; i>=k; i--) if (_c[i])
                rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    i64 solve(i64 n,vi64 a,vi64 b) { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
        i64 ans=0,pnt=0;
        i64 k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];
        _md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (i64 p=pnt; p>=0; p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (i64 i=k-1; i>=0; i--) res[i+1]=res[i];
                res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    vi64 BM(vi64 s) {
        vi64 C(1,1),B(1,1);
        i64 L=0,m=1,b=1;
        rep(n,0,SZ(s)) {
            i64 d=0;
            rep(i,0,L+1) d=(d+(i64)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                vi64 T=C;
                i64 c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L;
                B=T;
                b=d;
                m=1;
            } else {
                i64 c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    i64 gao(vi64 a,i64 n) {
        vi64 c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,vi64(a.begin(),a.begin()+SZ(c)));
    }
};

i64 m, f[300];

int main() {
   ios::sync_with_stdio(false);
   cin.tie(0);
   cin >> n >> m;
   for (int i = 0; i < m; ++i) f[i] = 1;
   for (int i = m; i <= 250; ++i) {
        f[i] = (f[i - 1] + f[i - m]) % mod;
   }
   vi64 v;
   for (int i = 1; i <= 250; ++i) {
        v.emplace_back(f[i]);
   }
   cout << linear_seq::gao(v,n-1)%mod << '\n';
   return 0;
}
