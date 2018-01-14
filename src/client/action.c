/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:03:28 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:15:48 by pribault         ###   ########.fr       */
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
	enqueue_putendl(client, 1, msg, size);
}
