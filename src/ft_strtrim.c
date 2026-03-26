/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:28:15 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:27:19 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static char			*get_error_result(void);
static const char	*find_body_start(const char *str, const char *set);
static const char	*find_body_end(const char *start, const char *end,
						const char *set);
static bool			is_in_set(const char c, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dest;
	char		*result;
	t_substr	trim_str;

	if (!s1 || !set)
		return (NULL);
	trim_str.len = ft_strlen(s1);
	if (!trim_str.len)
		return (get_error_result());
	trim_str.start = find_body_start(s1, set);
	if (!*trim_str.start)
		return (get_error_result());
	trim_str.end = find_body_end(trim_str.start, s1 + trim_str.len - 1, set);
	if (!*trim_str.end)
		return (get_error_result());
	trim_str.len = (size_t)(trim_str.end - trim_str.start + 1);
	result = malloc((trim_str.len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	dest = result;
	while (trim_str.start <= trim_str.end)
		*dest++ = *trim_str.start++;
	*dest = '\0';
	return (result);
}

static char	*get_error_result(void)
{
	char	*result;

	result = malloc(sizeof(char));
	if (result)
		result[0] = '\0';
	return (result);
}

static bool	is_in_set(const char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

static const char	*find_body_start(const char *str, const char *set)
{
	while (*str)
	{
		if (!is_in_set(*str, set))
			return (str);
		str++;
	}
	return (str);
}

static const char	*find_body_end(const char *start, const char *end,
		const char *set)

{
	while (end >= start)
	{
		if (!is_in_set(*end, set))
			return (end);
		end--;
	}
	return (end);
}
