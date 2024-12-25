/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:20:28 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 11:11:20 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal_received;

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = 0;
		s++;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	if (count * size >= LONG_MAX)
		return (NULL);
	s = malloc(count * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

void	clear_all(t_gc *head)
{
	t_gc	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->address)
			free(head->address);
		if (head->fd != -1)
			close(head->fd);
		free(head);
		head = tmp;
	}
}

void	clear(t_gc *head)
{
	while (head)
	{
		if (head->address && head->flag == 1)
		{
			free(head->address);
			head->address = NULL;
		}
		if (head->fd != -1 && head->flag == 1)
		{
			close(head->fd);
			head->fd = -1;
		}
		head = head->next;
	}
	g_signal_received = 0;
}

void	*gc(int size, int pass, int flag, int exit_status)
{
	static t_gc	*head;
	t_gc		*node;
	void		*address;
	int			fd;

	fd = -1;
	address = NULL;
	if (!pass || pass == 3)
	{
		node = ft_calloc(sizeof(t_gc), 1);
		if (!pass)
			address = ft_calloc(size, 1);
		else
			fd = size;
		if (!node || ((!address) && !pass))
			return (printf("error in allocation\n"), \
			clear_all(head), exit(1), NULL);
		node->next = head;
		fill_node(node, address, fd, flag);
		head = node;
		return (address);
	}
	if (pass == 4)
		return (clear(head), NULL);
	return (clear_all(head), exit(exit_status), NULL);
}
