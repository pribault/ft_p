/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_message.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:50:38 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 18:16:18 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		path_is_valid(t_server *server, t_data *data, char *file)
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

void	recv_cd(t_server *server, void *client, t_header *ptr, size_t size)
{
	t_data	*data;
	char	*long_name;
	char	*file;

	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	if (!(file = malloc(size - sizeof(t_header) + 1)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_memcpy(file, (void*)ptr + sizeof(t_header), size - sizeof(t_header));
	file[size - sizeof(t_header)] = '\0';
	if (!(long_name = ft_joinf("%s%s/", data->pwd, file)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (path_is_valid(server, data, long_name))
	{
		free(data->pwd);
		data->pwd = ft_strdup(long_name);
		enqueue_msg(server, client, new_msg("SUCCESS", 7), TYPE_STR);
	}
	else
		enqueue_msg(server, client, new_msg("ERROR: cannot open directory",
		28), TYPE_STR);
	free(long_name);
	free(file);
}

void	recv_ls_2(t_server *server, void *client, char *file)
{
	char	**ret;
	char	*to_send;

	if (!(ret = ft_ls(file)))
		enqueue_msg(server, client, new_msg("ERROR: cannot open directory",
		28), TYPE_STR);
	else
	{
		if (!(to_send = ft_implode(ret, '\n')))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_free_array((void**)ret, ft_arraylen(ret));
		enqueue_msg(server, client, new_msg("SUCCESS", 7), TYPE_STR);
		enqueue_msg(server, client, new_msg(to_send, ft_strlen(to_send)),
		TYPE_STR);
		free(to_send);
	}
}

void	recv_ls(t_server *server, void *client, t_header *ptr, size_t size)
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
		enqueue_msg(server, client, new_msg("ERROR: cannot open directory",
		28), TYPE_STR);
	free(long_file);
	free(file);
}

void	recv_pwd(t_server *server, void *client, t_header *ptr, size_t size)
{
	char	*path;
	t_data	*data;

	(void)ptr;
	(void)size;
	if (!(data = server_client_get_data(client)))
		return (ft_error(2, ERROR_CUSTOM, "client data null, wtf ?!? ._."));
	enqueue_msg(server, client,
	new_msg("SUCCESS", 7), TYPE_STR);
	path = data->pwd + ft_strlen(server->root) - 1;
	enqueue_msg(server, client, new_msg(path, ft_strlen(path)),
	TYPE_STR);
}

void	send_file(t_server *server, void *client, char *file)
{
	t_file_data	*final;
	struct stat	buff;
	char		*s;
	int			fd;

	if ((fd = open(file, O_RDWR)) == -1 ||
		fstat(fd, &buff) == -1)
		return (enqueue_msg(server, client,
		new_msg("ERROR: cannot open file", 23), TYPE_STR));
	if (!(s = mmap(NULL, buff.st_size, PROT_READ,
		MAP_FILE | MAP_PRIVATE, fd, 0)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	if (!(final = malloc(buff.st_size + sizeof(t_file_data))))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	enqueue_msg(server, client, new_msg("SUCCESS", 7), TYPE_STR);
	final->prot = buff.st_mode;
	ft_memcpy((void*)final + sizeof(t_file_data), s, buff.st_size);
	enqueue_msg(server, client, new_msg(final, buff.st_size +
	sizeof(t_file_data)), TYPE_RAW);
	free(final);
	munmap(s, buff.st_size);
}

void	recv_put(t_server *server, void *client, t_header *ptr, size_t size)
{
	t_file_data	*file;
	char		*name;
	struct stat	buff;
	int			fd;

	if (size < sizeof(t_header) + sizeof(t_file_data))
		return (ft_error(2, ERROR_CUSTOM,
		"message too small to be of type put"));
	file = (void*)ptr + sizeof(t_header);
	if (!(name = ft_joinf("%s/%s",
		((t_data*)server_client_get_data(client))->pwd, &file->name)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	if (stat(name, &buff) != -1)
		return (enqueue_msg(server, client,
		new_msg("ERROR: file already exist", 25), TYPE_STR));
	if ((fd = open(name, O_CREAT | O_WRONLY, file->prot)) == -1)
		return (enqueue_msg(server, client,
		new_msg("ERROR: cannot create file", 23), TYPE_STR));
	write(fd, (void*)file + sizeof(t_file_data),
	size - sizeof(t_header) - sizeof(t_file_data));
	close(fd);
	free(name);
	enqueue_msg(server, client, new_msg("SUCCESS", 7), TYPE_STR);
}

void	recv_get(t_server *server, void *client, t_header *ptr, size_t size)
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
		send_file(server, client, long_file);
	else
		enqueue_msg(server, client, new_msg("ERROR: cannot open file",
		23), TYPE_STR);
	free(long_file);
	free(file);
}
