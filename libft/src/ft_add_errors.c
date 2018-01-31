/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:16:33 by pribault          #+#    #+#             */
/*   Updated: 2018/01/31 15:23:55 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	init_array(void)
{
	size_t	i;

	i = (size_t)-1;
	while (g_default_errors[++i].format)
		;
	if (!(g_errors = malloc(sizeof(t_error) * (i + 1))))
		return (0);
	ft_memcpy(g_errors, &g_default_errors, sizeof(t_error) * (i + 1));
	return (1);
}

void	ft_add_errors(t_error *array)
{
	size_t	i;
	size_t	j;

	if (!array || (!g_errors && !init_array()))
		return ;
	i = (size_t)-1;
	while (g_errors[++i].format)
		;
	j = (size_t)-1;
	while (array[++j].format)
		;
	if (!(g_errors = realloc(g_errors, sizeof(t_error) * (i + j + 1))))
		return ;
	ft_memcpy(g_errors + i, array, sizeof(t_error) * (j + 1));
}
