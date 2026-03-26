/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:40:50 by lrain             #+#    #+#             */
/*   Updated: 2025/12/22 18:48:03 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	char			*retstr;
	char			*ret0;

	i = 0;
	str = (char *)s;
	retstr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!retstr)
		return (NULL);
	ret0 = retstr;
	while (*str)
		*retstr++ = f(i++, *str++);
	*retstr = '\0';
	return (ret0);
}
