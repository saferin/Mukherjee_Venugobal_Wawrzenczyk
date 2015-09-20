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

* func to parse the i/p chars*/
char* property_parse(char* chars, struct property **ppt) {
  char* key;
  char* value;
  int key_len = 0, value_len = 0;
  /* input validation to chk if the fist character is an open bracket */
  if (chars[0] != '(')
	  /* error thro mechanism */
    goto error;
  /* estimating the no of position in the character sequence */
  char* pos = chars + 1;
  //* iterating each of the character items */
  for (key = pos;; pos++) {
    if (*pos == 0)
      goto error;
    /* traverse to the next  item if the character is a delimiter (,)*/
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
  /* calculating the total no of values in the input */
  value_len = pos - value;
  pos++;
 /* defining prop object as a prop type */
  struct property *prop;
  /* memory allocation */
  prop = malloc(sizeof(struct property));
 /* allocatig the memory for the key */
  prop->key = malloc(key_len + 1);
  /* mem allocayion */
  memcpy(prop->key, key, key_len);
  /* declaring the end of the element */
  prop->key[key_len] = 0;

  prop->value = malloc(value_len + 1);
  memcpy(prop->value, value, value_len);
  prop->value[value_len] = 0;
/* assign the prop to ppt and returns the value to the respective function call */
  *ppt = prop;
  return pos;
/* error catching */
  error: /**/
  *ppt = NULL;
  return chars;
}
/* Function to parse the character input */
struct properties *parse_properties(char* chars) {
	 /* allocating memory for the properties */
  struct properties *props = malloc(sizeof(struct properties));
  /* function call to create a new list */
  props->props = new_list();
  /* iterating the char items */
  while (*chars != 0) {
	  /*  obj creation for property structure */
    struct property *prop;
    /* parsing property object and char item */
    chars = property_parse(chars, &prop);
    if (prop == NULL)
      break;
    /* add list item function call to add the top item thro prop list */
    list_append(props->props, prop);
  }
  return props;
}
/* iterating each items and printing it */
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
