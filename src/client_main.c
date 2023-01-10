#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> // @TODO rm and replace by my atoi
#include <stdio.h> // @TODO rm and replace by my ft_printf or use write

void	send_pid(pid_t server_pid)
{
	unsigned int	i;
	const pid_t		my_pid = getpid();

	printf("PID>%d\n", my_pid);
	i = 0;
	while (i < sizeof(pid_t) * 8)
	{
		if (!((my_pid >> i) & 1))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i++;
		sleep(1 / 100);
	}
}

int	*get_verif(void)
{
	static int	res;

	return (&res);
}

void	handler(int sig)
{
	if (sig == SIGUSR1)
		*get_verif() = 1;
}

int	wait_signal(int microseconds)
{
	while (microseconds > 0)
	{
		usleep(10000);
		if (*get_verif())
			return (0);
		microseconds -= 10;
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	int					i;
	int					j;
	pid_t				server_pid;
	struct sigaction	act;

	if (argc != 3)
		return ((printf("You need 2 arg"), 0));

	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);

	server_pid = atoi(argv[1]); // @TODO verif it -> verif int and kill(pid, 0)
	send_pid(server_pid);

	if (wait_signal(5000))
	{
		write(STDOUT_FILENO, "Can't established connection. closing..", 39);
		exit(1);
	}

	i = 0;
	j = 0;
	while (!i || argv[2][i - 1])
	{
		j = 0;
		while (j < 8)
		{
			if (!((argv[2][i] >> j) & 1))
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			j++;
			sleep(1 / 100);
		}
		i++;
	}
}
