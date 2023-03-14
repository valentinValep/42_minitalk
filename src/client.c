/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:36:40 by vlepille          #+#    #+#             */
/*   Updated: 2023/03/14 13:37:59 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	g_received;

void	handler(int sig)
{
	(void) sig;
	g_received = 1;
}

void	send_char(__pid_t pid, char c)
{
	int	i;
	int	usecond;

	i = -1;
	while (++i < (int) sizeof(char) * 8)
	{
		usecond = 0;
		if (kill(pid, (int []){SIGUSR1, SIGUSR2}[(c >> i) & 1]))
			exit(1);
		while (!g_received)
		{
			usleep(1);
			usecond++;
			if (usecond > 100000)
			{
				write(STDOUT_FILENO, "No server response : Stop\n", 26);
				i = -1;
				while (++i < 16)
					kill(pid, SIGUSR1);
				exit(1);
			}
		}
		g_received = 0;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
		return ((write(STDOUT_FILENO,
					"You need 2 args : server pid and a string\n", 42), 0));
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0))
		return ((write(STDOUT_FILENO, "Invalid PID\n", 12), 1));
	if (signal(SIGUSR1, handler) == SIG_ERR)
		return (1);
	i = -1;
	while ((i == -1 && i++) || argv[2][i++])
		send_char(server_pid, argv[2][i]);
	write(STDOUT_FILENO, "Message succefully send\n", 24);
}
