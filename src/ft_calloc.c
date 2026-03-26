/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:12:06 by lrain             #+#    #+#             */
/*   Updated: 2025/12/26 16:30:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
for errno:

#include <errno.h>

    if (nmemb > (size_t)-1 / size)
    {
        errno = ENOMEM;
        return (NULL);
    }
if count * size > SIZE_MAX
SIZE_MAX = max size_t, so -1 underflows to it
divide by size to prevent multiplication from overflowing
*/

void *ft_calloc(size_t nmemb, size_t size)
{
	void  *ret;
	size_t total_size;

	if (!nmemb || !size)
		return (malloc(0));

	if (nmemb > (size_t) -1 / size)
		return (malloc(0));
	total_size = size * nmemb;
	ret = malloc(total_size);
	if (!ret)
		return (NULL);
	return (ft_memset(ret, 0, total_size));
}
