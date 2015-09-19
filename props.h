/*
 * props.h
 *
 *  Created on: Sep 7, 2015
 *      Author: ogruber
 */

#ifndef PROPS_H_
#define PROPS_H_

struct property {
  char *key;
  char *value;
};

struct properties {
  struct list *props;
};

struct properties *parse_properties(char* chars);

void print_properties(struct properties *props);

#endif /* PROPS_H_ */
