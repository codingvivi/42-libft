/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:17:16 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 20:48:58 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	itoa_fwd_fd(const int n_original, unsigned int nb, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -((unsigned int)n);
	}
	else
		nb = (unsigned int)n;
	if (nb < 10)
	{
		c = nb + '0';
		write(fd, &c, 1);
	}
	else
		itoa_fwd_fd(n, nb, fd);
}

static void	itoa_fwd_fd(const int n_original, unsigned int nb, int fd)
{
	unsigned int	place_val;
	char			c;

	place_val = 1;
	while ((nb / 10) >= place_val)
		place_val *= 10;
	while (nb)
	{
		c = nb / place_val + '0';
		write(fd, &c, 1);
		nb %= place_val;
		place_val /= 10;
	}
	if (place_val && n_original != 0 && (n_original % place_val) == 0)
	{
		while (place_val)
		{
			write(fd, "0", 1);
			place_val /= 10;
		}
	}
}
