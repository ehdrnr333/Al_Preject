// ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== ==== 
//  Author 	 : Jun Su. Lim
//  File     : RBTree.h
//  Updated  : 16. 06. 04
//  Note
//  	red-black tree
//		rb_tree_iter_inorder�� rb_tree_destroy�� ��� ���
//      rb_tree_head->right�� red-black tree�� root
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <malloc.h>
#include <cstring>
#include <iostream>
#include"./Course.h"
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
#define MAX_STACK_SIZE 1000

typedef int itemType;
typedef int infoType;


namespace project
{

	struct node
	{
		itemType key; //record key : grade
		itemType tag; //color value
		Course *p_course;//course�� ����Ű�� ������
		struct node *left, *right;//Ʈ�� ������
	};

	struct node* stack[MAX_STACK_SIZE];
	int top;

	struct node *rb_tree_head, *x, *p, *g, *gg;//red-black pointer
	struct node *rb_tree_tail;
	static void rb_tree_init();
	static void rb_tree_split(itemType k);
	static struct node* rb_tree_rotate(itemType k, struct node *y);
	static void rb_tree_insert(Course * const t_course);
	static void rb_tree_destroy(struct node *t_node);
	static void node_destroy(struct node *t_node);
	static void rb_tree_iter_inorder();

	static void rb_tree_init()
	{
		rb_tree_tail = (struct node*)malloc(sizeof(struct node));
		rb_tree_tail->left = rb_tree_tail;
		rb_tree_tail->right = rb_tree_tail;
		rb_tree_tail->tag = black;
		rb_tree_tail->p_course = NULL;
		rb_tree_head = (struct node*)malloc(sizeof(struct node));
		rb_tree_head->right = rb_tree_tail;
		rb_tree_head->tag = black;
		rb_tree_head->p_course = NULL;
		rb_tree_head->key = itemMIN;
	}
	static void rb_tree_split(itemType k)
	{
		x->tag = red; x->left->tag = black; x->right->tag = black;
		if (p->tag) 
		{
			g->tag = red;//recolor
			if (k < g->key != k < p->key)
				p = rb_tree_rotate(k, g);//����ȸ��
			x = rb_tree_rotate(k, gg);//����ȸ��
			x->tag = black;
		}
	}
	static struct node* rb_tree_rotate(itemType k, struct node *y)
	{
		//tree rotation
		struct node *high, *low;
		high = (k < y->key) ? y->left : y->right;
		if (k < high->key) { low = high->left; high->left = low->right; low->right = high; }//��ȸ��
		else { low = high->right; high->right = low->left; low->left = high; }//��ȸ��
		if (k < y->key) y->left = low;
		else y->right = low;

		return low;
	}

	static void rb_tree_insert(Course * const t_course)
	{
		int k = t_course->point();
		x = rb_tree_head->right;
		p = rb_tree_head;
		g = rb_tree_head;
 		while (x != rb_tree_tail)
		{
			gg = g; g = p; p = x;
			x = (k < x->key) ? x->left : x->right;
			//�¿� �ڽ� ��尡 red�̸� recolor
			if (x->left->tag == red && x->right->tag == red) rb_tree_split(k);

		}

		x = (struct node*)malloc(sizeof(struct node));
		x->left = rb_tree_tail;
		x->right = rb_tree_tail;
		x->p_course = t_course;
		x->tag = red;
		// ��ø�Ǵ� ����?
		x->key = t_course->point();

		if (k < p->key) p->left = x; else p->right = x;
		//red-red�� �����ϱ� ���ؼ� rb_tree_split ȣ��
		//��Ʈ ���� �׻� black
		rb_tree_split(k); rb_tree_head->right->tag = black;
	}


	static void rb_tree_destroy(struct node *t_node)
	{
		if (t_node == rb_tree_tail)
			return;

		rb_tree_destroy(t_node->left);
		rb_tree_destroy(t_node->right);
		node_destroy(t_node);
	}

	static void node_destroy(struct node *t_node)
	{
		free(t_node);
	}
	static void push(struct node* node)
	{
		if (top >= MAX_STACK_SIZE - 1)
		{
			perror("Stack Overflow");
			return;
		}

		top++;
		stack[top] = node;
	}

	static struct node* pop()
	{
		struct node* node = NULL;
		if (top == -1)
			return rb_tree_tail;

		node = stack[top];
		top--;
		return node;
	}

	static void rb_tree_iter_inorder()
	{
		struct node* ptr = rb_tree_head->right;
		top = -1;

		while (1)
		{
			while (ptr != rb_tree_tail)
			{
				push(ptr);
				ptr = ptr->left;
			}

			ptr = pop();
			if (ptr == rb_tree_tail) break;
			//-------------------------------------------------
			//�� �κ��� Ʈ���� ��ȸ�ϸ鼭 course ������ ����ϴ� �κ�.
			//������ �����ϱ� ���ؼ��� �� �κ� ����ϸ� ��.
			std::cout << ptr->p_course->code()<<" " << ptr->p_course->point() << std::endl;
			//-------------------------------------------------
			ptr = ptr->right;
		}

	}

	
}

#endif
