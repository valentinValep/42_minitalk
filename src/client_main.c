#include <signal.h>
#include <sys/types.h>
#include <stdlib.h> // @TODO rm and replace by my atoi
#include <stdio.h> // @TODO rm and replace by my ft_printf or use write
int	main(int argc, char **argv)
{
	if (argc != 2)
		return ((printf("You need 1 arg"), 0));
	printf("You select PID %d", atoi(argv[1])); // @TODO RM
	kill(atoi(argv[1]), SIGUSR1);
}
