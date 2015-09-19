/*
 * stream.h
 *
 *  Created on: 19-Sep-2015
 *      Author: Aveek Mukherjee
 */

#ifndef STREAM_H_
#define STREAM_H_

/**
 * This represents one compartment in our stream
 * The buffer is a character array
 * At any point size gives us the size of the valid compartment buffer
 */
struct compartment{
	char * buffer;
	int size;
};

typedef struct compartment compartment;

/**
 * A stream is a list of compartments containing buffer
 */
struct stream{
	struct list * comps;
};

typedef struct stream stream;

/**
 * This function opens a stream and returns a pointer to the same
 * @return : a pointer to the stream, NULL on error
 */
stream* open();

/**
 * This function writes a buffer into the stream
 *
 * @param st		: the stream to be written into
 * @param buf		: the buffer to be written into the stream
 * @param buf_size	: the size to be written
 * @return
 */
int write(stream * st , const char * buf , int buf_size);

/**
 * This function attempts to read 'read_size' data from stream into a character buffer.
 * The programmer is responsible for creating the buffer on which the data is to be written.
 * The programmer is also responsible for destroying the buffer.
 *
 * @param st		: the stream to be read from
 * @param buf		: the buffer to be written to
 * @param read_size	: number of bytes to be read
 * @return			: the actual number of bytes read, -1 on error
 */
int read(stream * st , char * buf , int read_size);

/**
 * Closes the stream and deletes all compartments
 * @param st	: the stream to be closed
 * @return		: 0 if closed successfully
 */
int close(stream *st);

#endif /* STREAM_H_ */
