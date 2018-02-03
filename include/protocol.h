/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:22:43 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 15:58:15 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_H
# define PROTOCOL_H

# include "libsocket.h"
# include "libft.h"

# define FILE_NAME_MAX_SIZE	123

typedef enum	e_type
{
	TYPE_STR,
	TYPE_RAW,
	TYPE_LS,
	TYPE_CD,
	TYPE_PWD,
	TYPE_PUT,
	TYPE_GET,
	TYPE_MAX
}				t_type;

typedef enum	e_state
{
	STATE_NONE,
	STATE_WAITING_FOR_STR,
	STATE_WAITING_FOR_FILE,
	STATE_MAX
}				t_state;

# pragma pack(1)

typedef struct	s_header
{
	uint8_t		type;
	uint32_t	size;
}				t_header;

typedef struct	s_file_data
{
	char		name[FILE_NAME_MAX_SIZE];
	mode_t		prot;
}				t_file_data;

# pragma pack()

#endif
