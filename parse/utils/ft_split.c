#include "../../minishell.h"

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char *ft_white_space(char	*string)
{
	int index;

	index = 0;
	while (string[index])
	{
		if (ft_is_space(string[index]))
			return (string + index);
		index++;
	}
	return (NULL);
}

static size_t	ft_countword(char *s)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (ft_is_space(*s))
			s++;
		if (*s)
			count++;
		while (!ft_is_space(*s) && *s)
        	s++;
	}
	return (count);
}

int get_word_len(char *s, int i) {
	int start = i;
	bool double_quots = false;
	bool single_quots = false;

	while (s[i]) {
		if (s[i] == '\'' && !double_quots)
			single_quots = !single_quots;
		else if (s[i] == '\"' && !single_quots)
			double_quots = !double_quots;
		else if (ft_is_space(s[i]) && !single_quots && !double_quots)
			break;
		i++;
	}
	return (i - start);
}

int skip_spaces(char *s, int i) {
	while (s[i] && ft_is_space(s[i]))
		i++;
	return i;
}

char **ft_split(char *s) {
	int i = 0, j = 0;
	int word_len;
	int words = ft_countword(s);
	char **lst = malloc(sizeof(char *) * (words + 1));

	if (!lst)
		return NULL;
	while (s[i]) {
		i = skip_spaces(s, i);
		if (!s[i])
			break;
		word_len = get_word_len(s, i);
		lst[j++] = ft_substr(s, i, word_len);
		i += word_len;
	}
	lst[j] = NULL;
	return lst;
}
