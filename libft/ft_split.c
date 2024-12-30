/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:45:22 by djelacik          #+#    #+#             */
/*   Updated: 2024/05/03 10:38:09 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			i++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (i);
}

static void	*free_mem(char **word, char **start)
{
	while (word >= start)
	{
		free(*(word));
		*word = NULL;
		word--;
	}
	free(start);
	start = NULL;
	return (NULL);
}

static char	**split_array(const char *s, char c, char **split, char **start)
{
	size_t	i;
	size_t	j;
	int		word_len;

	i = -1;
	j = 0;
	word_len = 0;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && s[i] != '\0')
			word_len++;
		else if ((s[i] == c || i == ft_strlen(s)) && word_len > 0)
		{
			split[j] = ft_substr(s, i - word_len, word_len);
			if (!split[j])
			{
				free_mem(&split[j], start);
				return (NULL);
			}
			j++;
			word_len = 0;
		}
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	**start;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	start = split;
	if (!split_array(s, c, split, start))
		return (NULL);
	return (split);
}
