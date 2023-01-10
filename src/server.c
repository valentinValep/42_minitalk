#include "server.h"
#include "libft.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	action(int sig, siginfo_t *siginfo, void *context)
{
	static t_handler_storage	store;

	(void) context;
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	store.c += (sig == SIGUSR2) << store.i;
	store.i++;
	if (!store.str.str && ft_init_string(&store.str, NULL))
		exit(1);
	if (store.i == sizeof(char) * 8)
	{
		if (!store.c)
		{
			write(STDOUT_FILENO, store.str.str, store.str.strlen);
			write(STDOUT_FILENO, "\n", 1);
			ft_destroy_string(&store.str);
		}
		else
			if (ft_cat_string(&store.str, (char []){store.c, 0}))
				exit(1);
		store.i = 0;
		store.c = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Program PID : %d\n", getpid());
	act.sa_sigaction = action;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
