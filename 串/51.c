/*5-1 jmu-ds-最长数字序列   (25分)
 输入一个字符串，求该字符串中最长连续数字序列出现的起始位置及其长度。
 输入格式:
 输入一个字符串，可包含空格。
 输出格式:
 输出内容：最长数字序列起始位置和长度空格隔开。输出尾部不能有空格。输入空串，输出"NULL"
 输入样例:
 123ab12345a
 输出样例:
 5 5
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
struct str {
	char c;
	struct str *next;
};
void create(struct str **list) {
	char ch = getchar();
	if (ch == '\n')
		return;
	else {
		*list = (struct str *) malloc(sizeof(struct str));
		(*list)->c = ch;
		(*list)->next = NULL;
		create(&(*list)->next);
	}
}
int main() {
	struct str *str = NULL;
	create(&str);
	int locate = 0, lenth = 0;
	int finlocate = 0, finlenth = 0;
	while (str) {
		if (str->c > '0' && str->c < '9') {
			lenth++;
		} else {
			if (lenth > finlenth) {
				finlenth = lenth;
				finlocate = locate - lenth;
			}
			lenth = 0;
		}
		locate++;
		str = str->next;
	}
	printf("%d %d", finlocate, finlenth);
	return 0;
}
