int a[n];
//求第k小的数
nth_element(a, a + k, a + n);
//求第k大的数
nth_element(a, a + k, a + n, greater<>());