/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:27:23 by lrain             #+#    #+#             */
/*   Updated: 2025/12/10 16:17:58 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	*test_str;
	int		length;

	test_str = "42 chars long...null terminator included!!";
	length = ft_strlen(test_str);
	printf("the test string is:\n%s\n", test_str);
	printf("length is:%d", length);
	return (0);
}
