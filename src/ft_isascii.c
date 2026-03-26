/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:44:21 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:07:31 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
unsigned example:

...0000 0111 1111 all 1s for bits in range
|1's complement
v
...1111 1000 0000 all bits outside range

1010 0111 0101
1111 1000 0000
--------------
1010 0000 0000 lets tru larger than range

0000 0110 1100 outside of range shouldnt exit
1111 1000 0000 range already 0
 --------------
0000 0000 0000 everything will be 0

signed uses 2's complement, but the pattern will still work

*/

int	ft_isascii(int c)
{
	const int	mask = ~0x7f;

	c &= mask;
	return (!(c));
}

/* 127, reversed, masks bits up to 127*/
/* only bits larger 127 will result in non 0*/
/* if non masked, outside range bits let thru anything */
