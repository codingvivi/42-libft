/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:37:34 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:20:05 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	is_match(const char *str, const char *to_find, size_t count)

{
	while (*str != '\0' && *to_find != '\0' && *str == *to_find && count--)
	{
		str++;
		to_find++;
	}
	if (*to_find == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t count)
{
	if (*needle == '\0')
		return ((char *)haystack);
	else
	{
		while (*haystack != '\0' && count)
		{
			if (is_match(haystack, needle, count))
				return ((char *)haystack);
			haystack++;
			count--;
		}
		return (NULL);
	}
}
