/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:03:28 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 20:21:14 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	do_nothing(t_client *client, void *msg, size_t size)
{
	(void)client;
	(void)msg;
	(void)size;
}

void	get_raw_text(t_client *client, void *msg, size_t size)
{
	char	s[8] = "\e[2K\r";
	char	p[4] = "$> ";

	enqueue_write(client, 1, &s, 7);
	enqueue_putendl(client, 1, msg, size);
	enqueue_write(client, 1, &p, 3);
}

void	get_text_return(t_client *client, void *msg, size_t size)
{
	char	n[32];
	char	s[8] = "\e[2K\r";
	char	p[4] = "$> ";

	if (size >= sizeof(t_return))
	{
		ft_memcpy(&n, g_return_name[*(t_return*)msg],
			ft_strlen(g_return_name[*(t_return*)msg]) + 1);
		enqueue_write(client, 1, &s, 7);
		enqueue_putendl(client, 1, (char*)&n, ft_strlen((char*)&n));
		enqueue_putendl(client, 1, msg + sizeof(t_return), size - sizeof(t_return));
		enqueue_write(client, 1, &p, 3);
	}
}
