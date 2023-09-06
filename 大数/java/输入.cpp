输入
1.1 申明一个输入对象cin
Scanner cin=new Scanner(System.in);

1.2 输入一个int值
Int a=cin.nextInt();

1.3 输入一个大数
BigDecimal a=cin.nextBigdecimal();

1.4 EOF结束
while(cin.hasNext()) ...{}

输出
2.1 输出任意类型的str
System.out.println(str); //有换行
System.out.print(str)    //无换行
System.out.println"( "str);//输出字符串str
System.out.println("Hello,%s.Next year,you'll be %d",name,age);

大数类
3.1 赋值
BigInteger a=BigInteger.valueOf(12);
BigInteger b=new BigInteger(String.valueOf(12));
BigDecimal c=BigDecimal.valueOf(12.0);
BigDecimal d=new BigDecimal("12.0");//建议使用字符串以防止double类型导致的误差

也可以用上述方法构造一个临时对象用于参与运算
b.add(BigInteger.valueOf(105));
