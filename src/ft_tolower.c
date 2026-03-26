/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:13:31 by lrain             #+#    #+#             */
/*   Updated: 2025/12/18 22:17:21 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isupper(int c)
{
	return ((unsigned)c - 'A' < 26);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c | 32);
	return (c);
}
