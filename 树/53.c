/*5-3 修理牧场   (25分)
农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要N块木头，每块木头长度为整数L个长度单位，于是他购买了一条很长的、能锯
成N块的木头，即该木头的长度是L的总和。但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就
设酬金等于所锯木头的长度。例如，要将长度为20的木头锯成长度为8、7和5的三段，第一次锯木头花费20，将木头锯成12和8；第
二次锯木头花费12，将长度为12的木头锯成7和5，总花费为32。如果第一次将木头锯成15和5，则第二次锯木头花费15，总花费为
35（大于32）。
请编写程序帮助农夫计算将木头锯成N块的最少花费。
输入格式:
输入首先给出正整数
N（≤10^4），表示要将木头锯成N块。第二行给出N个正整数（≤50），表示每段木块的长度。
输出格式:
输出一个整数，即将木头锯成N块的最少花费。
输入样例:
8
4 5 1 2 1 3 1 1
输出样例:
49
*/
#include <stdio.h>
#include <stdlib.h>

struct node {
	int n;
	struct node *next;
};
void creat(struct node **list,int n){
	if(*list) creat(&(*list)->next,n);
	else {
		*list=(struct node *)malloc(sizeof(struct node));
		(*list)->n=n;
		(*list)->next=NULL;
	}
}
void sort(struct node **list){
	if(!*list) return;
	else if(!(*list)->next) return;
	else {
		struct node *temp=(*list)->next;
		while(temp)
			if((*list)->n>temp->n){
				(*list)->n=(*list)->n^temp->n;
				temp->n=(*list)->n^temp->n;
				(*list)->n=(*list)->n^temp->n;
			}else temp=temp->next;
		sort(&(*list)->next);
	}
}
void merge(struct node **list){
	if(!*list) return;
	else if(!(*list)->next) return;
	(*list)->n+=(*list)->next->n;
	(*list)->next=(*list)->next->next;
	merge(&(*list)->next);
}
void solve(struct node *list,int *res){
	if(!list) return;
	else if(!list->next) return;
	struct node *temp=NULL;
	creat(&temp, list->n+list->next->n);
	list=list->next->next;
	while(list){
		if(temp->n>list->n){
			creat(&temp->next, list->n);
			list=list->next;
		}else break;
	}
	merge(&temp->next);
	struct node *i=temp;
	for(;i->next;i=i->next)
		*res+=i->n;
	*res+=i->n;
	i->next=list;
	sort(&temp);
	solve(temp,res);
}
int main(){
	struct node *list=NULL;
	int N;
	scanf("%d",&N);
	for(int i=0;i<8;i++){
		int a;
		scanf("%d",&a);
		creat(&list,a);
	}
	sort(&list);
	int res=0;
	solve(list,&res);
	printf("%d",res);
	return 0;
}
