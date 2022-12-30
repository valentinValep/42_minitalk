#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> // @TODO rm and replace by my atoi
#include <stdio.h> // @TODO rm and replace by my ft_printf or use write

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 3)
		return ((printf("You need 2 arg"), 0));
	i = 0;
	j = 0;
	while (!i || argv[2][i - 1])
	{
		j = 0;
		while (j < 8)
		{
			if (!((argv[2][i] >> j) & 1))
				kill(atoi(argv[1]), SIGUSR1);
			else
				kill(atoi(argv[1]), SIGUSR2);
			j++;
			sleep(1 / 100);
		}
		i++;
	}
}
