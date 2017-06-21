/*
* tool.h
*
*  Created on: 2017��6��15��
*      Author: dongmingchao
*/

#ifndef TOOL_H_
#define TOOL_H_
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
//链表
struct node {
	int n;
	struct node *next;
};
void creat(struct node **list, int n) { //创建链表
	if (*list) creat(&(*list)->next, n);
	else {
		*list = (struct node *)malloc(sizeof(struct node));
		(*list)->n = n;
		(*list)->next = NULL;
	}
}
struct node *joint(struct node **list, int lenth) { //合并链表数组
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
//字符串
struct string {
	char c;
	struct string *next;
};
void str_creat(struct string **string) { //直接输入创建字符串
	char c = getchar();
	if (c == '\n' || c == ' ')
		return;
	else {
		*string = (struct string *) malloc(sizeof(struct string));
		(*string)->c = c;
		(*string)->next = NULL;
		str_creat(&(*string)->next);
	}
}
void str_push(struct string **stackstr, char c) { //压入字符栈
	if (*stackstr) {
		struct string *temp = (struct string *) malloc(sizeof(struct string));
		temp->c = c;
		temp->next = *stackstr;
		(*stackstr) = temp;
	}
	else {
		*stackstr = (struct string *) malloc(sizeof(struct string));
		(*stackstr)->c = c;
		(*stackstr)->next = NULL;
	}
}
void str_reverse(struct string **str) { //字符串转置
	struct string *temp = NULL;
	while (*str) {
		str_push(&temp, (*str)->c);
		(*str) = (*str)->next;
	}
	(*str) = temp;
}
void str_append(struct string **string, char c) { //字符串追加
	if (*string)
		str_append(&(*string)->next, c);
	else {
		*string = (struct string *) malloc(sizeof(struct string));
		(*string)->c = c;
		(*string)->next = NULL;
	}
}
//字符串聚合
struct mtstring {
	struct string *s;
	struct mtstring *next;
	struct mtstring *prior;
};
void mtstr_push(struct mtstring **stackstr, struct string *s) { //压入字符串栈
	if (*stackstr) {
		struct mtstring *temp = (struct mtstring *) malloc(
			sizeof(struct mtstring));
		temp->s = s;
		temp->next = *stackstr;
		temp->prior = NULL;
		(*stackstr)->prior = temp;
		(*stackstr) = temp;
	}
	else {
		*stackstr = (struct mtstring *) malloc(sizeof(struct mtstring));
		(*stackstr)->s = s;
		(*stackstr)->next = NULL;
		(*stackstr)->prior = NULL;
	}
}
void mtstr_reverse(struct mtstring **str) { //字符串集合转置
	struct mtstring *temp = NULL;
	while (*str) {
		mtstr_push(&temp, (*str)->s);
		(*str) = (*str)->next;
	}
	(*str) = temp;
}
//树
struct tree_str {
	struct string *s;
	struct tree_str *l;
	struct tree_str *r;
	struct tree_str *t;
};

//输出
void print(struct node *list) {
	if (!list) return;
	else printf("%d|", list->n);
	print(list->next);
}
void str_print(struct string *str) {
	if (!str)
		return;
	else printf("%c", str->c);
	str_print(str->next);
}
void tree_print(struct tree_str *tree, int order) {
	printf("tree print\n");
	if (!tree) return;
	else {
		switch (order) {
		case 1:
			str_print(tree->s);
			tree_print(tree->l, order);
			tree_print(tree->r, order);
			return;
		case 2:
			tree_print(tree->l, order);
			str_print(tree->s);
			tree_print(tree->r, order);
			return;
		case 3:
			tree_print(tree->l, order);
			tree_print(tree->r, order);
			str_print(tree->s);
			return;
		}
	}
}
int type(struct string *str) { //判断字符串类型
	if (!str)
		return 0;
	if (isalnum(str->c))
		return 1;
	switch (str->c) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '(':
		return 4;
	case ')':
		return 5;
	}
	return 0;
}
struct string *piece(struct string **str) { //将字符串中不同类型的部分切片
	if (!*str)
		return NULL;
	if (type(*str) == 1) {
		struct string *temp = NULL;
		while (*str)
			if (type(*str) == 1) {
				str_append(&temp, (*str)->c);
				(*str) = (*str)->next;
			}
			else
				break;
		return temp;
	}
	if (type(*str) == 2) {
		struct string *temp = NULL;
		str_append(&temp, (*str)->c);
		(*str) = (*str)->next;
		return temp;
	}
	if (type(*str) == 3) {
		struct string *temp = NULL;
		str_append(&temp, (*str)->c);
		(*str) = (*str)->next;
		return temp;
	}
	return NULL;
}
struct mtstring *str_analyze(struct string *str) {
	struct mtstring *result = NULL;
	struct string *symbol = NULL; //�½�����ջ
	do {
		struct string *temp = piece(&str); //�ַ�������
		if (type(temp) == 1)
			mtstr_push(&result, temp);
		else if (type(temp) > type(symbol))
			str_push(&symbol, temp->c);
		else {
			while (symbol) {
				struct string *t = (struct string *) malloc(sizeof(struct string));
				t->next = NULL;
				t->c = symbol->c;
				mtstr_push(&result, t);
				symbol = symbol->next;
			}
			str_push(&symbol, temp->c);
		}
	} while (str);
	while (symbol) {
		struct string *t = (struct string *) malloc(sizeof(struct string));
		t->next = NULL;
		t->c = symbol->c;
		mtstr_push(&result, t);
		symbol = symbol->next;
	}
	return result;
}
struct mtstring *toPE(struct string *str) { //转为前缀表达式
	str_reverse(&str);
	return str_analyze(str);
}
struct mtstring *toAPF(struct string *str) { //转为后缀表达式
	struct mtstring *t = str_analyze(str);
	mtstr_reverse(&t);
	return t;
}
void tree_born(struct tree_str **tree, struct string *str) { //制造树节点
	if (!str)
		return;
	if (*tree) {
		str_print((*tree)->s);
		str_print(str);
		return;
	}
	*tree = (struct tree_str *) malloc(sizeof(struct tree_str));
	(*tree)->s = str;
	(*tree)->l = NULL;
	(*tree)->r = NULL;
	(*tree)->t = NULL;
}
void tree_operation(struct tree_str **tree, struct string **str) {

}


#endif /* TOOL_H_ */
