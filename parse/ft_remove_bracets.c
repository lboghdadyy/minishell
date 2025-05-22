#include "../minishell.h"

void	 bad_substitution(void)
{
	write(2, "minishell : bad substitution\n", ft_strlen("minishell : bad substitution\n"));
}

int	check_br(char *string)
{
	int	index;

	if (!string)
		return (1);
	index = 0;
	while (string[index])
	{
		while (string[index] && string[index] != '$')
			index++;
		if (string[index] == '$' && string[index + 1] == '{')
		{
			index++;
			if (string[index + 1] == '}')
				return (bad_substitution(), 1);
			while (string[index] && string[index] != '}')
			{
				if (ft_strchr("$.@#$^&*()\t ", string[index]))
					return (bad_substitution(), 1);
				index++;
			}
		}
	}
	return (0);
}

int	len_without_br(char *string)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (string[index])
	{
		if (string[index] != '{' || string[index] != '}')
			count++;
		index++;		
	}
	return (count);
}

char	*ft_remove_bracets(char *string)
{
	int		index;
	int		i;
	char	*clean;
	size_t	len;

	index = 0;
	i = 0;
	len = len_without_br(string);
	if (len == 0)
	{
		printf("case 3\n");
		return (bad_substitution(), NULL);
	}
	clean = ft_malloc(len + 1, ALLOC);
	while (string[index])
	{
		if (!ft_strchr("{}", string[index]))
		{
			clean[i] = string[index];
			i++;
		}
		index++;
	}
	clean[i] = 0;
	return (clean);
}
