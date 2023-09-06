struct polygon{
    int n;
    Point p[maxp];
    Line l[maxp];
    void input(int _n){
        n=_n;
        for(int i=0; i<n; ++i) p[i].input();
		//半平面交有时要加上reverse(p,p+n)把它们变成逆时针顺序
    }
    void add(Point q){
        p[n++]=q;
    }
    void getline(){
        for(int i=0; i<n; ++i) l[i]=Line(p[i],p[(i+1)%n]);
    }
    struct cmp{
        Point p;
        cmp(const Point &p0){p=p0;}
        bool operator()(const Point &aa,const Point &bb){
            Point a=aa,b=bb;
            int d=sgn((a-p)^(b-p));
            if(d==0){
                return sgn(a.distance(p)-b.distance(p))<0;
            }
            return d>0;
        }
    };
    //进行极角排序
    //首先需要找到最左下角的点
    //需要重载号好Point的<操作符（min函数要用）
    void norm(){
        Point mi=p[0];
        for(int i=1;i<n;++i) mi=min(mi,p[i]);
        sort(p,p+n,cmp(mi));
    }
    //得到凸包
    //得到凸包里面的点编号是0~n-1的
    //两种凸包的方法
    //注意如果有影响，要特判下所有点共点，或者共线的特殊情况
    //测试 LightOJ1203 Light1239
    void getconvex(polygon &convex){
        sort(p,p+n);
        convex.n=n;
        for(int i=0; i<min(n,2); ++i) convex.p[i]=p[i];
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--; //特判
        if(n<=2) return;
        int &top=convex.n;
        top=1;
        for(int i=2; i<n; ++i){
            while(top && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) --top;
            convex.p[++top]=p[i];
        }
        int temp=top;
        convex.p[++top]=p[n-2];
        for(int i=n-3; i>=0; --i){
            while(top!=temp && sgn((convex.p[top]-p[i])^(convex.p[top-1]-p[i]))<=0) top--;
            convex.p[++top]=p[i];
        }
        if(convex.n==2 && (convex.p[0]==convex.p[1])) convex.n--;//特判
        convex.norm(); //原来的得到的是顺时针的点，排序后逆时针。
    }
	//得到凸包的另外一种方法
    //测试 LightOJ1203 LightOJ1239
    void Graham(polygon &convex){
        norm();
        int &top=convex.n;
        top=0;
        if(n==1){
            top=1;
            convex.p[0]=p[0];
            return;
        }
        if(n==2){
            top=2;
            convex.p[0]=p[0];
            convex.p[1]=p[1];
            if(convex.p[0]==convex.p[1]) --top;
            return;
        }
        convex.p[0]=p[0];
        convex.p[1]=p[1];
        top=2;
        for(int i=2; i<n; ++i){
            while(top>1 && sgn((convex.p[top-1]-convex.p[top-2])^
                               (p[i]-convex.p[top-2]))<=0) --top;  //这边 <= 改成 < 就能把凸包上共线的点也加进去
            convex.p[top++]=p[i];
        }
        if(convex.n==2 && convex.p[0]==convex.p[1]) convex.n--; //特判
    }
    //判断是不是凸的
    bool isconvex(){
        bool s[3];
        memset(s,false,sizeof(s));
        for(int i=0; i<n; ++i){
            int j=(i+1)%n;
            int k=(j+1)%n;
            s[sgn((p[j]-p[i])^(p[k]-p[i]))+1]=true;
            if(s[0] && s[2]) return false;
        }
        return true;
    }
	//旋转卡壳
    double rotate_calipers(){
        double ans=0;
        if(n==1) return ans;
        else if(n==2){
            ans=max(ans,p[0].distance(p[1]));
            return ans;
        }
        else if(n==3){
            ans=max(ans, p[0].distance(p[1]));
            ans=max(ans, p[0].distance(p[2]));
            ans=max(ans, p[1].distance(p[2]));
            return ans;
        } else{
            int i,j=1;
            p[n++]=p[0];
            for(int i=0; i<n; ++i){
                for(;cross(p[i+1],p[j+1],p[i])>cross(p[i+1],p[j],p[i]);j=(j+1)%n);
                ans=max(ans, max(p[i].distance(p[j]),p[i+1].distance(p[j])));//最远点对
            }
            return ans;
        }
    }
	//得到周长
    //测试 LightOj1239
    double getcircumference(){
        double sum=0;
        for(int i=0; i<n; ++i){
            sum+=p[i].distance(p[(i+1)%n]);
        }
        return sum;
    }
	//得到面积
    double getarea(){
        double sum=0;
        for(int i=0; i<n; ++i) sum+=(p[i]^p[(i+1)%n]);
        return fabs(sum)/2;
    }
};