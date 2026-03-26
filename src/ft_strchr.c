/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:20:18 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:26:23 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* return pointer to find, or to nullterm if not found*/
/* if c is null term, retur end of string */
/* walk to end or until character match */
/* use strchrnul to  */
/* result doesnt match if 0 returned and 0 wasn't the char requested */

static char	*ft_strchrnul(const char *str, int c)
{
	c = (unsigned char)c;
	if (!c)
		return ((char *)str + ft_strlen(str));
	while (*str && *(unsigned char *)str != c)
		str++;
	return ((char *)str);
}

char	*ft_strchr(const char *str, int c)
{
	char	*search_res;

	search_res = ft_strchrnul(str, c);
	if (*(unsigned char *)search_res == (unsigned char)c)
		return (search_res);
	else
		return (NULL);
}
