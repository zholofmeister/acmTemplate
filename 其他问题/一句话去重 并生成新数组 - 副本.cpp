sort(all(ans));  //一定要先排序
ans.resize(unique(all(ans)) - ans.begin());