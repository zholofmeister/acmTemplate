//s是两个s顺序拼接起来的字符串， len是原来一个s的长度， 返回的是起点的下标
// 传入的值s是个两个s， len是一个s
int min_string(char *s, int len) {
	int i = 0, j = 1, k = 0;
	while (i < len && j < len && k < len) {
		if (s[i + k] == s[j + k]) ++k;
		else if (s[i + k] < s[j + k]) j += k + 1, k = 0;
		else if (s[i + k] > s[j + k]) i += k + 1, k = 0;
		if (i == j) ++j;
	}
	return min(i, j);
}
int max_string(char *s, int len) {
	int i = 0, j = 1, k = 0;
	while (i < len && j < len && k < len) {
		if (s[i + k] == s[j + k]) ++k;
		else if (s[i + k] < s[j + k]) i += k + 1, k = 0;
		else if (s[i + k] > s[j + k]) j += k + 1, k = 0;
		if (i == j) ++j;
	}
	return min(i, j);
}