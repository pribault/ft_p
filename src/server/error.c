/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:07:43 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 16:59:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	error(int error, int state, void *param)
{
	char	*s;

	if (error == -1)
		s = ft_strdup(param);
	else if (error == 0)
		s = strerror(errno);
	else if (error == 1)
		s = ft_strdup("cannot allocate memory");
	else if (error == 2)
		s = ft_joinf("'%s', port already set, ignoring", param);
	else if (error == 3)
		s = ft_joinf("'%s' is not a valid port number, ignoring", param);
	else if (error == 4)
		s = ft_joinf("'%s' is not a valid number", param);
	else if (error == 5)
		s = ft_joinf("'%s' unknown parameter", param);
	else if (error == 6)
		s = ft_joinf("parameter '%s' take only 1 argument", param);
	else if (error == 100)
		s = ft_joinf("unknown command '%s'", param);
	else if (error == 101)
		s = ft_joinf("%s command take no more thank one parameter", param);
	else
		s = ft_strdup("unknown error");
	ft_printf("\e[0m\e[38;5;124m\e[4mError:\e[0m %s\e[0m\n", s);
	free(s);
	if (state)
		exit(state);
}
