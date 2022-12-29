#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
// @TODO rm bellow
#include <stdio.h> // @TODO replace by my printf
int	waiting = 1;

void	handle(int sig)
{
	(void) sig;
	waiting = 0;
}

int	main(void)
{
	printf("My PID is: %d\n", getpid());
	signal(SIGUSR1, handle);
	while (waiting)
		;
}
