/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tinkotsu <tinkotsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:22:38 by ifran             #+#    #+#             */
/*   Updated: 2019/10/13 23:50:31 by tinkotsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_list	    *s_check_and_create(t_list **list, int fd)
{
    t_file	*file;
    t_list	*temp;
	t_list	*new;

    if (fd < 0)
		return (NULL);
    temp = *list;
    while (temp)
    {
		if (((t_file *)temp->content)->fd == fd)
		    return (temp);
		temp = temp->next;
    }
	if (!(new = ft_lstnew(file, sizeof(t_file))))
		return (NULL);
	((t_file *)new->content)->str = NULL;
    ((t_file *)new->content)->fd = fd;
    ft_lstadd(list, new);
    return (*list);
}

static int	    get_buff(t_list *list, char **buff)
{
    char	*temp;
    int		res;

    res = 0;
    temp = ((t_file *)list->content)->str;
    if (temp)
    {
		((t_file *)list->content)->str = ft_strjoin(temp, *buff);
		ft_strdel(&temp);
    }
    else
		((t_file *)list->content)->str = ft_strdup(*buff);
    if (ft_strchr(((t_file *)list->content)->str, '\n'))
		res = 1;
    ft_strclr(*buff);
    return (res);
}

static int	    push_line(t_list *list, char **line)
{
    char	*temp;
    char	*str;

    if (!(str = ((t_file *)list->content)->str))
		return (0);
    if (!(temp = ft_strchr(str, '\n')))
		*line = ft_strdup(str);
    else
    {
		*line = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(temp));
		if (!(*(++temp)))
	    	temp = NULL;
		else
		    temp = ft_strdup(temp);
    }
    ((t_file *)list->content)->str = temp;
    ft_strdel(&str);
    return (1);
}

int		    get_next_line(const int fd, char **line)
{
    int		    c;
    char	    *buff;
    static  t_list  *list;
    t_list	    *curr;

    buff = ft_strnew(BUFF_SIZE);
    if (!(curr = s_check_and_create(&list, fd)))
		return (-1);
    while ((c = read(fd, buff, BUFF_SIZE)) > 0)
		if (get_buff(curr, &buff))
		    break ;
    ft_strdel(&buff);
    if (c < 0)
		return (-1);
    if (push_line(curr, line))
		return (1);
    return (0);
}
