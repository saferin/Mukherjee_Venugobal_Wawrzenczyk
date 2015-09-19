/*
 * list.c
 *
 *  Created on: Sep 19, 2015
 *      Author: zyta
 */

#include <stddef.h>
#include "stdint.h"
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list_entry {
	struct list_entry *next;
	void *elem;
};

struct list {
	struct list_entry * head;
	unsigned int size;
};

struct list* new_list() {
	struct list* list = malloc(sizeof(struct list));
	memset(list, 0, sizeof(struct list));
	return list;
}

int list_size(struct list* list) {
	return list->size;
}

void list_append(struct list* list, void* element) {
	if (list->size == 0) {
		// create new list_entry
		struct list_entry *niu;
		niu = malloc(sizeof(struct list_entry));
		memset(niu, 0, sizeof(struct list_entry));
		// add element to the list
		niu->elem = element;
		list->head = niu;
		list->size = 1;
	} else
	list_insert_after_index(list, list->size - 1, element);
}

void list_prepend(struct list* list, void* element) {
	if (list->size == 0) {
		// create new list_entry
		struct list_entry *niu;
		niu = malloc(sizeof(struct list_entry));
		memset(niu, 0, sizeof(struct list_entry));
		// add element to the list
		niu->elem = element;
		list->head = niu;
		list->size = 1;
	} else
		// add new element at the beginning of list
		list_insert_before_index(list, 0, element);
}

void* list_element_at(struct list* list, int idx) {
	if (idx > list->size) perror("id is greater than the lists size!");
	if (idx < 0) perror("id must be greater than 0!");

	struct list_entry *pos;
	pos = list->head;
	for (int i = 0; i < idx; i++)
		pos = pos->next;
	return pos->elem;
}

int list_insert_before_element(struct list* list, void* mark, void* element) {
	struct list_entry *prev = NULL;
	struct list_entry *pos;
	int idx = 0;
	pos = list->head;
	// search for the mark after which new element will be inserted
	// NOTE: if mark is not found -1 is returned
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}
	if (pos != mark) return -1;

	// create list_entry for element to insert
	struct list_entry *niu;
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

	// insert element before mark
	if (prev) {
		niu->next = prev->next;
		prev->next = niu;
	} else {
		niu->next = list->head->next;
		list->head = niu;
	}
	list->size++;
	return idx;
}


int list_insert_after_element(struct list* list, void* mark, void* element) {
	struct list_entry *pos;
	int idx = 0;
	pos = list->head;
	// search for the mark after which new element will be inserted
	// NOTE: if mark is not found -1 is returned
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		pos = pos->next;
	}
	if (pos != mark) return -1;

	// create list_entry for element to insert
	struct list_entry *niu;
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

	// insert element after mark
	niu->next = pos->next;
	pos->next = niu;
	list->size++;

	return idx;	// return id of element after which new one was inserted
}

void list_insert_before_index(struct list* list, int idx, void* element) {
	if (idx > list->size) perror("id is greater than the lists size!");
	if (idx < 0) perror("id must be greater than 0!");

	struct list_entry *prev = NULL;
	struct list_entry *pos;
	pos = list->head;
	// search for the element before which new element is inserted
	for (int i = 0; i < idx && pos; i++) {
		prev = pos;
		pos = pos->next;
	}
	struct list_entry *niu;

	// create list_entry for element to be inserted
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

	// insert element to the list if id>0
	if (prev) {
		niu->next = prev->next;
		prev->next = niu;
	} else {	// id = 0
		niu->next = list->head;
		list->head = niu;
	}
	list->size++;
}

void list_insert_after_index(struct list* list, int idx, void* element) {
	if (idx > list->size) perror("id is greater than the lists size!");
	if (idx < 0) perror("id must be greater than 0!");

	// create list_entry for element to insert
	struct list_entry *pos;
	pos = list->head;
	// search for the id after which new element will be inserted
	for (int i = 0; i < idx && pos; i++) {
		pos = pos->next;
	}
	struct list_entry *niu;

	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));

	// insert element to the list
	niu->elem = element;
	niu->next = pos->next;
	pos->next = niu;
	list->size++;
}

void* list_remove_at_index(struct list* list, int idx) {
	if (idx > list->size) perror("id is greater than the lists size!");
	if (idx < 0) perror("id must be greater than 0!");

	if(list_size(list) == 0) return NULL;

	struct list_entry *prev = NULL;
	struct list_entry *pos;
	pos = list->head;

	// find element to be removed
	for (int i = 0; i < idx; i++) {
		prev = pos;
		pos = pos->next;
	}

	// remove element from the list
	if (prev)
		prev->next = pos->next;
	else
	    list->head = pos->next;

	list->size--;
	void* elem = pos->elem;
	free(pos);
	return elem;
}

int list_remove_(struct list* list, void* mark) {
	struct list_entry *prev = NULL;
	struct list_entry *pos;

	int idx=0;
	pos = list->head;

	// search for the marked element to be removed
	// NOTE: if mark is not found -1 is returned
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}
	if (pos != mark) return -1;

	// remove element from the list
	if (prev)
		prev->next = pos->next;
	else
		list->head = pos->next;
	list->size--;
	free(pos);

	return idx;
}

