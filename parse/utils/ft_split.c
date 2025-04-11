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

char	**ft_split(char *s)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (ft_is_space(*s) && *s)
			s++;
		if (*s)
		{
			if (!ft_white_space(s))
				word_len = ft_strlen(s);
			else
				word_len = ft_white_space(s) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}
