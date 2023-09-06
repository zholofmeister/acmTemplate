#include<bits/stdc++.h>
#define double long double //double->long double
using namespace std;
vector<pair<double,int> > a;
int n,ansx,ansy;
double sum=1e5;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
        int x,y;
		scanf("%d%d",&x,&y);
		a.push_back({atan2(y,x),i+1});
	}
	sort(a.begin(),a.end());
	a.push_back(a[0]);
	for(int i=0;i<n;i++){
		double x=a[i+1].first-a[i].first;
		if(x<0)x+=2*acos(-1);
		if(x<sum)sum=x,ansx=a[i].second,ansy=a[i+1].second;
	}
	printf("%d %d",ansx,ansy);
	return 0;
}
