/*5-3 整型关键字的散列映射 (25分)
给定一系列整型关键字和素数P，用除留余数法定义的散列函数将关键字映射到长度为P的散列表中。用线性探测法解决
冲突。
输入格式:
输入第一行首先给出两个正整数N（≤1000）和P（≥N的最小素数），分别为待插入的关键字总数、以及散列表的长度
。第二行给出N个整型关键字。数字间以空格分隔。
输出格式:
在一行内输出每个整型关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。
输入样例:
4 5
24 15 61 88
输出样例:
4 0 1 3
 */
#include<stdio.h>
int main() {
	int N, P, in[1000] = { 0 }, locate[1000] = { 0 };
	scanf("%d%d", &N, &P);
	for (int i = 0; i < N; i++) {
		int n;
		scanf("%d", &n);
		int location = n % P;
		while (in[location]) {
			location++;
			location %= P;
		}
		in[location] = n;
		locate[i] = location;
	}
	for (int i = 0; i < N - 1; i++) {
		printf("%d ", locate[i]);
	}
	printf("%d", locate[N - 1]);
	return 0;
}
