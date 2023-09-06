//读不了浮点数
//前面四个快读效率都差不多 快写比printf快一点
int read() {
    int x=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f = -1;ch = getchar();}
    while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch = getchar();
    return x*f;
}

int read() {
	int ans = 0, f = 1; char c = getchar();
	for (;c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
	for (;c >= '0' && c <= '9'; c = getchar()) ans = ans * 10 + c - '0';
	return ans * f;
}

i64 read() {
	i64 ans = 0, f = 1; char c = getchar();
	for (;c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
	for (;c >= '0' && c <= '9'; c = getchar()) ans = ans * 10 + c - '0';
	return ans * f;
}

template<class T>inline void read(T &res)
{
	char c;T flag=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9')res=res*10+c-'0';res*=flag;
}

template <class T>
void write(T x){
    if(x < 0) x = -x, putchar('-');
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}