#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
// @TODO rm include bellow
#include <stdlib.h>
void	send_char(__pid_t pid, char c)
{
	int	i;

	i = -1;
	while (++i < (int)sizeof(char) * 8)
	{
		kill(pid, (int []){SIGUSR1, SIGUSR2}[(c >> i) & 1]);
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return ((write(STDOUT_FILENO, "You need 2 args : server pid and a string", 41), 0));

	// @TODO verif argv[1] is a pid
	i = -1;
	while ((i == -1 && i++) || argv[2][i++])
		send_char(atoi(argv[1]), argv[2][i]);
}
