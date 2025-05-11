#include "../../minishell.h"

int skip_spaces(char *s, int i)
{
	while (s[i] && ft_is_space(s[i]))
		i++;
	return i;
}


int get_word_len(char *s, int i)
{
	int start = i;
	bool double_quots = false;
	bool single_quots = false;

	if (s[i] == '|')
		return (1);
	if (ft_strchr("<>", s[i]))
	{
		while (ft_strchr("<>", s[i]) && s[i])
			i++;
		return (i - start);
	}
	while (s[i])
	{
		if (ft_strchr("|<>", s[i]) && !single_quots && !double_quots)
			return (i - start);
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

int	ft_countword(char *s)
{
	int i = 0;
	int count = 0;
	while (s[i])
	{
		i = skip_spaces(s, i);
		if (!s[i])
			break;
		i += get_word_len(s, i);
		count++;
	}
	return count;
}


char **ft_split(char *s)
{
	int i = 0;
	int j = 0;
	int word_len;
	int words = ft_countword(s);
	char **lst = ft_malloc(sizeof(char *) * (words + 1), ALLOC);

	if (!lst)
		return NULL;
	while (s[i])
	{
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
