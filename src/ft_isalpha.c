/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 01:23:38 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:06:59 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
01000001 A
00100000 32 --> power of 2, 1 followed by 0s
-------
01100001 a

adds 32 if number has 0 in
adds 32 if 0-31 or 65-97

for sane bit representation/the pattern to work
unifies blocks of 64
normalizes, sets the scale to 'a'
only check for one range and only one side. wow...

*/

int	ft_isalpha(int c)
{
	unsigned int	temp;

	temp = (unsigned)c;
	temp |= 32;
	temp -= 'a';
	return (temp < 26);
}
