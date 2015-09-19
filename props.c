/*
 * props.c
 *
 *  Created on: Sep 7, 2015
 *      Author: ogruber
 */

#include <stddef.h>
#include "stdint.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "props.h"

char* property_parse(char* chars, struct property **ppt) {
  char* key;
  char* value;
  int key_len = 0, value_len = 0;
  if (chars[0] != '(')
    goto error;
  char* pos = chars + 1;
  for (key = pos;; pos++) {
    if (*pos == 0)
      goto error;
    if (*pos == ',') {
      key_len = pos - key;
      pos += 1;
      value = pos;
      break;
    }
  }
  while (*pos != ')') {
    if (*pos == 0)
      goto error;
    pos++;
  }
  value_len = pos - value;
  pos++;

  struct property *prop;
  prop = malloc(sizeof(struct property));

  prop->key = malloc(key_len + 1);
  memcpy(prop->key, key, key_len);
  prop->key[key_len] = 0;

  prop->value = malloc(value_len + 1);
  memcpy(prop->value, value, value_len);
  prop->value[value_len] = 0;

  *ppt = prop;
  return pos;

  error: /**/
  *ppt = NULL;
  return chars;
}

/**
 *
 * @param chars
 * @return
 */
struct properties *parse_properties(char* chars) {
  struct properties *props = malloc(sizeof(struct properties));
  props->props = new_list();
  while (*chars != 0) {
    struct property *prop;
    chars = property_parse(chars, &prop);
    if (prop == NULL)
      break;
    list_append(props->props, prop);
  }
  return props;
}

void print_properties(struct properties *props) {
  if (props == NULL || list_size(props->props) == 0)
    printf("()");
  else {
    struct property* prop;
    for (int i = 0; i < list_size(props->props); i++) {
      prop = (struct property*) list_element_at(props->props, i);
      printf("(%s,%s)", prop->key, prop->value);
    }
  }
}
