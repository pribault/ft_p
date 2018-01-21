/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:43:12 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 16:59:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	command_exit(t_server *server, char **cmds, size_t len)
{
	(void)server;
	if (len == 1)
		exit(0);
	if (len == 2)
	{
		if (ft_isnumeric(cmds[1]))
			exit(ft_atoi(cmds[1]));
		else
			error(4, 0, cmds[1]);
	}
	else
		error(101, 0, cmds[0]);
}

void	treat_command_2(t_server *server, char **cmds, size_t len)
{
	if (!ft_strcmp(cmds[0], "exit"))
		command_exit(server, cmds, len);
	else
		error(100, 0, cmds[0]);
}

void	treat_command(t_server *server, char *cmd)
{
	char	**cmds;
	size_t	len;

	if (!(cmds = ft_multisplit(cmd, WHITESPACES)))
		error(1, 1, NULL);
	len = ft_arraylen(cmds);
	if (len)
		treat_command_2(server, cmds, len);
	ft_free_array((void**)cmds, len + 1);
}
