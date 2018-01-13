/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 14:31:16 by pribault          #+#    #+#             */
/*   Updated: 2018/01/13 19:28:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(char *s)
{
	int		i;
	char	boolean;

	i = 0;
	boolean = 0;
	while (s[i] && s[i] > 8 && s[i] < 14)
		i++;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			if (s[i] != '.' || boolean)
				return (0);
			boolean = 1;
		}
		i++;
	}
	return (1);
}
