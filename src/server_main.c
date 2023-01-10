#include "server.h"
#include <unistd.h>
#include <signal.h>
// @TODO rm bellow
#include <stdio.h> // @TODO replace by my printf

void	reset_client_pid(t_client_pid *client_pid)
{
	client_pid->pid = 0;
	client_pid->is_full = 0;
	client_pid->i = 0;
}

void	get_client_pid(t_client_pid *client_pid, int sig)
{
	client_pid->pid += (sig == SIGUSR2) << client_pid->i;
	client_pid->i++;
	if (client_pid->i == sizeof(pid_t) * 8)
	{
		printf("CLIENT_PID: %d\n",client_pid->pid);
		if (kill(client_pid->pid, SIGUSR1))
			reset_client_pid(client_pid);
		else
			client_pid->is_full = 1;
	}
}

void	handler(int sig)
{
	static int			i;
	static char			receive;
	static t_client_pid	client_pid;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	if (!client_pid.is_full)
	{
		i = 0;
		get_client_pid(&client_pid, sig);
		return ;
	}
	receive += (sig == SIGUSR2) << i;
	i++;
	if (i == 8)
	{
		if (receive)
		{
			write(STDOUT_FILENO, &receive, 1);
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
			reset_client_pid(&client_pid);
		}
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
	sigaddset(&act.sa_mask, SIGUSR1); // Used to block signals @TODO TRY
	//sigaddset(&act.sa_mask, SIGUSR2); // Used to block signals @TODO TRY
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);

	while (1)
		;
}
