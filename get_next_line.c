/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <ifran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:11:36 by ifran             #+#    #+#             */
/*   Updated: 2019/09/20 02:27:26 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_get_line(t_list *list, const int fd, char **line)
{
	char	*temp;
	char	*new_str;
	size_t	new_len;
	size_t	temp_len;

	while (((t_file *)list->content)->fd != fd)
		list = list->next;
	temp = ft_strchr(((t_file *)list->content)->str, '\n');
	temp_len = ((temp) ? (ft_strlen(temp)) : (0));
	new_len = ft_strlen(((t_file *)list->content)->str) - temp_len;
	*line = ft_strncpy(ft_strnew(new_len + 1),\
			((t_file *)list->content)->str, new_len);
	new_str = (temp ? (ft_strncpy(ft_strnew(temp_len),\
				temp + 1, temp_len - 1)) : NULL);
	ft_strdel(&(((t_file *)list->content)->str));
	((t_file *)list->content)->str = new_str;
}

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
				ft_get_line(list, fd, line);
				return (1);
			}
			return (0);
		}
		list = list->next;
	}
	return (0);
}

static t_file	*filenew(const int fd, char *str)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->fd = fd;
	file->str = str;
	return (file);
}

static void		newlist(t_list **list, char *str, const int fd)
{
	t_list	*start;
	char	*new_str;

	new_str = NULL;
	start = *list;
	while (start)
	{
		if (((t_file *)start->content)->fd == fd)
		{
			new_str = ft_strjoin((((t_file *)start->content)->str), str);
			ft_strdel(&(((t_file *)start->content)->str));
			((t_file *)start->content)->str = new_str;
			ft_strdel(&str);
			return ;
		}
		start = start->next;
	}
	ft_lstadd(list, ft_lstnew((t_file *)(filenew(fd, str)), sizeof(t_file)));
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	char			*buf_str;
	int				c;

	if (check_list(list, fd, line) > 0)
		return (1);
	buf_str = ft_strnew(BUFF_SIZE + 1);
	if ((c = read(fd, buf_str, BUFF_SIZE)) < 0)
		return (-1);
	if (*buf_str && c)
	{
		newlist(&list, buf_str, fd);
		return (get_next_line(fd, line));
	}
	if (list && *(((t_file *)list->content)->str))
	{
		ft_get_line(list, fd, line);
		ft_lstfree(&list);
		return (1);
	}
	return (0);
}
