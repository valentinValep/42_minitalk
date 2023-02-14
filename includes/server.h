/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:36:49 by vlepille          #+#    #+#             */
/*   Updated: 2023/02/14 17:54:06 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "libft.h"

typedef struct s_handler_storage
{
	int			i;
	char		number_of_null;
	char		c;
	t_string	str;
}	t_handler_storage;

#endif
