/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/02/19 00:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_pf_putstr_fd(char *s, int fd)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = "(null)";
	while (*s)
		count += write(fd, s++, 1);
	return (count);
}
