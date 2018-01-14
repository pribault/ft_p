/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:01:34 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:13:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	*g_global = NULL;

t_function	g_state_machine[STATE_MAX][TYPE_MAX] =
{
	{&get_raw_text, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing}
};

char		*g_types_name[TYPE_MAX] =
{
	"raw_text",
	"file",
	"shell command",
	"ls",
	"cd",
	"pwd",
	"auth"
};
