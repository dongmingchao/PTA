/*
 * 51.c
 *
 *  Created on: 2017年6月7日
 *      Author: dongmingchao
 */
/*5-1 根据后序和中序遍历输出先序遍历   (25分)
本题要求根据给定的一棵二叉树的后序遍历和中序遍历结果，输出
该树的先序遍历结果。
输入格式:
第一行给出正整数N(≤30)，是树中结点的个数。随后两行，每行
给出N个整数，分别对应后序遍历和中序遍历结果，数字间以空格
分隔。题目保证输入正确对应一棵二叉树。
输出格式:
在一行中输出Preorder:以及该树的先序遍历结果。数字间有1个
空格，行末不得有多余空格。
输入样例:
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
输出样例:
Preorder: 4 1 3 2 6 5 7*/
#include<stdio.h>
#include<stdlib.h>
struct node {
	int n;
	struct node *next;
};
struct map {
	struct map *next;
	int x, y; //位置
	int n;
};
struct tree{
	int n;
	struct tree *l;
	struct tree *r;
};
void creattree(struct tree **root){

}
void creat(struct node **list){
	if (*list)
		creat(&(*list)->next);
	else {
		*list = (struct node *) malloc(sizeof(struct node));
		int n;
		scanf("%d", &n);
		(*list)->n = n;
		(*list)->next = NULL;
	}
}
void creatmap(struct map **amap, int x, int y, int n) {
	if (*amap)
		creatmap(&(*amap)->next, x, y, n);
	else {
		*amap = (struct map*) malloc(sizeof(struct map));
		(*amap)->x = x;
		(*amap)->y = y;
		(*amap)->n = n;
		(*amap)->next = NULL;
	}
}
struct map *locate(struct node *hou, struct node *zhong, int mapsize) {
	struct map *amap = NULL;
	struct node *houhead = hou;
	mapsize--;
	int x = 0, y = mapsize;
	for (; zhong; zhong = zhong->next) {
		for (; hou; hou = hou->next) {
			if (hou->n == zhong->n) {
				creatmap(&amap, x, y, hou->n);
				y = mapsize;
				hou = houhead;
				break;
			} else
				y--;
		}
		x++;
	}
	return amap;
}
void solve(struct map *amap) {
	int y = 0;
	for (; amap; amap = amap->next) {
		printf("%d,%d amap->n=%d\n",amap->x,amap->y,amap->n);
		if (amap->y == y)
			printf("%d|", amap->n);
		y++;
	}
}
int main(){
	struct node *hou = NULL;
	struct node *zhong = NULL;
	int lenth;
	scanf("%d",&lenth);
	for (int i = 0; i < lenth; i++)
		creat(&hou);
	for (int i = 0; i < lenth; i++)
		creat(&zhong);
	struct map *resmap = locate(hou, zhong, lenth);
	solve(resmap);
	return 0;
}
