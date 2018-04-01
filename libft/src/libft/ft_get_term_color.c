/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_term_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:04:16 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 13:27:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_term_color(t_color front, t_color back, t_color_effect effect)
{
	front.r = (front.r * 6) / 256;
	front.g = (front.g * 6) / 256;
	front.b = (front.b * 6) / 256;
	back.r = (back.r * 6) / 256;
	back.g = (back.g * 6) / 256;
	back.b = (back.b * 6) / 256;
	return (ft_joinf("\e[%dm\e[38;5;%dm\e[48;5;%dm", effect,
		(uint8_t)(16 + front.r * 36 + front.g * 6 + front.b),
		(uint8_t)(16 + back.r * 36 + back.g * 6 + back.b)));
}
