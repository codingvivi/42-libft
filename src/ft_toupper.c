/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:18:27 by lrain             #+#    #+#             */
/*   Updated: 2025/12/19 11:59:36 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_islower(int c)
{
	return ((unsigned)c - 'a' < 26);
}

/* 1011111, unset 2^5, 32, which just flipped back to 0 for uppercases */
int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c & 0x5f);
	return (c);
}
