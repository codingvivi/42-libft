/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:20:25 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:17:12 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *const s2)
{
	const size_t	len_s1 = ft_strlen(s1);
	const size_t	len_s2 = ft_strlen(s2);
	const size_t	fulllen = len_s1 + len_s2;
	char			*dest;

	dest = malloc((fulllen + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, len_s1);
	ft_memcpy(dest + len_s1, s2, len_s2);
	dest[fulllen] = '\0';
	return (dest);
}
