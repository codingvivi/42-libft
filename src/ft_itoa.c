/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:52:24 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:09:31 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/* negative number i casts to max - i = x, x = number with distance i of max
negation of uint n is max - n
max - x = i */

static size_t	get_len(int n)
{
	unsigned int	nb;
	size_t			len;

	len = 0;
	if (n <= 0)
		len++;
	if (n < 0)
		nb = -((unsigned int)n);
	else
		nb = (unsigned int)n;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	nb;

	len = get_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[len] = '0';
	if (n < 0)
		nb = -((unsigned int)n);
	else
		nb = (unsigned int)n;
	while (nb)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[len] = '-';
	return (str);
}
