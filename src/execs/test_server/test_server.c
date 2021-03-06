/*
 *  main.c
 *
 *	Main file for server tests
 *
 *	build with: make EXEC=test_server
 *
 *  Created on: Oct 1, 2017
 *  Authors: Lorenz Gerber, Niklas Königsson
 *
 *  Chat client server project
 *  5DV197 Datakom course
 *	GPLv3
 */
#define _BSD_SOURCE
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "tcp_socket.h"
#include "socket_creator.h"
#include "socket_templates.h"
#include "pdu_parser.h"
#include "pdu_creator.h"

#define NUMBER_OF_CLIENTS 256

void * stress_test(void* data);

/*
 * test_server
 *
 * Test program for the chat server. To
 * run the tests, a chat server has to be
 * running on localhost, port 2000.
 * Else, modify the variable address and
 * port to a suitable value (both in main
 * and stress_test().)
 */
int main(int argc, char*argv[]){



	pthread_t thread_handle[NUMBER_OF_CLIENTS];
	for(int i = 0; i < NUMBER_OF_CLIENTS; i++){
		pthread_create(&thread_handle[i], NULL, stress_test, &i);
	}

	for(int i = 0; i < NUMBER_OF_CLIENTS; i++){
		pthread_join(thread_handle[i], NULL);
	}




	sleep(15);

	char address[128];

	gethostname(address, sizeof address);
	//char* address = "hplinuxbox"; // use in case of fixed host name
	int port = 2000;



	io_handler *client;
	pdu *test;



	// establish connection
	client = create_tcp_client_communicator(address, port);
	client->connect(client, 50);



	// create message, should not be echoed as we are not joined
	// we get kicked out
	test = create_mess(0, 0);
	test->add_message(test, 15, 1505933137, "Test Message 1.");
	client->send_pdu(client, test);
	test->free_pdu(test);



	// start again
	client = create_tcp_client_communicator(address, port);
	client->connect(client, 50);


	// try login with emtpy id, should be kicked
	test = create_join(0);
	test->add_identity(test, "");
	client->send_pdu(client, test);
	test->free_pdu(test);


	// start again
	client = create_tcp_client_communicator(address, port);
	client->connect(client, 50);


	// join chat session, should be echoed
	test = create_join(7);
	test->add_identity(test, "client1");
	client->send_pdu(client, test);
	test->free_pdu(test);


	test = NULL;
	// looping until an error happens or we get data
	while(client->status == STATUS_RECEIVE_EMPTY || client->status == 0){
		test = parse_header(client);
	}
	if(client->status != STATUS_RECEIVE_OK){
		printf("something wrong with receive in Client\n");
	}
	client->status = 0;

	test->print(test);
	test->free_pdu(test);
	printf("----\n");



	// send chat message again, should be echoed
	test = create_mess(0, 0);
	test->add_message(test, 15, 1505933137, "Test Message 2.");
	test->set_checksum(test);
	client->send_pdu(client, test);
	test->free_pdu(test);
	test = NULL;


	// close connection, then the chat server should close connection
	client->close(client);
	free_tcp_client_communicator(client);




    return 0;
}

void * stress_test(void* data){

	int rank = *(int*) data;
	printf("thread %d running \n", rank);


	char address[128];

	gethostname(address, sizeof address);
	//char* address = "hplinuxbox"; // use in case of fixed host name
	int port = 2000;

	io_handler *client;
	pdu *test;

	// establish connection
	client = create_tcp_client_communicator(address, port);
	client->connect(client, 50);


	// join chat session, should be echoed
	test = create_join(7);
	test->add_identity(test, "client1");
	client->send_pdu(client, test);
	test->free_pdu(test);

	test = create_mess(0, 0);
	test->add_message(test, 15, 1505933137, "Test Message 1.");
	test->set_checksum(test);
	client->send_pdu(client, test);
	test->free_pdu(test);


	sleep(5);
	return NULL;
}
