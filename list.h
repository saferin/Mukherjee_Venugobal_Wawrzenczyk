/*
 * list.h
 *
 *  Created on: Sep 2, 2015
 *      Author: ogruber
 */

#ifndef LIST_H_
#define LIST_H_

typedef int status_t;
#define STATUS_OK 0
#define STATUS_ERR -1

struct list_element;
struct list;

/**
 * Create new list
 *
 * @return pointer to created list
 */
extern struct list* new_list();

/**
 * Returns the  size of a given list
 *
 * @param list  : the pointer to the list
 * @return int  : size
 */
extern int list_size(struct list* list);

/**
 * Returns the element at the position passed as argument
 *
 * @param list : the pointer to the list
 * @param i	   : the position, 0 is position of the first element in the list
 */
extern void* list_element_at(struct list* list, int i);

/**
 * Attach an element at the end of the list
 *
 * @param list		: the pointer to the list
 * @param element	: the element that is supposed to be attached
 */
extern void list_append(struct list* list, void* element);

/**
 * Attach an element at the front of the list
 *
 * @param list		: the pointer to the list
 * @param element	: the element to be added
 */
extern void list_prepend(struct list* list, void* element);

/**
 * Inserts an element to the list just before the mark
 *
 * @param list		: the pointer to the list
 * @param mark		: the element before which new element should be inserted
 * @param element	: the element to be added
 * @return			: id of mark before which new element was inserted, -1 if mark was not found
 */
extern int list_insert_before_element(struct list* list, void* mark, void* element);

/**
 * Inserts an element to the list just after the mark
 *
 * @param list		: the pointer to the list
 * @param mark		: the element after which new element should be inserted
 * @param element	: the element to be added
 * @return			: id of mark after which new element was inserted if BUGS are not defined, -1 if mark was not found
 */
extern int list_insert_after_element(struct list* list, void* mark, void* element);

/**
 * Insert an element before the index i
 *
 * @param list		: the pointer to the list
 * @param i			: the index before which new element should be inserted, 0 is the first index
 * @param element	: the element to be added
 */
extern void list_insert_before_index(struct list* list, int i, void* element);

/**
 * Insert an element after the index i
 *
 * @param list		: the pointer to the list
 * @param i			: the index after which new element should be inserted, 0 is the first index
 * @param element	: the element to be added
 */
extern void list_insert_after_index(struct list* list, int i, void* element);

/**
 * Remove the element at the index i
 *
 * @param list	: the pointer to the list
 * @param i		: the index i, 0 is the first index
 * @return		: the pointer to the removed element or NULL if list is empty
 */
extern void* list_remove_at_index(struct list* list, int i);

/**
 * Find the element and remove it
 *
 * @param list		: the pointer to the list
 * @param mark		: the element to be removed
 * @return			: id of removed element
 */
extern int list_remove_(struct list* list, void* mark);


#endif /* LIST_H_ */
