/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:31:10 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:08:05 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* will cause underflow during normalization */
int	ft_isprint(int c)
{
	const unsigned int	range = '~' - ' ';
	unsigned int		temp;

	temp = (unsigned)c;
	temp -= ' ';
	return (temp <= range);
}
