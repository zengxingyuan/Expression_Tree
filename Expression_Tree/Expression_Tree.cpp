// Expression_Tree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#define MAX 100

//TreeNode
typedef struct node {
	char operater;
	int data;
	struct node *lchild;
	struct node *rchild;
}TreeNode;

//Stack 
typedef struct TreeStack {
	TreeNode *buf[MAX];
	int n;
}Treestack;

//creat empty stack
TreeStack *creat_empty_stack() {  
	TreeStack *pstack;
	pstack = (Treestack *)malloc(sizeof(TreeStack));
	pstack->n = -1;
	return pstack;
}

//pushstack
int push_stack(TreeStack *p, TreeNode *data) {
	p->n++;
	p->buf[p->n] = data;
	return 0;
}

//popstack
TreeNode *pop_stack(TreeStack *p) {
	TreeNode *data;
	data = p->buf[p->n];
	p->n--;

	return data;
}

//judge empty
int is_empty_stack(TreeStack *p) {
	if (p->n == -1)
		return 1;
	else return 0;
}

//creat suffixtree
TreeNode *create_suffixtree(char *str, TreeStack *p) {
	int i = 0;
	TreeNode *current ;
	TreeNode *left, *right;

	while (str[i]) {
		if (str[i] > '0'&&str[i] < '9') {
			current = (TreeNode *)malloc(sizeof(TreeNode));
			current->data = str[i] - '0';
			current->lchild = NULL;
			current->rchild = NULL;
			push_stack(p, current);

		}
		else {
			current = (TreeNode *)malloc(sizeof(TreeNode));
			current->operater = str[i];
			right = pop_stack(p);
			left = pop_stack(p);
			current->lchild = left;
			current->rchild = right;
			push_stack(p, current);
		}
		i++;
	}
	return p->buf[p->n];

}
//print node
void print_node(TreeNode *p) {
	if (p->lchild == NULL&&p->rchild == NULL)
		printf("%d", p->data);
	else
		printf("%c", p->operater);

}

//visit node
int visit_node(TreeNode *p) {
	print_node(p);
	return 0;
}

//post_tranverse
void PostOrder(TreeNode *p) {
	if (p == NULL) {
		return;
	}
	else {
		PostOrder(p->lchild);
		PostOrder(p->rchild);
		visit_node(p);
	}
}
//inorder_tranverse
void InOrder(TreeNode *p) {
	if (p == NULL) {
		return;
	}
	else {
		InOrder(p->lchild);
		visit_node(p);
		InOrder(p->rchild);
	}
}

//Preorder_traverse
void PreOrder(TreeNode *p) {
	if (p == NULL) {
		return;
	}
	else {
		visit_node(p);
		PreOrder(p->lchild);
		PreOrder(p->rchild);
	}
}



int main()
{
	TreeNode *p;
	TreeStack *pstack;
	int i = 0;
	char buf[100];

	scanf_s("%s",buf,MAX);

	pstack = creat_empty_stack();
	p = create_suffixtree(buf, pstack);

	printf("PostOrder: ");
	PostOrder(p);
	printf("\n");

	printf("InOrder: ");
	InOrder(p);
	printf("\n");

	printf("PreOrder: ");
	PreOrder(p);
	printf("\n");

    return 0;
}

