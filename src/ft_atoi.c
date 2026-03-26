/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:26:32 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:02:13 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* nb = nb * 10 + (prefix * (*str++ - '0'));
mine: more functional but multiplies every time*/

static int	ft_isspace(int i);

int	ft_atoi(const char *str)
{
	int	nb;
	int	neg;

	nb = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (ft_isdigit(*str))
		nb = 10 * nb - (*str++ - '0');
	if (!neg)
		nb *= -1;
	return (nb);
}

static int	ft_isspace(int i)
{
	unsigned int		temp;
	const unsigned int	range = '\r' - '\t';

	temp = (unsigned)i;
	temp -= '\t';
	return (temp <= range || i == ' ');
}
