#include "server.h"

void	get_protocol(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (!ft_strcmp(argv[++(*i)], "tcp"))
			server->protocol = TCP;
		else if (!ft_strcmp	(argv[*i], "udp"))
			server->protocol = UDP;
		else
			error(14, 0, argv[*i]);
	}
	else
		error(13, 0, argv[*i]);
}

void	get_verbose(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (!ft_strcmp(argv[++(*i)], "on"))
			server->opt += (server->opt & VERBOSE) ? 0 : VERBOSE;
		else if (!ft_strcmp	(argv[*i], "off"))
			server->opt -= (server->opt & VERBOSE) ? VERBOSE : 0;
		else
			error(11, 0, argv[*i]);
	}
	else
		error(13, 0, argv[*i]);
}

void	get_max(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 1 < argc)
	{
		if (ft_isnumeric(argv[++(*i)]))
		{
			if (ft_atoi(argv[*i]) >= 0)
				server->queue_max = ft_atou(argv[*i]);
			else
				error(16, 0, argv[*i]);
		}
		else
			error(15, 0, argv[*i]);
	}
	else
		error(13, 0, argv[*i]);
}

void	get_timeout(t_server *server, int argc, char **argv, int *i)
{
	if (*i + 2 < argc)
	{
		if (ft_isnumeric(argv[++(*i)]))
		{
			if (ft_atoi(argv[*i]) >= 0)
				server->timeout.tv_sec = ft_atou(argv[*i]);
			else
				error(16, 0, argv[*i]);
		}
		else
			error(15, 0, argv[*i]);
		if (ft_isnumeric(argv[++(*i)]))
		{
			if (ft_atoi(argv[*i]) >= 0)
				server->timeout.tv_usec = ft_atou(argv[*i]);
			else
				error(16, 0, argv[*i]);
		}
		else
			error(15, 0, argv[*i]);
	}
	else
		error(17, 0, argv[*i]);
}

void	get_param(t_server *server, int argc, char **argv, int *i)
{
	if (!ft_strcmp(argv[*i], "-p") || !ft_strcmp(argv[*i], "--protocol"))
		get_protocol(server, argc, argv, i);
	else if (!ft_strcmp(argv[*i], "-v") || !ft_strcmp(argv[*i], "--verbose"))
		get_verbose(server, argc, argv, i);
	else if (!ft_strcmp(argv[*i], "-h") || !ft_strcmp(argv[*i], "--help"))
		print_usage();
	else if (!ft_strcmp(argv[*i], "-m") || !ft_strcmp(argv[*i], "--max"))
		get_max(server, argc, argv, i);
	else if (!ft_strcmp(argv[*i], "-t") || !ft_strcmp(argv[*i], "--timeout"))
		get_timeout(server, argc, argv, i);
	else
		error(12, 0, argv[*i]);
}

void	get_flags(t_server *server, int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			get_param(server, argc, argv, &i);
		else if (ft_isnumeric(argv[i]) && ft_atoi(argv[i]) >= 0)
			server->port = ft_atou(argv[i]);
		else
			error(10, 0, argv[i]);
	}
}
