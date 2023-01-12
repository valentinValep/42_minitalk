/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:36:40 by vlepille          #+#    #+#             */
/*   Updated: 2023/01/12 14:27:55 by vlepille         ###   ########.fr       */
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

	i = -1;
	while (++i < (int) sizeof(char) * 8)
	{
		if (kill(pid, (int []){SIGUSR1, SIGUSR2}[(c >> i) & 1]))
			exit(1);
		while (!g_received)
			;
		g_received = 0;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		return ((write(STDOUT_FILENO,
					"You need 2 args : server pid and a string", 41), 0));
	if (kill(ft_atoi(argv[1]), 0))
		return ((write(STDOUT_FILENO, "Invalid PID", 11), 1));
	if (signal(SIGUSR1, handler) == SIG_ERR)
		return (1);
	i = -1;
	while ((i == -1 && i++) || argv[2][i++])
		send_char(ft_atoi(argv[1]), argv[2][i]);
}
