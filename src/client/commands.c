/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:43:12 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 20:33:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	command_exit(t_client *client, char **cmds, size_t len)
{
	(void)client;
	if (len == 1)
		exit(1);
	if (len == 2)
	{
		if (ft_isnumeric(cmds[1]))
			exit(ft_atoi(cmds[1]));
		else
			error(5, 0, cmds[1]);
	}
	else
		error(101, 0, cmds[0]);
}

void	command_pwd(t_client *client, char **cmds, size_t len)
{
	t_msg	msg;

	if (len != 1)
		return (error(102, 0, cmds[0]));
	msg.size = sizeof(uint64_t) + 4;
	if (!(msg.ptr = malloc(msg.size)))
		error(1, 1, NULL);
	*(uint64_t*)msg.ptr = msg.size;
	ft_memcpy(msg.ptr + sizeof(uint64_t), cmds[0], 4);
	server_enqueue_write_by_fd(client->server, client->fd, &msg);
	free(msg.ptr);
}

void	command_ls(t_client *client, char **cmds, size_t len)
{
	t_msg	msg;
	char	*s;

	if (len > 2)
		return (error(101, 0, cmds[0]));
	if (!(s = ft_implode(cmds, ' ')))
		error(1, 1, NULL);
	len = ft_strlen(s);
	msg.size = sizeof(uint64_t) + len + 1;
	if (!(msg.ptr = malloc(msg.size)))
		error(1, 1, NULL);
	*(uint64_t*)msg.ptr = msg.size;
	ft_memcpy(msg.ptr + sizeof(uint64_t), s, len + 1);
	server_enqueue_write_by_fd(client->server, client->fd, &msg);
	free(msg.ptr);
	free(s);
}

void	treat_command_2(t_client *client, char **cmds, size_t len)
{
	if (!ft_strcmp(cmds[0], "exit"))
		command_exit(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "pwd"))
		command_pwd(client, cmds, len);
	else if (!ft_strcmp(cmds[0], "ls"))
		command_ls(client, cmds, len);
	else
		error(100, 0, cmds[0]);
}

void	treat_command(t_client *client, char *cmd)
{
	char	**cmds;
	size_t	len;

	if (!(cmds = ft_multisplit(cmd, WHITESPACES)))
		error(1, 1, NULL);
	len = ft_arraylen(cmds);
	if (len)
		treat_command_2(client, cmds, len);
	ft_free_array((void**)cmds, len + 1);
}
