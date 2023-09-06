1. 计算几何题本地有可能开不了那么多点，交上去的时候一定别忘了改N的值啊！！
2. 如果你觉得思路没问题，但一直wa，那很有可能是精度问题，把1e-5改成1e-3 或 1e-5改成1e-8试试
3. 要多注意n=1,2.. 这种小值时候是否要特判
4. 对于某些题，要注意所有点共线的情况
5. 求直角三角形的斜边用hypot的时候，要注意如果要判断斜边是不是整数先要加一个eps再向下取整，比如3,4求出来的可能会是4.999999 (cf40A)
如 
const double eps=1e-8;
int tmp=hypot(x,y)+eps;
if(tmp*tmp==x*x+y*y){
	puts("black");
	return 0;
}
或者
const double eps=1e-8;
double d2=floor(dist+eps);
if(!sgn(dist-d2)){
	puts("black");
	return 0;
}
6. 如果出现点坐标都是[-1e9,1e9] && 用到(a-b)^(c-d) && 用的int存点 -> 会爆int,要开ll(UVA 11930),不放心就#define int long long