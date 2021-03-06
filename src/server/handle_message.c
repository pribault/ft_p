/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:50:38 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 18:19:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		path_is_valid(t_serv *server, t_data *data, char *file)
{
	size_t	root_len;
	size_t	len;
	size_t	i;
	int		state;
	char	**array;

	(void)data;
	root_len = ft_strlen(server->root);
	if (ft_strncmp(server->root, file, root_len))
		return (0);
	if (!(array = ft_multisplit(file + root_len, "/")))
		ft_error(2, ERROR_ALLOCATION, NULL);
	len = ft_arraylen(array);
	i = (size_t)-1;
	state = 0;
	while (++i < len && state >= 0)
	{
		if (!ft_strcmp(array[i], ".."))
			state--;
		else if (ft_strcmp(array[i], "."))
			state++;
	}
	ft_free_array((void**)array, len);
	return ((state >= 0) ? 1 : 0);
}

void	recv_cd(t_serv *server, void *client, t_header *ptr, size_t size)
{
	DIR		*dir;
	t_data	*data;
	char	*file[2];

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (!(file[0] = malloc(size - sizeof(t_header) + 1)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(file[0], (void*)ptr + sizeof(t_header), size - sizeof(t_header));
	file[0][size - sizeof(t_header)] = '\0';
	if (!(file[1] = ft_joinf("%s%s/", data->pwd, file[0])))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if ((dir = opendir(file[1])) && path_is_valid(server, data, file[1]))
	{
		free(data->pwd);
		data->pwd = ft_reduce_path(ft_strdup(file[1]));
		enqueue_msg(server, client, new_msg("\e[38;5;82mSUCCESS\e[0m", 21),
		TYPE_STR);
		closedir(dir);
	}
	else
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open directory", 43), TYPE_STR);
	free(file[1]);
	free(file[0]);
}

void	recv_ls_2(t_serv *server, void *client, char *file)
{
	char	**ret;
	char	*to_send;

	if (!(ret = ft_ls(file)))
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open directory", 43), TYPE_STR);
	else
	{
		if (!(to_send = ft_implode(ret, '\n')))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_free_array((void**)ret, ft_arraylen(ret));
		enqueue_msg(server, client, new_msg("\e[38;5;82mSUCCESS\e[0m", 21),
		TYPE_STR);
		enqueue_msg(server, client, new_msg(to_send, ft_strlen(to_send)),
		TYPE_STR);
		free(to_send);
	}
}

void	recv_ls(t_serv *server, void *client, t_header *ptr, size_t size)
{
	char	*long_file;
	char	*file;
	t_data	*data;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (!(file = malloc(size - sizeof(t_header) + 1)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(file, (void*)ptr + sizeof(t_header), size - sizeof(t_header));
	file[size - sizeof(t_header)] = '\0';
	if (!(long_file = ft_joinf("%s/%s", data->pwd, file)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (path_is_valid(server, data, long_file))
		recv_ls_2(server, client, long_file);
	else
		enqueue_msg(server, client, new_msg(
		"\e[38;5;160mERROR:\e[0m cannot open directory", 43), TYPE_STR);
	free(long_file);
	free(file);
}

void	recv_pwd(t_serv *server, void *client, t_header *ptr, size_t size)
{
	char	*path;
	t_data	*data;

	(void)ptr;
	(void)size;
	ft_printf("pwd=%s\n", ((t_data*)server_client_get_data(client))->pwd);
	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	enqueue_msg(server, client,
	new_msg("\e[38;5;82mSUCCESS\e[0m", 21), TYPE_STR);
	path = data->pwd + ft_strlen(server->root) - 1;
	enqueue_msg(server, client, new_msg(path, ft_strlen(path)),
	TYPE_STR);
}
