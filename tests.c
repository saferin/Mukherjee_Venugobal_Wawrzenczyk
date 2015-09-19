/*
 * tests.c
 *
 *  Created on: Sep 5, 2015
 *      Author: ogruber
 */

#include <stddef.h>
#include "stdint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include "list.h"
#include "props.h"

#define assert(cond,msg) { \
  if (!(cond)) {\
    printf("FAILURE: %s",msg);\
    exit(-1);  \
  }\
}

unsigned long long nano_time() {
	//timeval is a part of time.h
  unsigned long long result;
  struct timeval tp;
  if (gettimeofday(&tp, NULL) == -1) {
    printf("PANIC: gettimeofday call failed.");
    exit(-1);
  }
  result = (((unsigned long long) tp.tv_sec) * 1000000L);
  result += (((unsigned long long) tp.tv_usec));
  return result * 1000L;
}

#define RANDOM_INSERT_SIZE 1000
#undef ECHO

char* toString(int val) {
  char tmp[64];
  memset(tmp, 0, 64);
  sprintf(tmp, "%d", val);
  int len = strlen(tmp);
  char *str = malloc(len + 1);
  strcpy(str, tmp);
  return str;
}

void random_string_insert_test(struct list *list) {
  int* values = malloc(RANDOM_INSERT_SIZE * sizeof(int));
  memset(values, 0, RANDOM_INSERT_SIZE * sizeof(int));
  int count = 0;
  while (count < RANDOM_INSERT_SIZE) {
    int idx = (int) ((double) (random() * RANDOM_INSERT_SIZE)
        / (double) RAND_MAX);
    while (values[idx] != 0)
      idx = (idx + 1) % RANDOM_INSERT_SIZE;
    int inserted = 0;
    char*str = toString(idx);
#ifdef ECHO
    printf("\n--> val=%d from %s \n", idx, str);
#endif
    for (int i = 0; i < count; i++) {
      char* s = (char*) list_element_at(list, i);
      int mark = atoi(s);
#ifdef ECHO
      printf("  list[%d]=%d from %s \n", i, mark, s);
#endif
      if (mark > idx) {
        list_insert_before_index(list, i, str);
        inserted = 1;
        break;
      }
    }
    if (!inserted)
      list_append(list, str);
    values[idx] = 1;
    count++;
#ifdef ECHO
    print_list("list:", list);
#endif
  }

  for (int i = 0; i < RANDOM_INSERT_SIZE; i++)
    if (i != atoi((char*) list_element_at(list, i))) {
      char *val = (char*) list_element_at(list, i);
      printf("FAILURE! list[%d] != %s \n", i, val);
      exit(-1);
    }
}

struct element {
  int val;
};

void random_struct_insert_test(struct list *list) {
  int* values = malloc(RANDOM_INSERT_SIZE * sizeof(int));
  memset(values, 0, RANDOM_INSERT_SIZE * sizeof(int));
  int count = 0;
  while (count < RANDOM_INSERT_SIZE) {
    int idx = (int) ((double) (random() * RANDOM_INSERT_SIZE)
        / (double) RAND_MAX);
    while (values[idx] != 0)
      idx = (idx + 1) % RANDOM_INSERT_SIZE;
    int inserted = 0;
    struct element*niu = malloc(sizeof(struct element));
    niu->val = idx;
#ifdef ECHO
    printf("\n--> val=%d from %s \n", idx, str);
#endif
    for (int i = 0; i < count; i++) {
      struct element* e = (struct element*) list_element_at(list, i);
      int mark = e->val;
#ifdef ECHO
      printf("  list[%d]=%d from %s \n", i, mark, s);
#endif
      if (mark > idx) {
        list_insert_before_index(list, i, niu);
        inserted = 1;
        break;
      }
    }
    if (!inserted)
      list_append(list, niu);
    values[idx] = 1;
    count++;
#ifdef ECHO
    print_list("list:", list);
#endif
  }

  for (int i = 0; i < RANDOM_INSERT_SIZE; i++)
    if (i != ((struct element*) list_element_at(list, i))->val) {
      struct element *e = (struct element*) list_element_at(list, i);
      printf("FAILURE! list[%d] != %d \n", i, e->val);
      exit(-1);
    }
}

void basic_prop_test() {
  struct properties* props;
  props = parse_properties("");
  assert(props!=NULL, " no properties");
  props = parse_properties("()");
  assert(props!=NULL, " empty properties");
  props = parse_properties("(name,toto)");
  assert(props!=NULL, " toto properties");
  props = parse_properties("(first,toto)(last,titi)");
  assert(props!=NULL, " toto/titi properties");
  props = parse_properties("(first,toto)(last,titi)(surname,tata)");
  assert(props!=NULL, " totot/titi/tata properties");

  printf("Properties: ");
  print_properties(props);
  printf("\n");
}

#define PROP_TEST_SIZE 100000
void perf_prop_test() {
  struct properties* props;
  for (int i = 0; i < PROP_TEST_SIZE; i++) {
    props = parse_properties("(first,toto)(last,titi)(surname,tata)");
    assert(props!=NULL, " totot/titi/tata properties");
  }
}

void run_all_tests() {
  struct list *list;
  unsigned long long start, end;
  start = nano_time();
  list = new_list();
  random_string_insert_test(list);
  end = nano_time();
  printf("String random insert: %llu ms \n", (end - start) / 1000000L);

  start = nano_time();
  list = new_list();
  random_struct_insert_test(list);
  end = nano_time();
  printf("Struct random insert: %llu ms \n", (end - start) / 1000000L);

  /*
  basic_prop_test();

  start = nano_time();
  perf_prop_test();
  end = nano_time();
  printf("Property parsing test: %llu ms \n", (end - start) / 1000000L);
  */
}
