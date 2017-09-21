/*
 * test_suite.c
 *
 *  Created on: Sep 21, 2017
 *      Author: lgerber
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdu_parser.h"
#include "pdu_templates.h"
#include "pdu_creator.h"
#include "message_byte_array.h"


int main(int argc, char*argv[]){

	uint32_t length = 0;
	message_byte_array *MBA;




	/*
	 * Test REG
	 */
	printf("\n\nREG\n");

	// Create REG struct and add 1 server name
	pdu_REG *REG = create_REG(10,2000);
	REG->add_server_name(REG,"servername");

	// Create REG byte stream message to send
	MBA = REG->create_message(REG);
	length = get_length_REG(REG);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free REG and MBA
	free_pdu_reg(REG);
	free_message_byte_array(MBA);



	/*
	 * Test ALIVE
	 */
	printf("\n\nALIVE\n");

	// Create ALIVE struct
	pdu_ALIVE *ALIVE = create_ALIVE(100, 10000);

	// Create ALIVE byte stream message to send
	MBA = ALIVE->create_message(ALIVE);
	length = get_length_ALIVE(ALIVE);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free REG and MBA
	free_pdu_alive(ALIVE);
	free_message_byte_array(MBA);



	/*
	 * Test ACK
	 */
	printf("\n\nACK\n");

	// Create ACK struct
	pdu_ACK *ACK = create_ACK(10000);

	// Create ACK byte stream message to send
	MBA = ACK->create_message(ACK);
	length = get_length_ACK(ACK);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free ACK and MBA
	free_pdu_ack(ACK);
	free_message_byte_array(MBA);




	/*
	 * Test NOTREG
	 */
	printf("\n\nNOTREG\n");

	// Create NOTREG struct
	pdu_NOTREG *NOTREG = create_NOTREG(10000);

	// Create NOTREG byte stream message to send
	MBA = NOTREG->create_message(NOTREG);
	length = get_length_NOTREG(NOTREG);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free NOTREG and MBA
	free_pdu_notreg(NOTREG);
	free_message_byte_array(MBA);



	/*
	 * GETLIST
	 */
	printf("\n\nGETLIST\n");

	// Create GETLIST struct
	pdu_GETLIST *GETLIST = create_GETLIST();

	// Create GETLIST byte stream message to send
	MBA = GETLIST->create_message(GETLIST);
	length = get_length_GETLIST(GETLIST);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free GETLIST and MBA
	free_pdu_getlist(GETLIST);
	free_message_byte_array(MBA);




	/*
	 * SLIST
	 */
	printf("\n\nSLIST\n");

	// Create SLIST struct
	pdu_SLIST *SLIST = create_SLIST(1);
	uint8_t address[4] = {127,0,0,1};
	pdu_server_entry* server1 = create_server_entry(address,2000,4,10);
	server1->add_server_name(server1, "servername");
	SLIST->add_server_entry(SLIST, server1);

	MBA = SLIST->create_message(SLIST);
	length = get_length_SLIST(SLIST);
	printf("Length of message = %d\n", length);

	for(int i = 0; i < length; i++){
		printf("%d, ", MBA->array[i]);
	}

	// free SLIST and MBA
	free_pdu_slist(SLIST);
	free_message_byte_array(MBA);



	/*
	 * JOIN
	 */

	printf("\n\nJOIN\n");

	//Create JOIN and add identity
	pdu_JOIN *JOIN = create_JOIN(8);
	JOIN->add_identity(JOIN, "identity");

	// Create join byte stream message to send
	MBA = JOIN->create_message(JOIN);
	length = get_length_JOIN(JOIN);

	for(int i = 0; i < length; i++){
		printf("%d, ", MBA->array[i]);
	}

	// free JOIN and MBA
	free_pdu_join(JOIN);
	free_message_byte_array(MBA);


/*
	//Example create PARTICIPANTS
	pdu_PARTICIPANTS *PARTICIPANTS = create_PARTICIPANTS(3, 15);
	PARTICIPANTS->add_identities(PARTICIPANTS, "bull\0shit\0crap\0");
	for(int i = 0; i < PARTICIPANTS->number_identities;i++){
		printf("%s\n", PARTICIPANTS->identities[i]);
	}
	free_pdu_participants(PARTICIPANTS);


	pdu_MESS *MESS = create_MESS(8, 45);
	MESS->add_message(MESS, 64, 1505933137, "Now this is ä very funny story that I gonna unfold for you here.");
	MESS->add_client_identity(MESS, "bullcrap");
	printf("%s\n", MESS->message);
	free_pdu_mess(MESS);

	message_byte_array *array = create_message_byte_array(10);
    //char* cp = "z";
	array->add_uint32(array, 12312);
	array->add_uint32(array, 23234);
    array->add_chars(array,"abcd", 1);

	for(int i = 0;i < 12;i++){
		printf("%d, ", array->array[i]);
	}
	*/




	return 0;
}

