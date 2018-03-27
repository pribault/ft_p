/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_poll_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:32:57 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 13:44:35 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	client_add_write_request_to_set(fd_set *set, t_circ_buffer *queue,
			int *fd_max)
{
	t_towrite	*towrite;
	size_t		i;

	if (!set || !queue)
		return ;
	i = (size_t)-1;
	while ((towrite = ft_circ_buffer_get(queue, ++i)))
	{
		if (towrite->fd > *fd_max)
			*fd_max = towrite->fd;
		FD_SET(towrite->fd, set);
	}
}

static void	set_sets(t_client *client, fd_set *set, int *fd_max)
{
	FD_ZERO(&set[0]);
	FD_ZERO(&set[1]);
	FD_ZERO(&set[2]);
	if (client->opt & CLIENT_CONNECTED)
	{
		FD_SET(client->sockfd, &set[0]);
		FD_SET(client->sockfd, &set[2]);
		*fd_max = client->sockfd;
	}
	else
		*fd_max = 0;
	client_add_write_request_to_set(&set[1], &client->write_queue, fd_max);
}

void		client_poll_events(t_client *client)
{
	fd_set	set[3];
	int		fd_max;
	int		ret;

	if (!client || !(client->opt & CLIENT_RUNNING))
		return ;
	set_sets(client, (fd_set*)&set, &fd_max);
	if ((ret = select(fd_max + 1, &set[0], &set[1], &set[2],
		&client->timeout)) < 0)
		return ;
	if (!ret)
		return ;
	if (FD_ISSET(client->sockfd, &set[0]))
		client_get_incoming_message(client, &ret);
	if (FD_ISSET(client->sockfd, &set[2]) && client->excpt)
		client->excpt(client);
	client_manage_write_requests(client, &set[1], &ret);
	return ;
}
