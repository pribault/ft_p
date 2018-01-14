/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:04:44 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 21:41:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		my_exit(void)
{
	ft_putstr("\n\e[1A\e[Kexiting...\n");
	if (g_global)
		close(g_global->socket);
}

void		my_sig(int sig)
{
	exit(sig);
}

t_client	*init_client(void)
{
	static t_client	client;

	ft_bzero(&client, sizeof(t_client));
	client.socket = -1;
	client.protocol = TCP;
	client.port = 4242;
	client.timeout = (struct timeval){1, 0};
	client.state = STATE_IDLE;
	if (!(client.write_queue = ft_vector_new(sizeof(t_towrite), 0)))
		error(1, 1, NULL);
	return (&client);
}

int			main(int argc, char **argv)
{
	t_client	*client;

	atexit(&my_exit);
	signal(SIGINT, &my_sig);
	client = init_client();
	get_flags(client, argc, argv);
	connect_to_server(client);
	g_global = client;
	run_client(client);
	return (0);
}
