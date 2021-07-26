#include "utils.h"
#include "llist.h"


list_t createList() {
	return NULL;
}

// insert at start
list_t insert(data_t *data, list_t list) {
	lnode_t *node= my_malloc(sizeof(*node));
	node->data= data;
	node->next=list;
	return node;
}


void free_list(list_t list){
	lnode_t *new_node= list;
	while (new_node != NULL) {
		lnode_t *t= new_node;
		new_node= new_node->next;
		free(t->data);
		free(t);
	}
}

/**
 * Taken from Anh's solution for Assignment 1
 */