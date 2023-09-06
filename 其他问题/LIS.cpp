int LIS(int a[]) { //lis数组从0开始
    int len = 0;
    for1(i, n) {
        int x = lower_bound(lis, lis+len, a[i])-lis;
        lis[x] = a[i];
        len = max(len, x+1);
    }
    return len;
}
int LIS(int a[]) { //lis数组从1开始
    int len = 0;
    for1(i, n) {
        int x = lower_bound(lis+1, lis+1+len, a[i])-lis;
        lis[x] = a[i];
        len = max(len, x);
    }
    return len;
}
lower_bound : a1 < a2 < ... < an
upper_bound : a1 <= a2 <= ..<= an