/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:43:12 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 16:30:29 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	treat_command(t_server *server, char *cmd)
{
	size_t	len;
	char	**array;

	(void)server;
	if (!(array = ft_multisplit(cmd, WHITESPACES)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	len = ft_arraylen(array);
	if (len == 1 && !ft_strcmp(array[0], "exit"))
		exit(0);
	ft_free_array((void**)array, len);
}
