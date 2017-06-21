/*
5-4 一元多项式的乘法与加法运算   (20分)
设计函数分别求两个一元多项式的乘积与和。
输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。
输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
*/
#include<stdio.h>
#include<stdlib.h>
//这个题是个特殊的结构体
struct node {
	int base;
	int index;
	struct node *next;
};
void creat(struct node **list, int base, int index) {
	if (*list)
		creat(&(*list)->next, base, index);
	else {
		*list = (struct node *) malloc(sizeof(struct node));
		(*list)->base = base;
		(*list)->index = index;
		(*list)->next = NULL;
	}
}
void print(struct node *list) {
	if (!list)
		return;
	if (list->next) {
		printf("%d ", list->base);
		printf("%d ", list->index);
		print(list->next);
	} else {
		printf("%d ", list->base);
		printf("%d", list->index);
	}
}
void merge(struct node **list) { //合并指数相同的项
	if (!(*list))
		return;
	//else if(!(*list)->next) return;
	else {
		struct node *temp = (*list)->next;
		struct node *p = *list; //跟随指针temp，用于删除要合并的数据
		while (temp) {
			if ((*list)->index == temp->index) {
				(*list)->base += temp->base;
				struct node *target = temp;
				p->next = temp->next;
				temp = temp->next;
				free(target);
			} else {
				p = temp;
				temp = temp->next;
			}
		}
		merge(&(*list)->next);
	}
}
struct node *multiply(struct node *left, struct node *right) {
	//乘法即底数相乘，指数相加
	struct node *l_orgin = left; //保存left的开头
	struct node *res = NULL;
	while (right) {
		int base, index;
		while (left) {
			base = left->base * right->base;
			index = left->index + right->index;
			creat(&res, base, index);
			left = left->next;
		}
		right = right->next;
		left = l_orgin;
	} //base:-42index:5，base:9index:5 发现这两个没有合并
	merge(&res);
	return res;
}
void sort(struct node **list) {
	if (!*list)
		return;
	else {
		struct node *temp = (*list)->next;
		while (temp) {
			if ((*list)->index < temp->index) {
				(*list)->base = temp->base ^ (*list)->base;
				temp->base = temp->base ^ (*list)->base;
				(*list)->base = temp->base ^ (*list)->base;
				(*list)->index = temp->index ^ (*list)->index;
				temp->index = temp->index ^ (*list)->index;
				(*list)->index = temp->index ^ (*list)->index;
			}
			temp = temp->next;
		}
		sort(&(*list)->next);
	}
}
struct node *add(struct node *left, struct node *right) { //加法就是将两个链表拼起来进行一次合成
	if (left) { //会发现有乱序，需要一个排序算法
		struct node *i = left;
		for (; i->next; i = i->next)
			;
		i->next = right;
		merge(&left);
		sort(&left);
		return left;
	}
	else if (right) {
		merge(&right);
		sort(&right);
		return right;
	} else
		return NULL;
}
int main() {
	struct node *list[2] = { NULL };
	for (int j = 0; j < 2; j++) {
		int lenth;
		scanf("%d", &lenth);
		for (int i = 0; i < lenth; i++) {
			int base;
			scanf("%d", &base);
			int index;
			scanf("%d", &index);
			creat(&list[j], base, index);
		}
	}
	struct node *mult_res = multiply(list[0], list[1]);
	print(mult_res);
	printf("\n");
	if (!mult_res)
		printf("0 ");
	struct node *add_res = add(list[0], list[1]);
	print(add_res);
	if (!add_res)
		printf("0");
	return 0;
}
