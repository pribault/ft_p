/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:12:21 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 16:24:48 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_usage(void)
{
	ft_putchar('\n');
	ft_putstr("\e[0m\e[3m\e[1m./server <port> <options>\e[0m\n");
	ft_putstr(" \e[2mavailable options:\e[0m\n");
	ft_putstr("  --\e[4mhelp\e[0m or -h: \e[2mprint usage\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m or -p: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mon/off\e[0m\n");
	ft_putstr("  --\e[4mmax\e[0m or -m: \e[2m<n>\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m or -t: \e[2m<n second> ");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
}

void	get_clients_max(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (ft_isnumeric(argv[++(*i)]) && ft_atoi(argv[*i]) > -1)
			server_set_clients_max(server->server, ft_atou(argv[*i]));
		else
			error(4, 0, argv[*i]);
	}
	else
		error(6, 0, argv[*i]);
}

void	get_queue_max(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (ft_isnumeric(argv[++(*i)]) && ft_atoi(argv[*i]) > -1)
			server_set_queue_max(server->server, ft_atou(argv[*i]));
		else
			error(4, 0, argv[*i]);
	}
	else
		error(6, 0, argv[*i]);
}

void	get_command(t_server *server, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-m") || !ft_strcmp(argv[*i], "--max"))
		get_clients_max(server, argc, argv, i);
	else if (!ft_strcmp(argv[*i], "-q") || !ft_strcmp(argv[*i], "--queue"))
		get_queue_max(server, argc, argv, i);
	else if (!ft_strcmp(argv[*i], "-h") || !ft_strcmp(argv[*i], "--help"))
		print_usage();
	else
		error(5, 0, argv[*i]);
}

void	get_flags(t_server *server, int argc, char **argv)
{
	uint8_t	state;
	int		i;

	i = 0;
	state = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			get_command(server, argc, argv, &i);
		else if (!state)
		{
			if (ft_isnumeric(argv[i]) && ft_atoi(argv[i]) > -1 &&
				ft_atoi(argv[i]) < 65536)
			{
				server->port = argv[i];
				state++;
			}
			else
				error(3, 0, argv[i]);
		}
		else
			error(2, 0, argv[i]);
	}
}
