/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifran <ifran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 01:31:43 by ifran             #+#    #+#             */
/*   Updated: 2019/09/19 16:37:13 by ifran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char			*arr;
	size_t			full_len;

	full_len = 0;
	if (s1 && s2)
		full_len = ft_strlen(s1) + ft_strlen(s2);
	else if (!s1 && s2)
		full_len = ft_strlen(s2);
	else if (s1 && !s2)
		full_len = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (full_len + 1));
	if (!arr)
		return (NULL);
	if (s1)
		arr = ft_strcpy(arr, s1);
	if (s2)
		arr = ft_strcat(arr, s2);
	if (!s1 && !s2)
		*arr = '\0';
	return (arr);
}
