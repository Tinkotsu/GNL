/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <ifran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 21:48:43 by ifran             #+#    #+#             */
/*   Updated: 2019/09/18 17:28:35 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushback(t_list *lst, t_list *new_list)
{
	t_list *start;

	start = lst;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new_list;
	}
	else
		start = new_list;
	return (start);
}
