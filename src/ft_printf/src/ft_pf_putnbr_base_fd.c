/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_putnbr_base_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 03:40:15 by lrain             #+#    #+#             */
/*   Updated: 2026/02/20 17:16:31 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_pf_internal.h"

static int	itoa_fwd_fd(uint64_t nb, int fd, char *b_digi, unsigned int base);

int	ft_pf_putnbr_base_fd(int nb, char *base_digits, int fd)
{
	unsigned int	nb_u;
	int				count;

	count = 0;
	if (nb < 0)
	{
		count += write(fd, "-", 1);
		nb_u = -((unsigned int)nb);
	}
	else
		nb_u = (unsigned int)nb;
	count += ft_pf_putnbru_base_fd(nb_u, fd, base_digits);
	return (count);
}

/* uint64_t since we need nb to possibly hold a pointer,
which is larger than an unsigned int on 64 bit systems.
*/
int	ft_pf_putnbru_base_fd(uint64_t nb, int fd, char *base_digits)
{
	unsigned int	b_len;
	int				count;

	count = 0;
	b_len = 0;
	while (base_digits[b_len])
		b_len++;
	if (nb < b_len)
		count += write(fd, &base_digits[nb], 1);
	else
		count += itoa_fwd_fd(nb, fd, base_digits, b_len);
	return (count);
}

static int	itoa_fwd_fd(uint64_t nb, int fd, char *b_digi, unsigned int base)
{
	uint64_t	original_nb;
	int			count;
	uint64_t	place_val;

	original_nb = nb;
	count = 0;
	place_val = 1;
	while ((nb / base) >= place_val)
		place_val *= base;
	while (nb)
	{
		count += write(fd, &b_digi[nb / place_val], 1);
		nb %= place_val;
		place_val /= base;
	}
	if (place_val && original_nb != 0 && (original_nb % place_val) == 0)
	{
		while (place_val)
		{
			count += write(fd, &b_digi[0], 1);
			place_val /= base;
		}
	}
	return (count);
}
