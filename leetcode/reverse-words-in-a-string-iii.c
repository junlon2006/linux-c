/**
 * 
 * 给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

示例 1:

输入: "Let's take LeetCode contest"
输出: "s'teL ekat edoCteeL tsetnoc" 
注意：在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-words-in-a-string-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

static void __reverse(char *src, int len) {
    int i = 0, j = len - 1;
    char tmp;
    while (i < j) {
        tmp = src[i];
        src[i] = src[j];
        src[j] = tmp;
        i++, j--;
    }
}

static char * __alloc_new_heap_string(char *s) {
    int len = 1;
    char *p = s, *q;
    while (*p++) len++;
    p = malloc(len);
    q = p;
    while ((*q++ = *s++) != '\0');
    return p;
}

char * reverseWords(char * s) {
    char *new_str = __alloc_new_heap_string(s);
    char *p = new_str, *ret = new_str;
    char c;
    int len = 0;
    while (1) {
        c = *new_str++;
        if (c != ' ' && c != '\0') {
            len++;
        } else {
            __reverse(p, len); p = new_str; len = 0;
        }
        if (c == '\0') break;
    }
    return ret;
}