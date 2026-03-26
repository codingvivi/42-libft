/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 11:51:59 by lrain             #+#    #+#             */
/*   Updated: 2025/12/20 19:53:52 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	clamp(size_t n, size_t max)
{
	if (n > max)
		return (max);
	else
		return (n);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	const size_t	slen = ft_strlen(s);
	const size_t	offset = clamp(start, slen);

	len = clamp(len, slen - offset);
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	return (ft_memcpy(ret, s + offset, len));
}
