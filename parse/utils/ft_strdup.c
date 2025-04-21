#include "../../minishell.h"

char *ft_strdup(char *src)
{
	int i = 0;
	char *res;

	if (!src)
		return (NULL);
	while(src[i])
		i++;
	res = ft_malloc(sizeof(*res) * i + 1, ALLOC);
	if (res == NULL)
		return (NULL);
	i = 0;
	while(src[i])
	{
		res[i]=src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}