#include <cstdlib>
#include "Integer.h"

#define Log_10_2 0.3010299957
#define print2console
#ifdef print2console
#include <iostream>
#endif // print2console


struct duLNode {
	char data;
	duLNode * next, *prior;
};

static duLNode* duLNode_init();
static inline duLNode* NewNode();
static inline duLNode* NewNode(char char_src);
static int duLNode_length(duLNode *list);
static void duLNode_print(duLNode *list);
//static void duLNode_back_insert(duLNode **list, char char_src);
//static void duLNode_front_insert(duLNode *list, char char_src);
static void duLNode_head_insert(duLNode **list, char char_src);
//static void duLNode_tail_insert(duLNode *list, char char_src);
static void duLNode_destroy(duLNode *list);

Integer::Integer() {
	this->init = 0;
}
Integer::Integer(int int_src) {
	int bytes = (int)sizeof(int);
	this->init = 1;
	this->data = (char*)malloc(bytes);

	if (int_src == 0)
		this->zero = 1;
	else {
		this->zero = 0;
		this->byte = bytes;

		if (int_src > 0)
			this->sign = 1; 
		else { 
			this->sign = 0;
			int_src = -int_src;
		}
	}
	for (int i = 0; i < bytes; i++) {
		data[i] = int_src % 0x100;
		int_src = int_src >> 8;
	}
}

void Integer::print() {
	duLNode *list = duLNode_init(), *p;
	list->data = 'a';
	duLNode_head_insert(&list, 'b');
	duLNode_head_insert(&list, 'c');
	duLNode_head_insert(&list, 'd');
	duLNode_head_insert(&list, 'e');

	duLNode_print(list);

	


	std::cout << duLNode_length(list) << std::endl;
	
}

static inline duLNode* NewNode() {
	return (duLNode*)malloc(sizeof(duLNode));
}
static inline duLNode* NewNode(char char_src) {
	duLNode *p = (duLNode*)malloc(sizeof(duLNode));
	p->data = char_src;
	return p;
}
static duLNode* duLNode_init() {
	duLNode *list = NewNode();
	list->prior = list;
	list->next  = list;
	return list;
}
static int duLNode_length(duLNode *list) {
	duLNode *p = list;
	int  length=1;
	while (p->next != list) {
		length++;
		p = p->next;
#ifdef print2console
		std::cout << p << "  ";
#endif // print2console
	}
	return length;
}
static void duLNode_print(duLNode *list) {
	duLNode *p = list;
	while (p->prior != list) {
		p = p->prior;
		std::cout << (p->data) << ' ';
	}
	std::cout << (list->data) << ' ';
}
static void duLNode_head_insert(duLNode **list, char char_src) {
	duLNode *old_head = *list, *p;
	p = NewNode(char_src);
	
	p->prior = old_head->prior;
	p->next  = old_head;
	old_head->prior->next = p;
	old_head->prior       = p;
	
	*list = p;
}