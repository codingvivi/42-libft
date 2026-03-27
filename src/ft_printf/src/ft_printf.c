/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 05:14:10 by lrain             #+#    #+#             */
/*   Updated: 2026/02/22 15:27:40 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf_internal.h"
#include <stdarg.h>
#include <unistd.h>

static int	printf_write(char c, va_list *ap);

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	if (!str)
		return (-1);
	va_start(ap, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
			count += printf_write(*(++str), &ap);
		else
			count += write(1, &(*str), 1);
		str++;
	}
	va_end(ap);
	return (count);
}

static int	printf_write(char c, va_list *ap)
{
	int	count;

	count = 0;
	if (c == '%')
		count = write(1, "%", 1);
	else if (c == 'c')
		count = ft_pf_putchar_fd(va_arg(*ap, int), 1);
	else if (c == 's')
		count = ft_pf_putstr_fd(va_arg(*ap, char *), 1);
	else if (c == 'p')
		count = ft_pf_putptr_fd(va_arg(*ap, void *), 1);
	else if (c == 'd' || c == 'i')
		count = ft_pf_putnbr_base_fd(va_arg(*ap, int), "0123456789", 1);
	else if (c == 'u')
		count = ft_pf_putnbru_base_fd(va_arg(*ap, unsigned int), 1,
				"0123456789");
	else if (c == 'x')
		count = ft_pf_putnbru_base_fd(va_arg(*ap, unsigned int), 1,
				"0123456789abcdef");
	else if (c == 'X')
		count = ft_pf_putnbru_base_fd(va_arg(*ap, unsigned int), 1,
				"0123456789ABCDEF");
	return (count);
}
