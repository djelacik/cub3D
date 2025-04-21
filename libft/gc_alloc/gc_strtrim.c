#include "gc_alloc.h"

char	*gc_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;

	if (!s1 || !set)
		return (NULL);
	if (!*s1)
		return (gc_strdup(""));
	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *end))
		end--;
	if (start > end)
		return (gc_strdup(""));
	return (gc_substr(s1, start - s1, end - start + 1));
}
