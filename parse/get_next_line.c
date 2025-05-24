/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:37:47 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/24 20:21:49 by sbaghdad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cut_it(char *str)
{
	char	*cut;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	cut = ft_malloc(i + 1, ALLOC);
	if (!cut)
		return (free(str), NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		cut[i] = str[i];
		i++;
	}
	cut[i] = '\0';
	return (cut);
}

char	*change_index(char	*readed)
{
	int		i;
	int		j;
	char	*str;

	if (!readed)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (readed[i] != '\n' && readed[i])
		i++;
	if (readed[i] == '\n')
		i++;
	if (readed[i] == '\0')
		return (free(readed), NULL);
	str = ft_malloc(ft_strlen(readed + i) + 1, ALLOC);
	if (!str)
		return (free(readed), NULL);
	while (readed[i])
	{
		str[j] = readed[i];
		j++;
		i++;
	}
	str[j] = '\0';
	free(readed);
	return (str);
}

char	*get_it_gln(int fd, char *readed)
{
	char	*buffer;
	int		bytes;
	char	*tmp;

	bytes = 1;
	while (!ft_strchr(readed, '\n'))
	{
		buffer = ft_malloc(BUFFER_SIZE + 1, ALLOC);
		if (!buffer)
			return (NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0 && readed)
			return (free(buffer), readed);
		else if ((bytes == 0 && !readed) || bytes == -1)
			return (NULL);
		buffer[bytes] = '\0';
		tmp = ft_strj(readed, buffer);
		readed = tmp;
	}
	return (readed);
}

char	*get_next_line(char *prompt)
{
	static char	*readed;
	char		*line;
	char		*tmp;

	ft_putstr_fd(prompt, 1);
	readed = get_it_gln(0, readed);
	if (!readed)
	{
		return (NULL);
	}
	line = cut_it(readed);
	if (!line)
		return (line);
	tmp = change_index(readed);
	readed = tmp;
	return (line);
}
