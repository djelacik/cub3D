/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:59:00 by aapadill          #+#    #+#             */
/*   Updated: 2024/07/01 11:54:29 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_counter(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

static int	splitter(char **words, char const *s, char c, size_t q_words)
{
	size_t	i;
	char	*stop;

	i = 0;
	while (i < q_words && s)
	{
		while (*s == c)
			s++;
		stop = ft_strchr(s, c);
		if (!stop)
			stop = ft_strchr(s, 0);
		words[i] = ft_substr(s, 0, stop - s);
		if (!words[i])
		{
			while (i > 0)
				free(words[--i]);
			free(words);
			return (1);
		}
		s = stop + (*stop != 0);
		i++;
	}
	words[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c, int *n)
{
	size_t	q_words;
	char	**words;

	q_words = word_counter(s, c);
	*n = (int)q_words;
	words = malloc((q_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	if (splitter(words, s, c, q_words))
		return (NULL);
	return (words);
}
