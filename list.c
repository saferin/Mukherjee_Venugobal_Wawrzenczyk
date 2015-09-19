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
		struct list_entry *niu;
		niu = malloc(sizeof(struct list_entry));
		memset(niu, 0, sizeof(struct list_entry));
		niu->elem = element;
		list->head = niu;
		list->size = 1;
	} else
#endif
		list_insert_after_index(list, list->size - 1, element);
}

void list_prepend(struct list* list, void* element) {
	if (list->size == 0) {
		struct list_entry *niu;
		niu = malloc(sizeof(struct list_entry));
		memset(niu, 0, sizeof(struct list_entry));
		niu->elem = element;
		list->head = niu;
		list->size = 1;
	} else
		list_insert_before_index(list, 0, element);
}

//Aveek: This is going to crash if idx > size
void* list_element_at(struct list* list, int idx) {
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
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}
	struct list_entry *niu;
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

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

/*
 * My territory ends
 */
//Aveek : if mark not there, insert at tail, but return value is same as inserting after head
int list_insert_after_element(struct list* list, void* mark, void* element) {
	struct list_entry *pos;
	int idx = 0;
	pos = list->head;
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		pos = pos->next;
	}
	struct list_entry *niu;
	niu = malloc(sizeof(struct list_entry));
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;

	niu->next = pos->next;
	pos->next = niu;
	list->size++;
#ifndef BUGS
	return idx;
#endif
}

//Aveek : niu = malloc(sizeof(struct list_entry*));
void list_insert_before_index(struct list* list, int idx, void* element) {
	struct list_entry *prev = NULL;
	struct list_entry *pos;
	pos = list->head;
	for (int i = 0; i < idx; i++) {
		prev = pos;
		pos = pos->next;
	}
	struct list_entry *niu;
#ifdef BUGS
	niu = malloc(sizeof(struct list_entry*));
#else
	niu = malloc(sizeof(struct list_entry));
#endif
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;
	if (prev) {
		niu->next = prev->next;
		prev->next = niu;
	} else {
		niu->next = list->head;
		list->head = niu;
	}
	list->size++;
}

//Aveek : niu = malloc(sizeof(struct list_entry*));, no checking for idx > size
void list_insert_after_index(struct list* list, int idx, void* element) {
	struct list_entry *pos;
	pos = list->head;
	for (int i = 0; i < idx; i++) {
		pos = pos->next;
	}
	struct list_entry *niu;
#ifdef BUGS
  niu = malloc(sizeof(struct list_entry*));
#else
  niu = malloc(sizeof(struct list_entry));
#endif
	memset(niu, 0, sizeof(struct list_entry));
	niu->elem = element;
	niu->next = pos->next;
	pos->next = niu;
	list->size++;
}

//Aveek : cant be called on an empty list. It will crash;
void* list_remove_at_index(struct list* list, int idx) {
	//Suggestion
	if(list_size(list) ==0)
		return NULL;

	struct list_entry *prev = NULL;
	struct list_entry *pos;
	pos = list->head;
	for (int i = 0; i < idx; i++) {
		prev = pos;
		pos = pos->next;
	}
	if (prev)
		prev->next = pos->next;
	else
#ifdef BUGS
		list->head = pos;
#else
	    list->head = pos->next;
#endif
	list->size--;
	void* elem = pos->elem;
	free(pos);
	return elem;
}
//Aveek : idx shud be inittialised, we shud free pos to avoid memory leak
int list_remove_(struct list* list, void* mark) {
	struct list_entry *prev = NULL;
	struct list_entry *pos;
#ifdef BUGS
	int idx;
#else
	int idx=0;
#endif
	pos = list->head;
	while (pos) {
		if (pos->elem == mark)
			break;
		idx++;
		prev = pos;
		pos = pos->next;
	}
	if (prev)
		prev->next = pos->next;
	else
		list->head = pos->next;
	list->size--;
#ifndef BUGS
	free(pos);
#endif
	return idx;
}

