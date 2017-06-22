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
void insert(struct node **list, int n) { //队列的插入【指针会移动到队尾】怎么说呢，感觉有点废
	struct node *p = (struct node *) malloc(sizeof(struct node));
	p->n = n;
	p->next = NULL;
	if (!*list)
		*list = p;
	else {
		(*list)->next = p;
		*list = p;
	}
}
void print(struct node *list) {
	if (!list)
		return;
	else if (!list->next) {
		printf("%d", list->n);
		return;
	} else
		printf("%d|", list->n);
	print(list->next);
}
void create(struct node **list, int n) { //创建链表
	struct node *p = (struct node *) malloc(sizeof(struct node));
	p->n = n;
	p->next = NULL;
	if (!*list)
		*list = p;
	else {
		struct node *copy = *list;
		while (copy->next)
			copy = copy->next;
		copy->next = p;
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
void str_create(struct string **string) { //直接输入创建字符串
	char c = getchar();
	if (c == '\n' || c == ' ')
		return;
	else {
		*string = (struct string *) malloc(sizeof(struct string));
		(*string)->c = c;
		(*string)->next = NULL;
		str_create(&(*string)->next);
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
//搜索二叉树
struct tree {
	int n;
	struct tree *l;
	struct tree *r;
};
void tree_search_insert(struct tree **root, int n) {
	if (!*root) {
		*root = (struct tree *) malloc(sizeof(struct tree));
		(*root)->n = n;
		(*root)->l = NULL;
		(*root)->r = NULL;
	} else {
		if ((*root)->n > n)
			tree_search_insert(&(*root)->r, n);
		else
			tree_search_insert(&(*root)->l, n);
	}
}
//树节点链表
struct node_tree {
	struct node_tree *next;
	struct tree *t;
};
void node_tree_push(struct node_tree **list, struct tree *root) {
	if (*list) {
		struct node_tree *p = (struct node_tree *) malloc(sizeof(struct node_tree));
		p->next = *list;
		p->t = root;
		*list = p;
	} else {
		*list = (struct node_tree *) malloc(sizeof(struct node_tree));
		(*list)->next = NULL;
		(*list)->t = root;
	}
}
void node_tree_create(struct node_tree **list, struct tree *root) { //建一个树节点队列
	if (*list)
		node_tree_create(&(*list)->next, root);
	else {
		*list = (struct node_tree *) malloc(sizeof(struct node_tree));
		(*list)->next = NULL;
		(*list)->t = root;
	}
}
void tree_levelprint(struct tree *root) { //层次遍历
	if (!root)
		return;
	struct node_tree *list = NULL;
	do {
		printf("%d|", root->n);
		if (root->l)
			node_tree_create(&list, root->l);
		if (root->r)
			node_tree_create(&list, root->r);
		if (list->next) {
			root = list->t;
			list = list->next;
		} else {
			printf("%d", list->t->n);
			return;
		}
	} while (list);
}
//字符串树
struct tree_str {
	struct string *s;
	struct tree_str *l;
	struct tree_str *r;
	struct tree_str *t;
};

//输出
void str_print(struct string *str) {
	if (!str)
		return;
	else printf("%c", str->c);
	str_print(str->next);
}
struct node *tree_print(struct tree *tree, int order) { //改变order的值：1前序遍历，2中序遍历，3后序遍历
	if (!tree)
		return NULL;
	else {
		static struct node *head = NULL;
		switch (order) {
		case 1:
			create(&head, tree->n);
			tree_print(tree->l, order);
			tree_print(tree->r, order);
			return head;
		case 2:
			tree_print(tree->l, order);
			create(&head, tree->n);
			tree_print(tree->r, order);
			return head;
		case 3:
			tree_print(tree->l, order);
			tree_print(tree->r, order);
			create(&head, tree->n);
			return head;
		}
	}
	return NULL;
}
void tree_str_print(struct tree_str *tree, int order) {
	if (!tree)
		return;
	else {
		switch (order) {
		case 1:
			str_print(tree->s);
			tree_str_print(tree->l, order);
			tree_str_print(tree->r, order);
			return;
		case 2:
			tree_str_print(tree->l, order);
			str_print(tree->s);
			tree_str_print(tree->r, order);
			return;
		case 3:
			tree_str_print(tree->l, order);
			tree_str_print(tree->r, order);
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
	struct string *symbol = NULL; //符号栈
	do {
		struct string *temp = piece(&str); //字符串取片
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
