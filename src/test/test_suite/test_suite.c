/*
 * test_suite.c
 *
 *  Created on: Sep 21, 2017
 *      Author: lgerber
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdu_templates.h"
#include "pdu_creator.h"
#include "message_byte_array.h"
#include "pdu_serializer.h"


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
	printf("Length of message = %d\n", length);


	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
	printf("\n");


	// free REG and MBA
	free_pdu_reg(REG);
	free_message_byte_array(MBA);


	pdu *reg = create_reg(10,2000);
	reg->add_server_name(reg,"servername");

	MBA = reg->create_message(reg);

	length = get_length_reg(reg);

	printf("Length of message = %d\n", length);


	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
    printf("\n");
	// free reg and MBA
	reg->free_pdu(reg);
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
	printf("Length of message = %d\n", length);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
    printf("\n");

	// free REG and MBA
	free_pdu_alive(ALIVE);
	free_message_byte_array(MBA);
    pdu *alive = create_alive(100, 10000);

    // Create ALIVE byte stream message to send
    MBA = alive->create_message(alive);
    length = get_length_alive(alive);
    printf("Length of message = %d\n", length);

    for(int i = 0;i < length;i++){
        printf("%d, ", MBA->array[i]);
    }
    printf("\n");

    // free REG and MBA
    free_alive(alive);
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
    printf("Length of message = %d\n", length);
	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
    printf("\n");

	// free ACK and MBA
	free_pdu_ack(ACK);
	free_message_byte_array(MBA);

    pdu *ack = create_ack(10000);

    // Create ACK byte stream message to send
    MBA = ack->create_message(ack);
    length = get_length_ack(ack);
    printf("Length of message = %d\n", length);
    for(int i = 0;i < length;i++){
        printf("%d, ", MBA->array[i]);
    }
    printf("\n");

    // free ACK and MBA
    free_ack(ack);
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
    printf("Length of message = %d\n", length);
	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
    printf("\n");

	// free NOTREG and MBA
	free_pdu_notreg(NOTREG);
	free_message_byte_array(MBA);

    pdu *notreg = create_notreg(10000);

    // Create NOTREG byte stream message to send
    MBA = notreg->create_message(notreg);
    length = get_length_notreg(notreg);
    printf("Length of message = %d\n", length);
    for(int i = 0;i < length;i++){
        printf("%d, ", MBA->array[i]);
    }
    printf("\n");

    // free NOTREG and MBA
    free_notreg(notreg);
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
    printf("Length of message = %d\n", length);
	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}
    printf("\n");

	// free GETLIST and MBA
	free_pdu_getlist(GETLIST);
	free_message_byte_array(MBA);

    pdu *getlist = create_getlist();

    // Create GETLIST byte stream message to send
    MBA = getlist->create_message(getlist);
    length = get_length_getlist(getlist);
    printf("Length of message = %d\n", length);
    for(int i = 0;i < length;i++){
        printf("%d, ", MBA->array[i]);
    }
    printf("\n");

    // free GETLIST and MBA
    free_getlist(getlist);
    free_message_byte_array(MBA);


	/*
	 * SLIST
	 */
	printf("\n\nSLIST\n");

	// Create SLIST struct
	pdu_SLIST *SLIST = create_SLIST(2);
	uint8_t address[4] = {127,0,0,1};
	pdu_server_entry* server1 = create_server_entry(address,2000,4,10);
	server1->add_server_name(server1, "servername");
	SLIST->add_server_entry(SLIST, server1);

	uint8_t  address2[4] = {127,0,0,2};
	pdu_server_entry* server2 = create_server_entry(address2,2001,4,11);
	server2->add_server_name(server2, "servername2");
	SLIST->add_server_entry(SLIST, server2);

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
	 * PARTICIPANTS
	 */

	printf("\n\nPARTICIPANTS\n");

	//Create PARTICIPANTS and add some identities
	pdu_PARTICIPANTS *PARTICIPANTS = create_PARTICIPANTS(3, 15);
	PARTICIPANTS->add_identities(PARTICIPANTS, "partic\0ipa\0nts\0");


	for(int i = 0; i < PARTICIPANTS->number_identities;i++){
		printf("%s\n", PARTICIPANTS->identities[i]);
	}


	// Create participants byte stream message to send
	MBA = PARTICIPANTS->create_message(PARTICIPANTS);
	length = get_length_PARTICIPANTS(PARTICIPANTS);
	printf("Length of message = %d\n", length);

	for(int i = 0; i < length; i++){
		printf("%d, ", MBA->array[i]);
	}


	// free PARTICIPANTS and MBA
	free_pdu_participants(PARTICIPANTS);
	free_message_byte_array(MBA);


	/*
	 * QUIT
	 */
	printf("\n\nQUIT\n");

	// Create QUIT struct
	pdu_QUIT *QUIT = create_QUIT();

	// Create GETLIST byte stream message to send
	MBA = QUIT->create_message(QUIT);
	length = get_length_QUIT(QUIT);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	// free QUIT and MBA
	free_pdu_quit(QUIT);
	free_message_byte_array(MBA);


	/*
	 * MESS
	 */

	printf("\n\nMESS\n");

	//Create PARTICIPANTS and add some identities

	pdu_MESS *MESS = create_MESS(8, 99);
	MESS->add_message(MESS, 13, 1505933137, "Test Message.");
	MESS->add_client_identity(MESS, "identity");

	printf("%s\n", MESS->message);

	// Create PARTICIPANTS byte stream for send
	MBA = MESS->create_message(MESS);
	length = get_length_MESS(MESS);
	printf("Length of message = %d\n", length);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	free_pdu_mess(MESS);
	free_message_byte_array(MBA);

	/*
	 * PJOIN
	 */

	printf("\n\nPJOIN\n");

	//Create PJOIN and add some identities

	pdu_PJOIN *PJOIN = create_PJOIN(8);
	PJOIN->add_client_identity(PJOIN, 1505933137, "identity");

	printf("%s\n", PJOIN->client_identity);

	// Create PJOIN byte stream for send
	MBA = PJOIN->create_message(PJOIN);
	length = get_length_PJOIN(PJOIN);
	printf("Length of message = %d\n", length);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	free_pdu_pjoin(PJOIN);
	free_message_byte_array(MBA);


	/*
	 * PLEAVE
	 */

	printf("\n\nPLEAVE\n");

	//Create PLEAVE and add some identities

	pdu_PLEAVE *PLEAVE = create_PLEAVE(8);
	PLEAVE->add_client_identity(PLEAVE, 1505933137, "identity");

	printf("%s\n", PLEAVE->client_identity);

	// Create PLEAVE byte stream for send
	MBA = PLEAVE->create_message(PLEAVE);
	length = get_length_PLEAVE(PLEAVE);
	printf("Length of message = %d\n", length);

	for(int i = 0;i < length;i++){
		printf("%d, ", MBA->array[i]);
	}


	free_pdu_pleave(PLEAVE);
	free_message_byte_array(MBA);


	return 0;
}

