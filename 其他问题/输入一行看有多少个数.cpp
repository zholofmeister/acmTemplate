//结果存在op数组中(0 ~ n-1)
vector<int> op(maxn);

int input(){
    string str, ss;
    getline(cin, str);
    if (str[0] == '-')
        return -1;
    istringstream s(str);
    vector<int> v;
    v.clear();
    while(s >> ss){
        int tmp = 0;
        for (int i = 0;i < int(ss.size()); i++)
            tmp = tmp * 10 + (ss[i] - '0');
        v.push_back(tmp);
    }
    for (int i = 0;i < int(v.size()); i++)
        op[i] = v[i];
    return v.size();
}