#include <bits/stdc++.h>
using namespace std;
string str, s;
int main() {
    while (true) {
        getline(cin, str);
        if (int(str.size()) == 1 && str[0] == '#') break;
        istringstream all(str);
        while (all >> s) {
            cout << "s : " << s << endl;
        }
    }
    return 0;
}
