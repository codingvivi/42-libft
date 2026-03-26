/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 14:20:25 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:32:14 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *m, int c, size_t count)
{
	const unsigned char	*src = m;

	c = (unsigned char)c;
	while (count--)
	{
		if (src[count] == c)
			return ((void *)(src + count));
	}
	return (NULL);
}

char	*ft_strrchr(const char *str, int c)
{
	return (ft_memrchr(str, c, ft_strlen(str) + 1));
}
