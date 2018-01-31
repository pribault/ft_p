/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 13:15:41 by pribault          #+#    #+#             */
/*   Updated: 2018/01/31 15:21:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_error	g_default_errors[] =
{
	{ERROR_ALLOCATION, "allocation error", ERROR_EXIT},
	{ERROR_FILE, "cannot open file %s", 0},
	{ERROR_UNKNOWN, "unknown", 0},
	{ERROR_STR, "'%s' is not a valid string", 0},
	{ERROR_INTEGER, "'%s' is not a valid integer", 0},
	{ERROR_UNSIGNED, "'%s' is not a valid unsigned", 0},
	{ERROR_FLOAT, "'%s' is not a valid float", 0},
	{0, NULL, 0}
};

t_error	*g_errors = NULL;

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

void		ft_error(int fd, int error, uint64_t param)
{
	char	*format;
	char	*s;
	size_t	i;

	if (!g_errors && !init_array())
		return ;
	i = (size_t)-1;
	while (g_errors[++i].format)
		if (error == g_errors[i].error_code && (format =
			ft_joinf("\e[0m\e[38;5;124m\e[4mError:\e[0m %s\e[0m\n",
			g_errors[i].format)))
		{
			if ((s = ft_joinf(format, param)))
			{
				ft_putstr_fd(s, fd);
				free(s);
			}
			free(format);
			if (g_errors[i].opt & ERROR_EXIT)
				exit(1);
		}
}
