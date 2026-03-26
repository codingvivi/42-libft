/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:05:20 by lrain             #+#    #+#             */
/*   Updated: 2025/12/25 19:16:02 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static unsigned int	occurences(const char *s, char c);
static void			free_arr(char **arr, size_t size);
static char			**str_to_arr(const char *str, char delim, size_t n_words,
						char **arr);

char	**ft_split(char const *s, char c)
{
	char			**strings;
	unsigned int	n_words;

	if (!s)
		return (NULL);
	n_words = occurences(s, c);
	strings = malloc(sizeof(char *) * (n_words + 1));
	if (!strings)
		return (NULL);
	strings = str_to_arr(s, c, n_words, strings);
	return (strings);
}

static unsigned int	occurences(const char *s, char c)
{
	unsigned int	count;
	bool			in_word;

	count = 0;
	in_word = false;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (*s == c && in_word)
			in_word = false;
		s++;
	}
	return (count);
}

static char	**str_to_arr(const char *str, char delim, size_t n_words,
		char **arr)
{
	const char	*curr = str;
	const char	*next;
	size_t		i;
	size_t		len;

	i = 0;
	while (i < n_words)
	{
		next = ft_strchr(curr, delim);
		len = next - curr;
		if (len)
		{
			arr[i] = ft_substr(curr, 0, len);
			if (!arr[i])
			{
				free_arr(arr, i);
				return (NULL);
			}
			i++;
		}
		curr = next + 1;
	}
	arr[i] = NULL;
	return (arr);
}

static void	free_arr(char **arr, size_t size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}
