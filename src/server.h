#ifndef SERVER_H
# define SERVER_H

# include <sys/types.h>

typedef struct s_client_pid
{
	pid_t	pid;
	int		is_full;
	int		i;
}	t_client_pid;

#endif