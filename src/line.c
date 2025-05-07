/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:54:14 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 01:54:15 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	line_is_only_spaces(char *line)
{
	size_t	count;
	char	*original;
	
	count = 0;
	original = line;
	while (*line)
	{
		if (*line == ' ')
			count++;
		line++;
	}
	if (ft_strlen(original) == count)
		return (true);
	return (false);
}

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (!valid_character(*line))
			return (false);
		line++;
	}
	return (true);
}

//*key and *rest point at new malloc strings
bool	split_line(char *line, char **key, char **rest)
{
	char	*trimmed;
	char	*sep;

	trimmed = gc_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (false);
	sep = trimmed;
	//find the first space, that will be our separator
	while (*sep && !ft_isspace(*sep))
		sep++;
	if (!*sep)
		return (false);
	*sep = '\0';
	sep++;
	//skip spaces before the rest
	while (ft_isspace(*sep))
		sep++;
	if (!*sep)
		return (false);
	*key = gc_strdup(trimmed);
	*rest = gc_strtrim(sep, " \t\n\r");
	return (*key && *rest);
}

