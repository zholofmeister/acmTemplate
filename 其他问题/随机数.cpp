【随机函数】
使用mt19937而不是rand()
#include <chrono>
#include <random>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());  
ll ans = rng();  
printf("%I64d\n",ans); 
范围为0 - 4294967295（2的32次方 - 1）

【随机生成整数】
int randInt(int l,int r){    //生成l到r的整数,l <= r  
    return (rng() % (r - l + 1)) + l;  
}  