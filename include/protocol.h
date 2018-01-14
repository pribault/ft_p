/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:22:43 by pribault          #+#    #+#             */
/*   Updated: 2018/01/14 16:18:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_H
# define PROTOCOL_H

# include "libft.h"

typedef enum	e_type
{
	TYPE_RAW_TEXT,
	TYPE_FILE,
	TYPE_SHELL_CMD,
	TYPE_MAX
}				t_type;

typedef enum	e_state
{
	STATE_IDLE,
	STATE_WAITING,
	STATE_DOWNLOADING,
	STATE_MAX
}				t_state;

# pragma pack(1)

typedef struct	s_header
{
	uint8_t		type;
	uint64_t	size;
}				t_header;

# pragma pack()

#endif
