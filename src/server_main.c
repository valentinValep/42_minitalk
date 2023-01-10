#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
// @TODO rm includes bellow
#include <stdio.h>

void	handler(int sig)
{
	printf("Signal : %d\n", sig);
}

int	main(void)
{
	printf("Program PID : %d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
