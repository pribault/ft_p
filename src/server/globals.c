/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:15:11 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 15:28:43 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server	*g_global = NULL;

/*
**	states:
**	- 0: idle;
**	- 1: waiting for data;
**	- 2: downloading;
*/

/*
**	types:
**	- 0: raw text
**	- 1: file
**	- 2: shell command
*/

t_function	g_state_machine[STATE_MAX][TYPE_MAX] =
{
	{&get_raw_text, NULL, NULL},
	{NULL, NULL, NULL},
	{NULL, NULL, NULL}
};

char	*g_types_name[TYPE_MAX] =
{
	"raw_text",
	"file",
	"shell command"
};
