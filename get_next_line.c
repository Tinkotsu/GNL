/* HEADER */

#include "get_next_line.h"

static	t_list	*s_check_and_create(t_list **list, int fd)
{
	t_file	*file;
	t_list	*temp;

	temp = *list;
	while (temp)
	{
		if (((t_file *)temp->content)->fd == fd)
			return (temp);
		temp = temp->next;
	}
	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	file->str = NULL;
	file->fd = fd;
	ft_lstadd(list, ft_lstnew(file, sizeof(t_file)));
	return (*list);
}

static int		get_buff(t_list *list, char **buff)
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

static int		push_line(t_list *list, char **line)
{
	char	*temp;
	char	*str;

	str = ((t_file *)list->content)->str;
	if (!str)
		return (0);
	if ((temp = ft_strchr(str, '\n')))
	{
		*line = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(temp));
		if (*(++temp))
			((t_file *)list->content)->str = ft_strdup(temp);
		else
			((t_file *)list->content)->str = NULL;
	}
	else
	{
		*line = ft_strdup(str);
		((t_file *)list->content)->str = NULL;
	}
	ft_strdel(&str);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int				c;
	char			*buff;
	static	t_list	*list;
	t_list			*curr;

	if (fd < 0)
		return (-1);
	*line = NULL;
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
