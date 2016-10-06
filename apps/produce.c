#include <prodcons.h>

void producer(int count) {

	int i;
	for(i=1;i<=count;i++){
		wait(consumed);

	        /* CRITICAL SECTION */
		n = i; // this is the only place where 'n' will be updated
		printf("produced : %d\n", n);

		signal(produced);
	}
}



