#include <xinu.h>
#include <prodcons.h>

void consumer(int count)
{
	while((0<n) && (n<=count)) {
		printf("consumed : %d\n", n);

		if(n == count)
			return;
	}
}

