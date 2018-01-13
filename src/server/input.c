/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:47:40 by pribault          #+#    #+#             */
/*   Updated: 2018/01/13 20:59:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	read_from_terminal(t_server *server, int *n)
{
	size_t	size;
	char	buffer[READ_BUFFER_SIZE];
	char	*s;

	if (FD_ISSET(0, &server->in))
	{
		ft_bzero(&buffer, sizeof(buffer));
		size = read(0, &buffer, READ_BUFFER_SIZE);
		buffer[size] = '\0';
		s = ft_joinf("receiving [%s]\n", &buffer);
		enqueue_write(server, 1, s, ft_strlen(s));
		free(s);
		(*n)--;
	}
}

void	read_from_socket(t_server *server, int *n)
{
	t_client	client;

	if (FD_ISSET(server->socket, &server->in))
	{
		if ((client.fd = accept(server->socket, &client.addr,
			&client.addr_len)) < 0)
			error(0, 0, NULL);
		ft_vector_add(server->clients, &client);
		ft_printf("client %s added\n",
			inet_ntoa(((struct sockaddr_in *)&client.addr)->sin_addr));
		(*n)--;
	}
}

void	read_input(t_server *server, int *n)
{
	char		buffer[READ_BUFFER_SIZE];
	t_vector	*vector;
	t_client	*client;
	size_t		i;
	int			r;

	read_from_terminal(server, n);
	read_from_socket(server, n);
	i = (size_t)-1;
	vector = server->clients;
	while (*n && ++i < vector->n)
	{
		client = ft_vector_get(vector, i);
		if (FD_ISSET(client->fd, &server->in))
		{
			if ((r = read(client->fd, &buffer, sizeof(buffer))) < 0)
				error(0, 0, NULL);
			else if (!r)
			{
				ft_printf("connexion closed for %s\n",
					inet_ntoa(((struct sockaddr_in *)&client->addr)->sin_addr));
				close(client->fd);
				ft_vector_del_one(vector, i--);
			}
			else
			{
				ft_printf("message received from %s:\n",
					inet_ntoa(((struct sockaddr_in *)&client->addr)->sin_addr));
				ft_memdump(&buffer, r);
			}
			(*n)--;
		}
	}
}

void	set_input(t_server *server)
{
	t_vector	*vector;
	t_client	*client;
	size_t		i;

	FD_ZERO(&server->in);
	FD_SET(0, &server->in);
	FD_SET(server->socket, &server->in);
	if (server->socket > server->io_max)
		server->io_max = server->socket;
	vector = server->clients;
	i = (size_t)-1;
	while (++i < vector->n)
	{
		client = ft_vector_get(vector, i);
		FD_SET(client->fd, &server->in);
		if (client->fd > server->io_max)
			server->io_max = client->fd;
	}
}
