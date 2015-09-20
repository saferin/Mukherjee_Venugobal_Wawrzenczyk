/*
 * props.h
 *
 *  Created on: Sep 7, 2015
 *      Author: ogruber
 */

#ifndef PROPS_H_
#define PROPS_H_
/* Structure to hold the values */
struct property {
  char *key;
  char *value;
};
/* structure to define the collection  of the property*/
struct properties {
  struct list *props;
};
/* object for the structure properties*/
struct properties *parse_properties(char* chars);
/* function declaration for - print properties */
void print_properties(struct properties *props);

#endif /* PROPS_H_ */
