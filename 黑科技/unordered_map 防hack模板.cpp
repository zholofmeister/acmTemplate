头文件 #include <bits/stdc++.h>
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<XXX, XXX, custom_hash> you_name_it;

两组数据：
unordered_map中的insert (优化过）：
x = 107897: 0.035 seconds
x = 126271: 0.031 seconds

（未优化过）：
x = 107897: 0.014 seconds
x = 126271: 2.787 seconds