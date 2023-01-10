#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
void	handler(int sig)
{
	static int		i;
	static char		c;
	static t_string	str;

	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	c += (sig == SIGUSR2) << i;
	i++;
	if (!str.str && ft_init_string(&str, NULL))
		exit(1);
	if (i == sizeof(char) * 8)
	{
		if (c)
		{
			if (ft_cat_string(&str, (char []){c, 0}))
				exit(1);
		}
		else
		{
			write(STDOUT_FILENO, str.str, str.strlen);
			write(STDOUT_FILENO, "\n", 1);
			ft_destroy_string(&str);
		}
		i = 0;
		c = 0;
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
