/**
 * Authors: Tornike Bakuradze (Github: tokobaku)
 * 			Davit Kuzanashvili (Github: DavidKuzanashvili)
 * Created: 04.03.2019
 * Last Update: 04.03.2019
 * 
 * Copyright: well, do whatever you want. keeping this copyright notice would be appreciated,
 *  but you don't really have to :)
 */

/** DOCUMENTATION
 * 
 * C implementation of linked list
 *
 * !!! DANGER !!!
 * since it is a header-only library it doesn't hide any member of structs
 * do not change or modify them unless you are sure it won't do any harm
 * 
 * this library was made to provide stl for C language
 * 
 * USAGE:
 * before using you have to type CSTL_DECL_NEW_LIST_TYPE(<type>) in a global scope
 * e.g. if you want list of ints type CSTL_DECL_NEW_LIST_TYPE(int)
 * this declaration is typedef friendly: CSTL_DECL_NEW_LIST_TYPE(size_t) is valid
 * but if you have struct foo{...}; it's not valid to use CSTL_DECL_NEW_LIST_TYPE(foo)
 * 	or CSTL_DECL_NEW_LIST_TYPE(struct foo)
 * instead do: typedef struct foo{...} foo_t; and then: CSTL_DECL_NEW_LIST_TYPE(foo_t)
 * 
 * API REFERENCE:
 * CSTL_DECL_NEW_LIST_TYPE(<type>) will generate these functions, structs and typedefs for you:
 * cstl_list_<type> - linked list;
 * cstl_list_<type>_node - node of linked list;
 * 
 * e.g. if you do CSTL_DECL_NEW_LIST_TYPE(int) you will get:
 * cstl_list_int - linked list of ints
 * cstl_list_int_node - node of linked list of ints
 * 
 * CONSTRUCTORS:
 * new_cstl_list_<type> ():
 * 	returns: cstl_list_<type>* pointing to empty list. an empty list contains
 * 	two nodes first and last and one int size = 0 representing the number of
 * 	elements in the list. DO NOT MODIFY THEM, it might crash your programm
 * 	and cause a lot of problems.
 * 
 * cstl_list_<type>_clone (const cstl_list_<type> *list):
 * 	arguements: list - a valid poiner to cstl_list_<type> or NULL
 * 	returns: cstl_list_<type>* which is a clone of original list passed as arguement.
 * 	after calling this function modifing the cloned list won't affect the original and vice versa.
 * 
 * cstl_list_<type>_copy (const cstl_list_<type> *src, cstl_list_<type> *dest):
 * 	arguements: src - a valid pointer to cstl_list_<type> or NULL,
 * 				dest - a valid pointer to cstl_list_<type> or NULL
 * 	returns: void
 * 	copies src to dest. after calling this function it is guaranteed that modifiend src won't affect
 * 	dest and vice versa. 
 * 
 * new_cstl_list_<type>_node ():
 * 	returns: cstl_list_<type>_node* pointing to node. all bytes filled with 0.
 * 	this consturctor is used by library itself there is no need of using it.
 * 
 * DESTRUCTOR:
 * free_cstl_list_<type> (cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to list or NULL
 * 	destructs list. do not use std's free it will cause memory leaks.
 * 
 * ITERATORS:
 * cstl_list_<type>_first (const cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to cstl_list_<type> or NULL
 * 	returns: cstl_list_<type>_node* pointing to first node of the list or NUL if list is NULL
 * 	please **NOTE** that returned node is out of the range of the list elements. if you want to access
 * 	node pointing to first element use cstl_list_<type>_front (const cstl_list_<type> *list)
 * 	just like in c++ list::first() and list::front()
 * 
 * cstl_list_<type>_last (const cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to cstl_list_<type> or NULL
 * 	returns: cstl_list_<type>_node* pointing to last node of the list or NULL if list is  NULL
 * 	please **NOTE** that returned node is out of the range of the list elements. if you want to access
 * 	node pointing to last element use cstl_list_<type>_back (const cstl_list_<type> *list)
 * 	just like int c++ list::last() and list::back()
 * 
 * cstl_list_<type>_front (const cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to cstl_list_<type> or NULL
 * 	returns: cstl_list_<type>_node* pointing to first element of the list (element added by user) or NULL
 * 	if there isn't any or list is NULL
 * 
 * cstl_list_<type>_back (const cstl_list_<type> *list):
 * arguements: list - a valid pointer to cstl_list_<type> or NULL
 * returns: cstl_list_<type>_node* pointing to last element of the list (element added by user) or NULL
 * if there isn't any or list is NULL
 * 
 * CAPACITY:
 * cstl_list_<type>_size (const cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to cstl_list_<type> or NULL
 * 	returns: size_t number of elements in list. if list is NULL or empty 0 is returned
 * 
 * cstl_list_<type>_empty (const cstl_list_<type> *list):
 * 	arguements: list - a valid pointer to cstl_list_<type> or NULL
 * 	returns: true if list isn't emtpy or NULL, otherwise false
 * 
 * 
 * 
 */

#ifndef __CSTL_LIST_HEADER__
#define __CSTL_LIST_HEADER__

#include <stdlib.h>

#define CSTL_DECL_NEW_LIST_TYPE(type)\
typedef struct s_cstl_list_##type##_node {\
	struct s_cstl_list_##type##_node *prev;\
	struct s_cstl_list_##type##_node *next;\
	type data;\
} cstl_list_##type##_node;\
\
typedef struct s_cstl_list_##type {\
	cstl_list_##type##_node *first;\
	cstl_list_##type##_node *last;\
	size_t size;\
} cstl_list_##type;\
\
cstl_list_##type##_node* new_cstl_list_##type##_node () {\
	cstl_list_##type##_node *node = (cstl_list_##type##_node*)calloc(1, sizeof(cstl_list_##type##_node));\
	return node;\
}\
\
cstl_list_##type* new_cstl_list_##type () {\
	cstl_list_##type *list = (cstl_list_##type*)calloc(1, sizeof(cstl_list_##type));\
	list->first = new_cstl_list_##type##_node();\
	list->last = new_cstl_list_##type##_node();\
	list->first->next = list->last;\
	list->last->prev = list->first;\
	return list;\
}\
\
cstl_list_##type##_node* cstl_list_##type##_add (cstl_list_##type *list, type value) {\
	cstl_list_##type##_node *node = new_cstl_list_##type##_node();\
	node->next = list->last;\
	node->prev = list->last->prev;\
	node->data = value;\
	list->last->prev->next = node;\
	list->last->prev = node;\
	list->size++;\
	return node;\
}\
\
cstl_list_##type##_node* cstl_list_##type##_remove (cstl_list_##type *list, cstl_list_##type##_node *node) {\
	if (node->prev != NULL)\
		node->prev->next = node->next;\
	if (node->next != NULL)\
		node->next->prev = node->prev;\
	cstl_list_##type##_node *result = node->next;\
	free(node);\
	list->size--;\
	return result;\
}\
\
cstl_list_##type##_node* cstl_list_##type##_first (const cstl_list_##type *list) {\
	if (list == NULL) return NULL;\
	if (list->size == 0) return NULL;\
	return list->first->next;\
}\
\
cstl_list_##type##_node* cstl_list_##type##_last (const cstl_list_##type *list) {\
	if (list == NULL) return NULL;\
	if (list->size == 0) return NULL;\
	return list->first->next;\
}\
\
cstl_list_##type##_node* cstl_list_##type##_front (const cstl_list_##type *list) {\
	if (list == NULL) return NULL;\
	if (list->size == 0) return NULL;\
	return list->first->next;\
}\
cstl_list_##type##_node* cstl_list_##type##_back (const cstl_list_##type *list) {\
	if (list == NULL) return NULL;\
	if (list->size == 0) return NULL;\
	return list->last->prev;\
}\
\
size_t cstl_list_##type##_size (const cstl_list_##type *list) {\
	if (list == NULL) return 0;\
	return list->size;\
}\
\
_Bool cstl_list_##type##_empty (const cstl_list_##type *list) {\
	if (list == NULL) return 0;\
	if (list->size != 0) return 1;\
	return 0;\
}\
\
type cstl_list_##type##_node_data (const cstl_list_##type##_node *node) {\
	return node->data;\
}\
\
void free_cstl_list_##type (cstl_list_##type *list) {\
	cstl_list_##type##_node *first = list->first;\
	while (first != NULL) {\
		first = cstl_list_##type##_remove(list, first);\
	}\
	free(list);\
}\
\
void cstl_list_##type##_sort (cstl_list_##type *list) {\
	if (list->size < 2)\
		return;\
	cstl_list_##type *l1 = new_cstl_list_##type();\
	cstl_list_##type *l2 = new_cstl_list_##type();\
	cstl_list_##type##_node *node = cstl_list_##type##_first(list);\
	for (int i = 0; i < list->size / 2; ++i) {\
		cstl_list_##type##_add(l1, node->data);\
		node = node->next;\
	}\
	for (int i = list->size / 2; i < list->size; ++i) {\
		cstl_list_##type##_add(l2, node->data);\
		node = node->next;\
	}\
	cstl_list_##type##_sort(l1);\
	cstl_list_##type##_sort(l2);\
	cstl_list_##type##_node *n1 = cstl_list_##type##_first(l1);\
	cstl_list_##type##_node *n2 = cstl_list_##type##_first(l2);\
	node = cstl_list_##type##_first(list);\
	for (int i = 0; i < list->size; ++i) {\
		if (n1 == NULL) {\
			node->data = n2->data;\
			n2 = n2->next;\
			node = node->next;\
			continue;\
		}\
		if (n2 == NULL) {\
			node->data = n1->data;\
			n1 = n1->next;\
			node = node->next;\
			continue;\
		}\
		if (n1->data < n2->data) {\
			node->data = n1->data;\
			n1 = n1->next;\
			if (n1->next == NULL)\
				n1 = NULL;\
		} else {\
			node->data = n2->data;\
			n2 = n2->next;\
			if (n2->next == NULL)\
				n2 = NULL;\
		}\
		node = node->next;\
	}\
	free_cstl_list_##type(l1);\
	free_cstl_list_##type(l2);\
}\
\
void cstl_list_##type##_customsort (cstl_list_##type *list, _Bool (*pred)(type a, type b)) {\
	if (list->size < 2)\
		return;\
	cstl_list_##type *l1 = new_cstl_list_##type();\
	cstl_list_##type *l2 = new_cstl_list_##type();\
	cstl_list_##type##_node *node = cstl_list_##type##_first(list);\
	for (int i = 0; i < list->size / 2; ++i) {\
		cstl_list_##type##_add(l1, node->data);\
		node = node->next;\
	}\
	for (int i = list->size / 2; i < list->size; ++i) {\
		cstl_list_##type##_add(l2, node->data);\
		node = node->next;\
	}\
	cstl_list_##type##_customsort(l1, pred);\
	cstl_list_##type##_customsort(l2, pred);\
	cstl_list_##type##_node *n1 = cstl_list_##type##_first(l1);\
	cstl_list_##type##_node *n2 = cstl_list_##type##_first(l2);\
	node = cstl_list_##type##_first(list);\
	for (int i = 0; i < list->size; ++i) {\
		if (n1 == NULL) {\
			node->data = n2->data;\
			n2 = n2->next;\
			node = node->next;\
			continue;\
		}\
		if (n2 == NULL) {\
			node->data = n1->data;\
			n1 = n1->next;\
			node = node->next;\
			continue;\
		}\
		if (pred(n1->data, n2->data)) {\
			node->data = n1->data;\
			n1 = n1->next;\
			if (n1->next == NULL)\
				n1 = NULL;\
		} else {\
			node->data = n2->data;\
			n2 = n2->next;\
			if (n2->next == NULL)\
				n2 = NULL;\
		}\
		node = node->next;\
	}\
	free_cstl_list_##type(l1);\
	free_cstl_list_##type(l2);\
}\
\
cstl_list_##type* cstl_list_##type##_clone (const cstl_list_##type *list) {\
	if (list == NULL)\
		return NULL;\
	cstl_list_##type *result = new_cstl_list_##type();\
	cstl_list_##type##_node *node = cstl_list_##type##_first(list);\
	if (node) {\
		while (node->next != NULL) {\
			cstl_list_##type##_add(result, node->data);\
			node = node->next;\
		}\
	}\
	return result;\
}\
\
void cstl_list_##type##_copy (const cstl_list_##type *src, cstl_list_##type *dest) {\
	free_cstl_list_##type(dest);\
	dest = cstl_list_##type##_clone(src);\
}\
\
_Bool cstl_list_##type##_equals (const cstl_list_##type *l1, const cstl_list_##type *l2) {\
	if (l1 == l2)\
		return 1;\
	if (l1->size != l2->size)\
		return 0;\
	if (l1->size == 0)\
		return 1;\
	cstl_list_##type##_node *n1 = cstl_list_##type##_first(l1);\
	cstl_list_##type##_node *n2 = cstl_list_##type##_first(l2);\
	while (n1->next != NULL) {\
		if (n1->data != n2->data)\
			return 0;\
		n1 = n1->next;\
		n2 = n2->next;\
	}\
	return 1;\
}

#define foreach(type, list, node)\
for (cstl_list_##type##_node *node = list->first->next; node != list->last; node = node->next)

#endif