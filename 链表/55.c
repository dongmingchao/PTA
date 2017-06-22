/*5-5 两个有序链表序列的合并   (20分)
 已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的并集新非降序链表S3。
 输入格式:
 输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。
 数字用空格间隔。
 输出格式:
 在一行中输出合并后新的非降序链表，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
 输入样例:
 1 3 5 -1
 2 4 6 8 10 -1
 输出样例:
 1 2 3 4 5 6 8 10
 */
#include<stdio.h>
#include<stdlib.h>
struct node {
	int n;
	struct node *next;
};
void create(struct node **list) {
	int n;
	scanf("%d", &n);
	if (n == -1)
		return;
	else {
		*list = (struct node *) malloc(sizeof(struct node));
		(*list)->n = n;
		(*list)->next = NULL;
		create(&(*list)->next);
	}
}
void sort(struct node **list) {
	if (!*list)
		return;
	else {
		struct node *temp = (*list)->next;
		while (temp) {
			if ((*list)->n > temp->n) {
				(*list)->n = temp->n ^ (*list)->n;
				temp->n = temp->n ^ (*list)->n;
				(*list)->n = temp->n ^ (*list)->n;
			}
			temp = temp->next;
		}
		sort(&(*list)->next);
	}
}
void print(struct node *list) {
	if (!list)
		return;
	else if (!list->next) {
		printf("%d", list->n);
	} else {
		printf("%d ", list->n);
		print(list->next);
	}
}
struct node *joint(struct node **list, int lenth) {
	int save = lenth;
	while (lenth > 1) {
		struct node *i = list[save - lenth];
		for (; i->next; i = i->next)
			;
		lenth--;
		i->next = list[save - lenth];
	}
	return list[0];
}
int main() {
	struct node *list[2] = { NULL };
	create(&list[0]);
	create(&list[1]);
	list[0] = joint(list, 2);
	sort(&list[0]);
	print(list[0]);
	return 0;
}
