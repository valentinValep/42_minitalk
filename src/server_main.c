#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
// @TODO rm includes bellow
#include <stdio.h>

void	handler(int sig)
{
	static int	i;
	static char	c;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	c += (sig == SIGUSR2) << i;
	i++;
	if (i == sizeof(char) * 8)
	{
		if (c)
			write(STDOUT_FILENO, &c, 1);
		else
			write(STDOUT_FILENO, "\n", 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	printf("Program PID : %d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
