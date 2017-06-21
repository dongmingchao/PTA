/*5-4 jmu-ds-二叉树实现表达式求解   (25分)
用二叉树来表示表达式，树的每一个节点包括一个运算符和运算数。代数表达式中只包含+，-，*，/，（，）和一位整数且没有
错误。按照先括号，再乘除，后加减的规则构造二叉树。如图所示是"1+(2+3)*2-4/5"代数表达式对应二叉树，用对应的二叉
树计算表达式的值。
输入格式:
输入一行表达式字符串，括号内只能有一个运算符。
输出格式:
输出表达式的计算结果.如果除数为0，提示divide 0 error!
输入样例1:
(1+2)*3-4/5+(3-2)
输出样例1:
9.2
输入样例2:
1+2*3-4
输出样例2:
3
*/
#include "../tool.h"
int trans(struct string *str) {
	char res[7];
	int i = 0;
	while (str) {
		res[i] = str->c;
		str = str->next;
		i++;
	}
	res[i] = '\0';
	return atoi(res);
}
int calculate(struct mtstring **str) {
	int res;
	switch ((*str)->s->c) {
	case '+':
		res = trans((*str)->prior->prior->s) + trans((*str)->prior->s);
		(*str)->prior = (*str)->prior->prior->prior;
		return res;
	case '-':
		res = trans((*str)->prior->prior->s) - trans((*str)->prior->s);
		(*str)->prior = (*str)->prior->prior->prior;
		return res;
	case '/':
		res = trans((*str)->prior->prior->s) / trans((*str)->prior->s);
		(*str)->prior = (*str)->prior->prior->prior;
		return res;
	case '*':
		res = trans((*str)->prior->prior->s) * trans((*str)->prior->s);
		(*str)->prior = (*str)->prior->prior->prior;
		return res;
	}
	printf("ERROR");
	return 0;
}
int main(){
	struct string *s=NULL;
	struct mtstring *symbol = NULL;
	str_creat(&s);
	str_print(s);
	printf("\n");
	symbol = toAPF(s);
	int res = 0;
	while (symbol) {
		str_print(symbol->s);
		if (type(symbol->s) != 1) {
			res += calculate(&symbol);
		}
		symbol = symbol->next;
	}
	printf("%d", res);
	return 0;
}
