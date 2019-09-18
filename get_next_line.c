/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <ifran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:11:36 by ifran             #+#    #+#             */
/*   Updated: 2019/09/18 19:11:25 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_list(t_list *list, const int fd, char **line)
{
	if (!list)
		return (0);
	while (list)
	{
		if (((t_file *)list->content)->fd == fd)
		{
			if (ft_strchr(((t_file *)list->content)->str, '\n'))
			{
				get_line(list, fd, line);
				return (1);
			}
			if (ft_strchr(((t_file *)list->content)->str, '\0'))
				return (-1);
			return (0);
		}
		list = list->next;
	}
	return (0);
}

static t_file	*filenew(const int fd, char *str)
{
	t_file	*file;

	if (!str || !fd)
		return (NULL);
	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->fd = fd;
	file->str = *str;
	return (file);
}

void			get_line(t_list *list, const int fd, char **line)
{
	char	*temp;
	char	*new_str;
	size_t	new_len;

	while(((t_file *)list->content)->fd != fd)
		list = list->next;
	if (!(temp = ft_strchr(((t_file *)list->content)->str, '\n')))
		return (0);
	new_len = ft_strlen(((t_file *)list->content)->str) - ft_strlen(temp);
	*line = ft_strncpy(ft_strnew(new_len + 1),\
									((t_file *)list->content)->str, new_len);
	new_str = ft_strncpy(ft_strnew(ft_strlen(temp)),\
									temp + 1, ft_strlen(temp) - 1);
	ft_strdel(&(((t_file *)list->content)->str));
	((t_file *)list->content)->str = new_str;
}

void			newlist(t_list *list, char *str, const int fd)
{
	t_list	*start;
	char	*new_str;

	start = list;
	while (list)
	{
		if (((t_file *)list->content)->fd == fd)
		{
			new_str = ft_strjoin((((t_file *)list->content)->str), str);
			ft_strdel(&(((t_file *)list->content)->str));
			((t_file *)list->content)->str = new_str;
			return ;
		}
		list = list->next;
	}
	lstadd(&start, lstnew(filenew(fd, str), sizeof(t_file)));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	char			*buf_str;

	if(check_list(list, fd, line) > 0)
		return (1);
	if (check_list(list, fd, line) < 0)
		return (0);
	buf_str = ft_strnew(BUFF_SIZE + 1); 
	if (read(fd, buf_str, BUFF_SIZE) < 0)
		return (-1);
	newlist(list, buf_str, fd);
	return (get_next_line(fd, line));
}
