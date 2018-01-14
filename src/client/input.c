/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 18:16:47 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 16:17:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_raw(t_client *client, char **cmd, size_t size)
{
	t_header	header;

	if (size != 2)
		return (error(201, 0, NULL));
	header.type = TYPE_RAW_TEXT;
	header.size = ft_strlen(cmd[1]);
	enqueue_write(client, client->socket, &header, sizeof(t_header));
	enqueue_write(client, client->socket, cmd[1], ft_strlen(cmd[1]));
}

void	treat_command(t_client *client, char **cmd, size_t size)
{
	if (!ft_strcmp(cmd[0], "/quit") || !ft_strcmp(cmd[0], "/exit"))
		exit(0);
	else if (!ft_strcmp(cmd[0], "/send_raw") || !ft_strcmp(cmd[0], "/sr"))
		send_raw(client, cmd, size);
	else
		error(200, 0, cmd[0]);
}

void	read_from_terminal(t_client *client, int *n)
{
	char	**cmd;
	char	buffer[READ_BUFFER_SIZE];
	int		size;
	size_t	len;

	if (FD_ISSET(0, &client->in))
	{
		ft_bzero(&buffer, sizeof(buffer));
		if ((size = read(0, &buffer, READ_BUFFER_SIZE - 1)) < 0)
			error(0, 0, NULL);
		else
		{
			buffer[size] = '\0';
			if (!(cmd = ft_multisplit((char*)&buffer, WHITESPACES)))
				error(1, 1, NULL);
			len = ft_arraylen(cmd);
			if (len)
				treat_command(client, cmd, len);
			ft_free_array((void**)cmd, len);
		}
		(*n)--;
	}
}

void	read_from_socket(t_client *client, int *n)
{
	char	buffer[READ_BUFFER_SIZE];
	int		r;

	if (FD_ISSET(client->socket, &client->in))
	{
		if ((r = read(client->socket, &buffer, sizeof(buffer))) < 0)
			error(0, 0, NULL);
		else if (!r)
		{
			ft_printf("closing connexion\n");
			close(client->socket);
			exit(0);
		}
		else
		{
			ft_printf("message received:\n");
			ft_memdump(&buffer, r);
		}
		(*n)--;
	}
}
