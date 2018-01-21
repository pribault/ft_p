/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:40:21 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 20:33:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static char	*error_2(int error, void *param, char *s)
{
	if (error == 101)
		s = ft_joinf("command '%s' take only one or two parameters", param);
	else if (error == 102)
		s = ft_joinf("command '%s' take only one paramter", param);
	else
		s = ft_strdup("unknown error");
	return (s);
}

void		error(int error, int state, void *param)
{
	char	*s;

	if (error == -1)
		s = ft_strdup(param);
	else if (error == 0)
		s = strerror(errno);
	else if (error == 1)
		s = ft_strdup("cannot allocate memory");
	else if (error == 2)
		s = ft_joinf("'%s' address and port already set, ignoring", param);
	else if (error == 3)
		s = ft_joinf("'%s' is not a valid port number, ignoring", param);
	else if (error == 4)
		s = ft_joinf("could not connect to %s:%s",
		((t_client*)param)->address, ((t_client*)param)->port);
	else if (error == 5)
		s = ft_joinf("'%s' is not a number", param);
	else if (error == 100)
		s = ft_joinf("unknown command '%s'", param);
	else
		s = error_2(error, param, NULL);
	ft_printf("\e[0m\e[38;5;124m\e[4mError:\e[0m %s\e[0m\n", s);
	free(s);
	if (state)
		exit(state);
}
