/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:34:53 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 14:35:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	get_protocol(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (!ft_strcmp(argv[++(*i)], "tcp"))
			server->protocol = TCP;
		else if (!ft_strcmp(argv[*i], "udp"))
			server->protocol = UDP;
		else
			error(14, 0, argv[*i]);
	}
	else
		error(13, 0, argv[*i]);
}
