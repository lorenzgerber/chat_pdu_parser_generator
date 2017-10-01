/*
 * socket_creator.c
 *
 *  Created on: Oct 1, 2017
 *      Author: lgerber
 */

#include "socket_creator.h"

/**
 * create_dummy_socket
 *
 * This method is used for testing. It creates a socket
 * mock to test the parser functionality.
 */
io_handler* create_dummy_socket(int op_code){
	io_handler *dummy_socket = malloc(sizeof(io_handler));
	dummy_socket->read_head = 0;
	dummy_socket->request_n_word = dummy_socket_request_n_word;

	switch(op_code){
		case PDU_MESS:
			return dummy_socket_mess(dummy_socket);
			break;
		default:
			break;
	}

	return dummy_socket;
}


/**
 * Function read from dummy socket
 *
 * This function is registered in creat_dummy_socket
 *
 */
uint8_t* dummy_socket_request_n_word(struct io_handler *self, int n_word){

	uint8_t* next_read = &self->buffer->array[self->read_head];
	self->read_head += n_word * 4;

	return next_read;
}