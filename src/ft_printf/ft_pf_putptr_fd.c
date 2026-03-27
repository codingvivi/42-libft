/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putptr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/02/19 18:39:14 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_pf_internal.h"

int	ft_pf_putptr_fd(void *ptr, int fd)
{
	int			count;
	uintptr_t	ptr_as_num;

	count = 0;
	if (!ptr)
		return (ft_pf_putstr_fd("(nil)", fd));
	ptr_as_num = (uintptr_t)ptr;
	count += ft_pf_putstr_fd("0x", fd);
	count += ft_pf_putnbru_base_fd(ptr_as_num, fd, "0123456789abcdef");
	return (count);
}
