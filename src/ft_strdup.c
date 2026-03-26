/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:09:14 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:16:21 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str1)
{
	size_t	size;
	char	*ret;

	size = ft_strlen(str1);
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	return (ft_memcpy(ret, str1, size + 1));
}
