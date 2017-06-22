/*5-2 jmu-ds-实现KMP   (20分)
 给两个字符串A、B, 从A中找出第一次出现B的位置。
 输入格式:
 第一行输入一个整数n，表示测试数据的个数
 对于每组测试数据，输入两个字符串S T，S和T中间用一个空格隔开，每组数据占一行。
 输出格式:
 对于每组测试数据，输出A中找出第一次出现B的位置，如果A不包含B，输出“not find!”
 输入样例:
 3
 abcdabbcd abbc
 abcd efg
 abbcdd bbc
 输出样例:
 4
 not find!
 1*/
#include"../all.h"
void mtstr_print(struct mtstring *list) {
	if (list) {
		str_print(list->s);
		printf("\n");
		mtstr_print(list->next);
	}
}
int kmp(struct string *left, struct string *right) {
	struct node *next = NULL;
	struct string *front = right, *last = right->next;
	int rightlenth = 0;
	for (struct string *i = right; i->next; i = i->next)
		rightlenth++;
	int locate = 0;
	create(&next, locate);
	while (last) {
		if (last->c == front->c) {
			front = front->next;
			locate++;
		} else {
			front = right;
			locate = 1;
		}
		last = last->next;
		create(&next, locate);
	}
	struct node *orginnext = next;
	struct string *orginright = right;
	int now = 0;
	while (left) {
		if (left->c == right->c) {
			right = right->next;
			next = next->next;
			if (!right)
				return now - rightlenth;
		} else {
			int back = next->n;
			right = orginright;
			next = orginnext;
			for (int i = 0; i < back; i++) {
				right = right->next;
				next = next->next;
			}
		}
		left = left->next;
		now++;
	}
	return -1;
}
int main() {
	struct mtstring *in = NULL;
	int n;
	scanf("%d", &n);
	getchar(); //吸回车
	for (int i = 0; i < 2 * n; i++) { // 因为有数字之后的回车
		struct string *s = NULL;
		char ch = getchar();
		while ((ch != '\n') && (ch != ' ')) {
			str_create(&s, ch);
			ch = getchar();
		}
		mtstr_push(&in, s);
	}
	mtstr_reverse(&in);
	while (in) {
		int res = kmp(in->s, in->next->s);
		if (res == -1)
			printf("not find!\n");
		else
			printf("%d\n", res);
		in = in->next->next;
	}
	return 0;
}
