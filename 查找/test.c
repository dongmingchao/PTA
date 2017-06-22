#include"../all.h"

int main() {
	struct node *list = NULL;
	for (int i = 0; i < 5; i++)
		insert(&list, i);
	print(list);
}
