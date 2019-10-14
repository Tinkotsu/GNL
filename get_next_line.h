/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:52:26 by ifran             #+#    #+#             */
/*   Updated: 2019/10/14 14:53:00 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include "libft.h"

typedef struct		s_file
{
	int				fd;
	char			*str;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
