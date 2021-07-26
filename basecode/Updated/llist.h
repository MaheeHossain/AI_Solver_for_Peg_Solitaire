/*
   this is Alistair's  listops.c 
*/
#ifndef _LIST_
#define _LIST_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

typedef struct node lnode_t;

typedef void* data_t;

struct node {
	data_t *data;
	lnode_t *next;
};

typedef lnode_t *list_t;

list_t createList(); 
list_t insert(data_t *data, list_t list);
void free_list(list_t list);


#endif

/**
 * Taken from Anh's solution for Assignment 1
 */