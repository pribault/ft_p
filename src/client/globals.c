/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 21:01:34 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 20:42:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	*g_global = NULL;

/*
**	states:
**	- 0: idle;
**	- 1: waiting for data;
**	- 2: downloading;
**	- 3: waiting for raw text response;
*/

/*
**	types:
**	- 0: raw text;
**	- 1: file;
**	- 2: shell command;
**	- 3: ls;
**	- 4: cd;
**	- 5: pwd;
**	- 6: auth;
*/

t_function	g_state_machine[STATE_MAX][TYPE_MAX] =
{
	{&get_raw_text, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&get_text_return, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing}
};

char		*g_return_name[RETURN_MAX] =
{
	"success",
	"fail"
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
