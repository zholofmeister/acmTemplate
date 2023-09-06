题意：
给你两条线段，一条白线一条黑线，现在问你有多少区域面积看得到白线看不到黑线，注意黑白线不包括断线，先输入白线两端点再输入黑线两端点。
-1000<=x,y<=1000
思路：
先分三种情况讨论，两条线段规范相交，不规范相交，不相交。
然后里面在细致的讨论。

反思:
1. 两线段ab,cd形成的区域是ac,bd还是ad,bc不能判断ac，ad谁小就确定，可以先随意形成两条线段，如果规范相交（这种情况只有规范相交和不相交两种情况），就不是这两条线段，换另一种就行。
2. 考虑不相交的情况漏考虑了两线段共线的情况。
3. 求三角形面积可以用叉积或者海伦公式，推荐叉积，因为叉积精度高，求面积别忘了叉积取绝对值再/2。

int tc;
scanf("%d",&tc);
int kase=1;
while(tc--){
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&po[0].x,&po[0].y,&po[1].x,&po[1].y,&po[2].x,&po[2].y,&po[3].x,&po[3].y);
	Line l11=Line(po[0],po[1]),l22=Line(po[2],po[3]);
	int rel=l11.segcrossseg(l22);
	if(rel==2) printf("Case %d: 0.000\n",kase++);
	else if(rel==1){
		if(l11.parallel(l22)) printf("Case %d: 0.000\n",kase++);
		else if(po[0]==po[2] || po[0]==po[3] || po[1]==po[2] || po[1]==po[3]) printf("Case %d: inf\n",kase++);
		else{
			Point cp=l11.crosspoint(l22);
			if(cp==l11.s || cp==l11.e) printf("Case %d: 0.000\n",kase++);
			else printf("Case %d: inf\n",kase++);
		}
	} else{
		Point cp=l11.crosspoint(l22);
		Line newl1,newl2;
		if(l11.linecrossline(l22)==1) printf("Case %d: 0.000\n",kase++); //共线
		else if(l11.pointonseg(cp)){
			printf("Case %d: inf\n",kase++);
		}
		else if(l22.pointonseg(cp)) printf("Case %d: 0.000\n",kase++);
		else{
			newl1=Line(po[0],po[2]);newl2=Line(po[1],po[3]);
			if(newl1.segcrossseg(newl2)!=0) {newl1=Line(po[0],po[3]);newl2=Line(po[1],po[2]);}
			Point cp2=newl1.crosspoint(newl2);
			if(newl1.parallel(newl2)){printf("Case %d: inf\n",kase++);}
			else{
				if(l11.relation(cp2)==l11.relation(l22.s)){
					printf("Case %d: inf\n",kase++);
				}
				//else printf("Case %d: %.8f\n",kase++,gao(cp2.distance(l11.s),cp2.distance(l11.e),l11.s.distance(l11.e)));
				else printf("Case %d: %.8f\n",kase++,fabs((l11.e-cp2)^(l11.s-cp2))/2);
			}
		}
	}
}