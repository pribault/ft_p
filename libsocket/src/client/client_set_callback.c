/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_set_callback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 13:29:34 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:42:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_set_callback(t_client *client, t_callback cb, void *ptr)
{
	if (cb >= CALLBACK_MAX)
		return ;
	((void**)&client->connect)[cb] = ptr;
}
