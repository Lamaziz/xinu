#include <xinu.h>
#include <prodcons.h>

int n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/

shellcmd xsh_prodcons(int nargs, char *args[])
{
  //Argument verifications and validations
	/* Output info for '--help' argument */
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\t It is a demo pf producer and concumer problem.It will run producer and consumer procss fo N times whwew N is defined by user ,otheewise it will run 2000 times!\n");
		printf("Options (one per invocation):\n");
		printf("\t<integer>\t its option for user to write an integer N\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	/* Check argument count */
	if (nargs > 2) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
			args[0]);
		return 1;
	}

  char* countStr = NULL;
  int intValue;
  int count = 2000;             //local varible to hold count
  //check args[1] if present assign value to count
	if (nargs == 2) {
		/*
			args[1] =	20		// correct input, everthing else is bad input
						+20
						-20
						abc
						2.95
						-2.95
						+2.95
		*/
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
  
//create the process producer and consumer and put them in ready queue.
  //Look at the definations of function create and resume in the system folder for reference.      
  resume( create(producer, 1024, 20, "producer", 1, count));
  resume( create(consumer, 1024, 20, "consumer", 1, count));
  return (0);
}