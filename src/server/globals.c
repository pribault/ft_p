/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 15:15:11 by pribault          #+#    #+#             */
/*   Updated: 2018/01/15 20:48:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_server	*g_global = NULL;

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
	{&get_raw_text, &do_nothing, &do_nothing, &do_ls, &do_nothing,
		&do_pwd, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing},
	{&do_nothing, &do_nothing, &do_nothing, &do_nothing, &do_nothing,
		&do_nothing, &do_nothing}
};

char	*g_types_name[TYPE_MAX] =
{
	"raw_text",
	"file",
	"shell command",
	"ls",
	"cd",
	"pwd",
	"auth"
};
