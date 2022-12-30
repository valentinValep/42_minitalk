#include "server.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
// @TODO rm bellow
#include <stdio.h> // @TODO replace by my printf

void	handler(int sig)
{
	static int		i;
	static char		receive;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	receive += (sig == SIGUSR2) << i;
	i++;
	if (i == 8)
	{
		if (!receive)
		{
			write(STDOUT_FILENO, "\n", 1);
			receive = 0;
			i = 0;
			return ;
		}
		printf("<%d>\n", receive);
		write(STDOUT_FILENO, &receive, 1);
		receive = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	printf("My PID is: %d\n", getpid());

	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	//sigaddset(set, SIGUSR1); // Used to block signals @TODO TRY
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	while (1)
		;
}
//sigemptyset
//sigaddset
//sigaction

//pause
//sleep
//usleep
//exit