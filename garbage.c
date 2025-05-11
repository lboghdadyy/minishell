#include "minishell.h"

t_garbage	*ft_lstlast_garbage(t_garbage *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_garabage(t_garbage **lst, t_garbage *new)
{
	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_garbage(*lst)->next = new;
}

t_garbage	*ft_new_garbage(void *adress)
{
	t_garbage	*new;

	new = malloc (sizeof(t_garbage));
	if (!new)
	{
		free(adress);
		perror("malloc()");
		ft_malloc(0, CLEAR);
		return (NULL);
	}
	new->address = adress;
	new->next = NULL;
	return (new);
}

void	clear_it(t_garbage *garbage)
{
	t_garbage	*clear;

	while (garbage)
	{
		clear = garbage->next;
		free(garbage->address);
		free(garbage);
		garbage = clear;
	}
	clear_fds(0, 0 ,2);
}

int clear_fds(char *file, int type, int save)
{
	static int	fd[1024];
	static int	index = 0;

	if (save == 1)
	{
		if (type == RED_OUT || type == RED_IN)
			fd[index] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (type == APPE)
			fd[index] = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (fd[index] == -1)
			ft_malloc(0, CLEAR);
		// printf("opened = %d\n", fd[index]);
		return (fd[index++]);
	}
	else
	{
		// printf("here\n");
		for (int i = 0; i < index; i++)
		{
			close(fd[i]);
		}
		index = 0;
	}
	return (-1);
}



void	*ft_malloc(size_t size, int flag)
{
	static t_garbage	*garbage;
	void				*ret;

	if (flag == CLEAR)
	{
		clear_it(garbage);
		return (NULL);
		// exit(size);
	}
	ret = malloc(size);
	if (!ret)
	{
		clear_it(garbage);
		perror("malloc()");
		return (NULL);
		// exit(1);
	}
	add_to_garabage(&garbage, ft_new_garbage(ret));
	return (ret);
}
