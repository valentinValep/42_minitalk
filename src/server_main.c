#include "server.h"
#include "libft.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	handler(int sig)
{
	static t_handler_storage	store;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	store.c += (sig == SIGUSR2) << store.i;
	store.i++;
	if (!store.str.str && ft_init_string(&store.str, NULL))
		exit(1);
	if (store.i == sizeof(char) * 8)
	{
		if (store.c)
		{
			if (ft_cat_string(&store.str, (char []){store.c, 0}))
				exit(1);
		}
		else
		{
			write(STDOUT_FILENO, store.str.str, store.str.strlen);
			write(STDOUT_FILENO, "\n", 1);
			ft_destroy_string(&store.str);
		}
		store.i = 0;
		store.c = 0;
	}
}

int	main(void)
{
	ft_printf("Program PID : %d\n", getpid());

	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
