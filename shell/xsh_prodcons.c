#include <prodcons.h>

int n;                 // Definition for global variable 'n'. Global variables are by default initialized to 0.

sid32 consumed, produced;     // Defination for semaphores

shellcmd xsh_prodcons(int nargs, char *args[]) {

	char* countStr = NULL;
	int intValue;


	/* Output info for '--help' argument */
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tCreates two synchronized processes named producer and consumer which will take integer count as an optional argument\n");
		printf("Options (one per invocation):\n");
		printf("\t[unsigned-integer]\t:\t(OPTINAL PARAMETER) set the producer consumer loop for that many times\n");
		printf("\t[nothing]\t\t:\twith no argument, the producer consuer loop will run 2000 times\n");
		printf("\t--help\t\t\t:\tdisplay this help and exit\n");
		printf("\n");
		return 0;
	}


	//Argument verifications and validations
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		return 1;
	}

	int count = 2000;             //local varible to hold count

   	//check args[1] if present assign value to count
	if (nargs == 2) {
		countStr = &args[1][0];
		intValue = 0;
		while(*countStr != '\0') {
			if (('0' <= *countStr) && (*countStr <= '9')) {
				intValue = (intValue*10) + (*countStr - '0');
			} else {
				fprintf(stderr, "BAD INPUT: \"%s\" is not an unsigned positive integer value\n", args[1]);
				return 1;
			}
			++countStr;
		}
		count = intValue;
		countStr = NULL;
	}


	/*Initialise semaphores*/
	produced = semcreate(0);
	consumed = semcreate(1);

	resume( create(producer, 1024, 20, "producer", 1, count) );
	resume( create(consumer, 1024, 20, "consumer", 1, count) );
	return 0;
}

