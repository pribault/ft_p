/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:47:40 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 17:02:03 by pribault         ###   ########.fr       */
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
		ft_bzero(&client, sizeof(t_client));
		client.addr_len = sizeof(client.addr);
		client.state = STATE_IDLE;
		if ((client.fd = accept(server->socket, &client.addr,
			&client.addr_len)) < 0)
			error(0, 0, NULL);
		else
		{
			ft_printf("client %s added\n",
			inet_ntoa(((struct sockaddr_in *)&client.addr)->sin_addr));
			ft_vector_add(server->clients, &client);
		}
		(*n)--;
	}
}

void	close_connexion(t_vector *vector, t_client *client, size_t i)
{
	ft_printf("connexion closed for %s\n",
		inet_ntoa(((struct sockaddr_in *)&client->addr)->sin_addr));
	close(client->fd);
	ft_vector_del_one(vector, i--);
}

void	read_input(t_server *server, int *n)
{
	char		buffer[READ_BUFFER_SIZE];
	t_vector	*vector;
	t_client	*client;
	size_t		i;
	int			r;

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
				close_connexion(vector, client, i);
			else
				treat_message(server, client, ft_memdup(&buffer, r), r);
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
