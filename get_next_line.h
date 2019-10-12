/* HEADER */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

# include "libft.h"

typedef struct 		s_file
{
	int 			fd;
	char 			*str;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
