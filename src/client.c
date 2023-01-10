#include "libft.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int	received;

void	handler(int sig)
{
	(void) sig;
	received = 1;
}

void	send_char(__pid_t pid, char c)
{
	int	i;

	i = -1;
	while (++i < (int) sizeof(char) * 8)
	{
		kill(pid, (int []){SIGUSR1, SIGUSR2}[(c >> i) & 1]);
		while (!received)
			;
		received = 0;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return ((write(STDOUT_FILENO,
					"You need 2 args : server pid and a string", 41), 0));
	if (kill(ft_atoi(argv[1]), 0))
		return ((write(STDOUT_FILENO, "Invalid PID", 11), 1));
	signal(SIGUSR1, handler);
	i = -1;
	while ((i == -1 && i++) || argv[2][i++])
		send_char(ft_atoi(argv[1]), argv[2][i]);
}