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
#include "../all.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
/*struct node {
	char c;
	struct node *next;
 };
 void create(struct node **list) {
	char ch = getchar();
	if (ch == '\n')
		return;
	else {
		*list = (struct node *) malloc(sizeof(struct node));
		(*list)->c = ch;
		(*list)->next = NULL;
 create(&(*list)->next);
	}
 }*/
int main() {
	struct string *str = NULL;
	char ch;
	ch = (char) getchar();
	while (ch != '\n') {
		str_create(&str, ch);
		ch = (char) getchar();
	}
	int locate = 0, lenth = 0;
	int finlocate = 0, finlenth = 0;
	while (str) {
		if (isdigit(str->c)) {
			lenth++;
		} else {
			if (lenth > finlenth) {
				finlenth = lenth;
				finlocate = locate - lenth;
			}
			lenth = 0;
		}
		locate++;
	}
	printf("%d %d", finlocate, finlenth);
	return 0;
}
