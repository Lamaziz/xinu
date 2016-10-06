#include <prodcons.h>

void consumer(int count) {
	for(int i=1;i<=count;i++){
		wait(produced);

		printf("consumed : %d\n",n);

                // NOTE: When we check "n" upto equal value of "count", our consumer method should stop.
		if(n == count) {
	
		        // The deed is done. We have consumed all produced values.
			// Now we must delete the semaphores and return!
			semdelete(produced);
			semdelete(consumed);

	        	return;
	        }

	        signal(consumed);
	}

}

