/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:41:38 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 19:38:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_usage(void)
{
	ft_putchar('\n');
	ft_putstr("\e[0m\e[3m\e[1m./client <address> <port> <options>\e[0m\n");
	ft_putstr(" \e[2mavailable options:\e[0m\n");
	ft_putstr("  --\e[4mhelp\e[0m or -h: \e[2mprint usage\e[0m\n");
	ft_putstr("  --\e[4mprotocol\e[0m or -p: \e[2mtcp/udp\e[0m\n");
	ft_putstr("  --\e[4mverbose\e[0m or -v: \e[2mon/off\e[0m\n");
	ft_putstr("  --\e[4mtimeout\e[0m or -t: \e[2m<n second> ");
	ft_putstr("<n micro seconds>\e[0m\n");
	ft_putchar('\n');
}

void	get_command(t_client *client, int argc, char **argv, int *i)
{
	(void)client;
	(void)argc;
	if (!ft_strcmp(argv[*i], "-h") || !ft_strcmp(argv[*i], "--help"))
		print_usage();
	else
		error(5, 0, argv[*i]);
}

void	get_main_parameters(t_client *client, char *s, uint8_t *state)
{
	if (!*state)
	{
		client->address = s;
		(*state)++;
	}
	else
	{
		if (ft_isnumeric(s) && ft_atoi(s) > -1 && ft_atoi(s) < 65536)
		{
			client->port = s;
			(*state)++;
		}
		else
			error(3, 0, s);
	}
}

void	get_flags(t_client *client, int argc, char **argv)
{
	uint8_t	state;
	int		i;

	i = 0;
	state = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			get_command(client, argc, argv, &i);
		else if (state <= 1)
			get_main_parameters(client, argv[i], &state);
		else
			error(2, 0, argv[i]);
	}
}
