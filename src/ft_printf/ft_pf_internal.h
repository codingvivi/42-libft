/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 00:00:00 by lrain             #+#    #+#             */
/*   Updated: 2026/02/20 00:00:00 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PF_INTERNAL_H
# define FT_PF_INTERNAL_H

# include <stdint.h>

int	ft_pf_putchar_fd(char c, int fd);
int	ft_pf_putstr_fd(char *s, int fd);
int	ft_pf_putptr_fd(void *ptr, int fd);
int	ft_pf_putnbr_base_fd(int nb, char *base_digits, int fd);
int	ft_pf_putnbru_base_fd(uint64_t nb, int fd, char *base_digits);

#endif
