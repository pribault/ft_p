/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:51:11 by pribault          #+#    #+#             */
/*   Updated: 2018/01/31 13:11:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_flag(void)
{
}

void		ft_get_flags(int argc, char **argv, t_flag *flags, int n_flags)
{
	int		i;
	int		j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (++j < n_flags)
			if (!ft_strcmp(argv[i], flags[j].str))
				ft_get_flag();
	}
}
