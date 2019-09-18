/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 01:58:14 by ifran             #+#    #+#             */
/*   Updated: 2019/09/11 15:09:14 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	char	*arr_start;

	if (!s)
		return (NULL);
	while (start)
	{
		++s;
		--start;
	}
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr_start = arr;
	while (len)
	{
		*arr++ = *s++;
		--len;
	}
	*arr = '\0';
	return (arr_start);
}
