/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaghdad <sbaghdad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:37:47 by sbaghdad          #+#    #+#             */
/*   Updated: 2025/05/18 21:10:50 by sbaghdad         ###   ########.fr       */
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

char	*change_index(char	*rest)
{
	int		i;
	int		j;
	char	*str;

	if (!rest)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (rest[i] != '\n' && rest[i])
		i++;
	if (rest[i] == '\n')
		i++;
	if (rest[i] == '\0')
		return (free(rest), NULL);
	str = ft_malloc(ft_strlen(rest + i) + 1, ALLOC);
	if (!str)
		return (free(str), free(rest), NULL);
	while (rest[i])
	{
		str[j] = rest[i];
		j++;
		i++;
	}
	str[j] = '\0';

	return (str);
}

void herdoc_signal(int sig)
{
	(void)sig;
	signal_status(1);
}

char	*get_it(int fd, char *rest)
{
	char	*buffer;
	int		bytes;
	char	*tmp;

	bytes = 1;
	signal(SIGINT, &herdoc_signal);
	while (!ft_strchr(rest, '\n'))
	{
		if (signal_status(-1))
		{
			close(0);
			break;
		}
		buffer = ft_malloc((size_t)BUFFER_SIZE + 1, ALLOC);
		bytes = read(fd, buffer, (size_t)BUFFER_SIZE);
		if (bytes == 0 && rest)
			return (rest);
		else if ((bytes == 0 && !rest) || bytes == -1)
			return (NULL);
		buffer[bytes] = '\0';
		tmp = ft_strjoin(rest, buffer);
		rest = tmp;
	}
	tmp = NULL;
	if (signal_status(-1))
		return (NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*after_new_line;
	char		*line;
	char		*tmp;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	after_new_line = get_it(fd, after_new_line);
	if (!after_new_line)
	{
		free(after_new_line);
		return (NULL);
	}
	line = cut_it(after_new_line);
	if (!line)
	{
		return (free (after_new_line), line);
	}
	tmp = change_index(after_new_line);
	after_new_line = tmp;
	return (line);
}
