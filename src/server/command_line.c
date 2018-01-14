/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 18:07:16 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 18:21:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	interpret_command_line(t_server *server, char *line)
{
	char	**cmd;
	size_t	len;

	(void)server;
	if (ft_strlen(line) && (cmd = ft_multisplit(line, WHITESPACES)))
	{
		len = ft_arraylen(cmd);
		if (!ft_strcmp(cmd[0], "quit") || !ft_strcmp(cmd[0], "exit"))
			exit(0);
		else
			error(50, 0, line);
		ft_free_array((void**)cmd, len + 1);
	}
}
