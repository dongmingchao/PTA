/*5-1 是否完全二叉搜索树   (30分)
 将一系列给定数字顺序插入一个初始为空的二叉搜索树（定义为左子树键值大，右子树键值小），你需要判断最后的
 树是否一棵完全二叉树，并且给出其层序遍历的结果。
 输入格式：
 输入第一行给出一个不超过20的正整数N；第二行给出N个互不相同的正整数，其间以空格分隔。
 输出格式：
 将输入的N个正整数顺序插入一个初始为空的二叉搜索树。在第一行中输出结果树的层序遍历结果，数字间以1个空格
 分隔，行的首尾不得有多余空格。第二行输出YES，如果该树是完全二叉树；否则输出NO。
 输入样例1：
 9
 38 45 42 24 58 30 67 12 51
 输出样例1：
 38 45 24 58 42 30 12 67 51
 YES
 输入样例2：
 8
 38 24 12 45 58 67 42 51
 输出样例2：
 38 45 24 58 42 12 67 51
 NO
 */
#include<stdio.h>
#include<stdlib.h>
struct tree {
	int n;
	struct tree *l;
	struct tree *r;
};
struct node_tree {
	struct node_tree *next;
	struct tree *t;
};
void node_tree_create(struct node_tree **list, struct tree *root) { //建一个树节点队列
	if (*list)
		node_tree_create(&(*list)->next, root);
	else {
		*list = (struct node_tree *) malloc(sizeof(struct node_tree));
		(*list)->next = NULL;
		(*list)->t = root;
	}
}
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
struct node_tree *tree_level(struct tree *root) { //层次遍历
	if (!root)
		return NULL;
	struct node_tree *list = NULL;
	struct node_tree *result = NULL;
	do {
		node_tree_create(&result, root);
		if (root->l)
			node_tree_create(&list, root->l);
		if (root->r)
			node_tree_create(&list, root->r);
		if (list->next) {
			root = list->t;
			list = list->next;
		} else {
			node_tree_create(&result, list->t);
			return result;
		}
	} while (list);
	return NULL;
}
void node_tree_print(struct node_tree *list) {
	while (list) {
		if (!list->next) {
			printf("%d", list->t->n);
			return;
		}
		printf("%d|", list->t->n);
		list = list->next;
	}
}
int isbalance(struct node_tree *list) {
	int leastisleaf = 0;
	while (list) {
		if (list->t->l && list->t->r) {
			if (leastisleaf)
				return 0;
			list = list->next;
		} else if (list->t->l) {
			if (leastisleaf)
				return 0;
			list = list->next;
		} else if (list->t->r) {
			return 0;
		} else {
			leastisleaf = 1;
			list = list->next;
		}
	}
	return 1;
}
int main() {
	struct tree *atree = NULL;
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		tree_search_insert(&atree, n);
	}
	struct node_tree *list = tree_level(atree);
	node_tree_print(list);
	if (isbalance(list))
		printf("\nYES");
	else
		printf("\nNO");
	return 0;
}
