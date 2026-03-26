/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:46:40 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:18:51 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t count)
{
	char	*dst_start;

	dst_start = dst;
	if (!count--)
		return (ft_strlen(src));
	while (count && *src)
	{
		*dst = *src;
		count--;
		src++;
		dst++;
	}
	*dst = '\0';
	return ((dst - dst_start) + ft_strlen(src));
}
/* distance copied + remaining length of src */
/* doesn't have to traverse src twice,or have it be at original position */
