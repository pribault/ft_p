/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 18:16:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_usage(void)
{
	ft_putchar('\n');
	ft_putstr("\e[3m\e[1m./server <port> <options>\e[0m\n");
	ft_putstr(" \e[2mavailable options:\e[0m\n");
	ft_putstr("  --\e[4mhelp\e[0m or -h: \e[2mprint usage\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m or -p: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mon/off\e[0m\n");
	ft_putstr("  --\e[4mmax\e[0m or -m: \e[2m<n>\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m or -t: \e[2m<n second> ");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
	exit(0);
}

char	*error_3(int error, void *param, char *s)
{
	if (error == 50)
		s = ft_joinf("unknown command '%s'", param);
	else
		s = ft_strdup("unknown error");
	return (s);
}

char	*error_2(int error, void *param, char *s)
{
	if (error == 12)
		s = ft_joinf("unknown option '%s'", param);
	else if (error == 13)
		s = ft_strdup("option '%s' must take exactly one argument");
	else if (error == 14)
		s = ft_joinf("unknown protocol '%s', allowed: tcp, udp", param);
	else if (error == 15)
		s = ft_joinf("'%s' is not a number", param);
	else if (error == 16)
		s = ft_joinf("'%s' number must be in interval [0;2147483647]", param);
	else if (error == 17)
		s = ft_joinf("option '%s' must take exactly two argument", param);
	else if (error == 18)
		s = ft_joinf("port already set to %d, overwriting",
			*(uint16_t*)param);
	else if (error == 100)
		s = ft_strdup("receiving abnormally small packet, ignoring");
	else if (error == 101)
		s = ft_strdup("receiving packet of unknown type, ignoring");
	else if (error == 102)
		s = ft_joinf("unknown data type %d", *(uint8_t*)param);
	else
		s = error_3(error, param, s);
	return (s);
}

void	error(int error, int state, void *param)
{
	char	*s;
	char	*t;

	if (error == -1)
		t = ft_strdup(param);
	else if (error == 0)
		t = strerror(errno);
	else if (error == 1)
		t = ft_strdup("cannot allocate memory");
	else if (error == 10)
		t = ft_joinf("'%s' must be a number in interval [0;65536]", param);
	else if (error == 11)
		t = ft_joinf("unknown parameter '%s', allowed: on, off", param);
	else
		t = error_2(error, param, NULL);
	s = ft_joinf("%s%s", "\e[38;5;124m\e[4mError:\e[0m ", t);
	if (g_global)
		enqueue_putendl(g_global, 2, s, ft_strlen(s));
	else
		ft_putendl_fd(s, 2);
	free(t);
	free(s);
	if (state)
		exit(state);
}
