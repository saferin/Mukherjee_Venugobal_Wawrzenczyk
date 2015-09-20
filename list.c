/*
 * list.c
 *
 *  Created on: Sep 2, 2015
 *      Author: ogruber
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
#ifndef BUGS
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
#endif
	// NOTE: if BUGS is defined and list->size == 0 program crashes in list_insert_after_index
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
	// SUGGESTION: if (idx > list->size) perror("id is greater than the lists size!");
	// SUGGESTION: if (idx < 0) perror("id must be greater than 0!");
	struct list_entry *pos;
	pos = list->head;
	// NOTE: if idx > list->size function crashes
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
	// NOTE: if mark is not found new element will be inserted before last element
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}
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
	// NOTE: if mark is not found new element will be inserted at the end
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		pos = pos->next;
	}
	// create list_entry for element to insert
	struct list_entry *niu;
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

	// insert element after mark
	niu->next = pos->next;
	pos->next = niu;
	list->size++;
#ifndef BUGS
	return idx;	// return id of element after which new one was inserted
#endif
	// NOTE: if BUGS is defined nothing is returned by this function
}

void list_insert_before_index(struct list* list, int idx, void* element) {
	// SUGGESTION: if (idx > list->size) perror("id is greater than the lists size!");
	// SUGGESTION: if (idx < 0) perror("id must be greater than 0!");

	struct list_entry *prev = NULL;
	struct list_entry *pos;
	pos = list->head;
	// search for the element before which new element is inserted
	// if the idx > list->size function crushes
	// SUGGESTION: for (int i = 0; i < idx && pos; i++) {
	for (int i = 0; i < idx; i++) {
		prev = pos;
		pos = pos->next;
	}
	struct list_entry *niu;

 // NOTE: if BUGS is defined allocation is wrong
#ifdef BUGS
	niu = malloc(sizeof(struct list_entry*));
#else
	niu = malloc(sizeof(struct list_entry));
#endif
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
	// SUGGESTION: if (idx > list->size) perror("id is greater than the lists size!");
	// SUGGESTION: if (idx < 0) perror("id must be greater than 0!");

	// create list_entry for element to insert
	struct list_entry *pos;
	pos = list->head;
	// search for the id after which new element will be inserted
	// if id > list->size function crushes
	// SUGGESTION: for (int i = 0; i < idx && pos; i++) {
	for (int i = 0; i < idx; i++) {
		pos = pos->next;
	}
	struct list_entry *niu;
// NOTE: if BUGS is defined allocation is wrong
#ifdef BUGS
  niu = malloc(sizeof(struct list_entry*));
#else
  niu = malloc(sizeof(struct list_entry));
#endif
	memset(niu, 0, sizeof(struct list_entry));

	// insert element to the list
	niu->elem = element;
	niu->next = pos->next;
	pos->next = niu;
	list->size++;
}

void* list_remove_at_index(struct list* list, int idx) {
	// SUGGESTION: if (idx > list->size) perror("id is greater than the lists size!");
	// SUGGESTION: if (idx < 0) perror("id must be greater than 0!");

	// SUGGESTION: if(list_size(list) == 0) return NULL;

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
#ifdef BUGS
		list->head = pos;
#else
	    list->head = pos->next;
#endif
	// NOTE: if BUGS is defined function crashes - in the next step pos is deleted

	list->size--;
	void* elem = pos->elem;
	free(pos);
	return elem;
}

int list_remove_(struct list* list, void* mark) {
	struct list_entry *prev = NULL;
	struct list_entry *pos;
#ifdef BUGS
	int idx;
#else
	int idx=0;
#endif
	// NOTE: if BUGS is defined idx isn't initialised - function crashes

	pos = list->head;

	// search for the marked element to be removed
	// NOTE: if mark is not found last element in the list is removed
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}

	// remove element from the list
	if (prev)
		prev->next = pos->next;
	else
		list->head = pos->next;
	list->size--;
#ifndef BUGS
	free(pos);
#endif
	// if BUGS is defined pos isn't freed - memory leak

	return idx;
}

