/*
 * stream.c
 *
 *  Created on: 19-Sep-2015
 *      Author: aveekmukherjee
 */

#include <stddef.h>
#include "stdint.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "stream.h"

stream* open(){
	stream *st = NULL;

	st= malloc(sizeof(stream));
	st->comps = new_list();

	return st;
}

int write(stream * st ,const char * buf , int buf_size){
	int status = STATUS_ERR;

	//TODO: break a big buffer into multiple compartments

	//create a new compartment with the buffer
	compartment *cp = malloc(sizeof(compartment));
	cp->buffer = malloc(sizeof(char)*buf_size);
	//copy the bufer into compartment
	memcpy(cp->buffer,buf,buf_size);
	cp->size = buf_size;

	//append the new compartment to the stream list
	list_append(st->comps, (void*)cp);

	return status;
}

int read(stream * st , char * buf , int read_size){
	int status = STATUS_ERR;
	int actual_read = 0;

	if(buf == NULL){
		//If buf is null we should not operate
		return status;
	}

	while(actual_read < read_size){
		//remove the first element
		compartment* cp = (compartment*)list_remove_at_index(st->comps,0);

		if(cp==NULL){
			//we reached the end of list
			return actual_read;
		}

		//calculate how many bytes we are yet to read from stream to buffer
		int yet_to_read = read_size - actual_read;
		//calculate how many bytes from the present compartment needs to be copied to the buffer
		int bytes_to_copy = (yet_to_read > cp->size) ? cp->size : yet_to_read;

		//we actually read 'bytes_to_copy' more
		actual_read += bytes_to_copy;
		memcpy(buf,cp->buffer,bytes_to_copy);

		if(yet_to_read < cp->size){
			/**
			 * if our compartment contained more data than was actually required,
			 * we need to copy back the remaining data back into our stream
			 * in a new compartment
			 */
			int new_size = cp->size - yet_to_read;
			char *buf = malloc(sizeof(char) * new_size);

			//copy the remaining data to the temporary buffer
			memcpy(buf,(cp->buffer+yet_to_read),new_size);

			//free the old buffer
			free(cp->buffer);

			//point to the new buffer
			cp->buffer = buf;
			cp->size = new_size;

			//add back the compartment at front
			list_append(st->comps , (void*)cp);
		}
	}

	return actual_read;
}

int close(stream *st){
	int status = STATUS_ERR;

	do{

	}while();

	return status;
}
