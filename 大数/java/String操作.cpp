https://ac.nowcoder.com/acm/contest/9004/C
牛客C
题意：
给你一个长度1e5并且只包含(1~9)的字符串，把这n个数分成k块，顺序可以随意搞，让这k块数的和最大。
思路：
先把String转成array然后sort一下（默认从小到大），用StringBuilder（据说快一点）从后往前贪心取即可。

import java.util.*;
import java.math.BigInteger;
public class Solution {
    public String Maxsumforknumers (String x, int k) {
        char[] a=x.toCharArray();
        Arrays.sort(a);
        StringBuilder s=new StringBuilder();
        for(int i=a.length-1; i>k-2; --i){
            s.append(String.valueOf(a[i]));
        }
        BigInteger res=new BigInteger(s.toString());
        for(int i=k-2; i>=0; --i){
            res=res.add(new BigInteger(String.valueOf(a[i])));
        }
        return res.toString();
    }
}
