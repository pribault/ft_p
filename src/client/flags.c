#include "client.h"

void	get_param(t_client *client, int argc, char **argv, int *i)
{
	(void)client;
	(void)argc;
	error(12, 0, argv[*i]);
}

void	get_flags(t_client *client, int argc, char **argv)
{
	int		i;
	char	state;

	i = 0;
	state = 0;
	while (++i < argc)
		if (argv[i][0] == '-')
			get_param(client, argc, argv, &i);
		else if (!state)
		{
			client->addr = argv[i];
			state++;
		}
		else if (state == 1)
		{
			client->service = argv[i];
			state++;
		}
		else
			error(10, 0, argv[i]);
}
