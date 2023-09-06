//https://ac.nowcoder.com/acm/contest/5670/E
def gcd(a, b):
    if b == 0 : return a
    else : return gcd(b, a % b)
n = int(input())
a = [1]
vis = [0] * (n + 1)
temp = input().split()
for x in temp : 
    tx = int(x)
    a.append(tx)
ans = 1
for i in range(1, 1 + n) : 
    u = i
    cnt = 0
    if vis[u] == 1 : continue
    while vis[u] == 0 : 
        vis[u] = 1;
        cnt += 1
        u = a[u]
    ans = (ans * cnt) // gcd(ans, cnt)
ans = int(ans)
print(ans)
    
    