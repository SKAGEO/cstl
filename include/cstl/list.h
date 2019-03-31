/** STRUCTURE
 * 
 * C implementation of doubly linked list (dll)
 * 
 * every list (even empty the one) contains two nodes: head and tail.
 * head node can't have previous node and no node's next node can be head
 * (there is no node at the left hand side of the head node)
 * 
 * tail node can't have next node and no node's previous node can be tail
 * (there is no node at the right hand side of the tail node)
 * 
 * initially every list looks like this:
 *  ______        ______
 * |      |      |      |
 * | head | <--> | tail |
 * |______|      |______|
 * 
 * every new node is added between head and tail:
 * 
 *  ______        ____________        ______________                 ______
 * |      |      |            |      |              |               |      |
 * | head | <--> | added node | <--> | another node | <--> ... <--> | tail |
 * |______|      |____________|      |______________|               |______|
 * 
 * node contains pointer to previous node, data it holds and pointer to next node
 * 
 * cstl_listNode *previous, void *data, cstl_listNode *next;
 */

#ifndef __CSTL_LIST_HEADER__
#define __CSTL_LIST_HEADER__


#endif