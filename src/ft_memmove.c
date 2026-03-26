/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:09:11 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:13:39 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

/* underflow forbidden range to max number */
void	*ft_memmove(void *dest, const void *src, size_t count)
{
	const char		*s = src;
	const uintptr_t	overlap_range = -2 * count;
	uintptr_t		distance;
	char			*d;

	d = dest;
	distance = (uintptr_t)s - (uintptr_t)d;
	if (d == s)
		return (d);
	if (distance - count <= overlap_range)
		return (ft_memcpy(d, s, count));
	if (d < s)
	{
		while (count--)
			*d++ = *s++;
	}
	else
		while (count--)
			d[count] = s[count];
	return (dest);
}
/* subtract pointer adresses as numbers  */
/* if non overlap use (theoretically) faster memcpy */
/* if dest to the left, copy from right to left and vice versa*/
