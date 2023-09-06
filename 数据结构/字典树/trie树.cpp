//UVA644 判断输入的多组字符串中有没有一个串是另一个串的子串
const int maxn = 500100;
int trie[maxn][26], sum[maxn], ed[maxn], root, len, tot;
char s[maxn];
bool flag;

void Insert(char s[]) {
    root = 0;
    len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int id = int(s[i] - 'a');
        if (!trie[root][id]) trie[root][id] = ++tot;
        /*if (ed[trie[root][id]]) {
            flag = true;
        }
        if (i == len-1) {
            ++ed[trie[root][id]];
            if (sum[trie[root][id]]) {
                flag = true;
            }
        }*/
        sum[trie[root][id]]++;
        root = trie[root][id];
    }
}
int Find(char s[]) {
    root = 0;
    len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int id = int (s[i] - 'a');
        if (!trie[root][id]) return 0;
        root = trie[root][id];
    }
    return sum[root];
}
void init() { //多组数据慎用，要么把字典树开小一点
    memset(trie, 0, sizeof(trie));
    memset(sum, 0, sizeof(sum));
    memset(ed, 0, sizeof (ed));
    tot = 0;
    flag = false;
}

int main() {
    int kase = 1;
    init();
    while (~scanf("%s", s)) {
        if (strlen(s) == 1 && s[0] == '9') {
            if (flag == false) printf("Set %d is immediately decodable\n", kase++);
            else printf("Set %d is not immediately decodable\n", kase++);
            init();
        } else {
            Insert(s);
        }
    }
    return 0;
}