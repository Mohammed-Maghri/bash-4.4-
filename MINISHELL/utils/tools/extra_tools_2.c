/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:36:05 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:29:36 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_node(t_gc *node, void *address, int fd, int flag)
{
	node->address = address;
	node->flag = flag;
	node->fd = fd;
}

void	check_for_prev(t_list **node)
{
	if ((*node)->token_type != WORD)
		return ;
	while ((*node) && (*node)->is_visited)
		(*node) = (*node)->prev;
}

void	check_for_next(t_list **node)
{
	if ((*node)->token_type != WORD)
		return ;
	while ((*node) && (*node)->is_visited)
		(*node) = (*node)->next;
}

void	add_dollar(t_list **tmp)
{
	if (!compare((*tmp)->next, DOLLAR))
		return ;
	(*tmp)->content = ft_strjoin((*tmp)->content, (*tmp)->next->content);
	(*tmp)->next = (*tmp)->next->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = (*tmp);
}

char	*checking(t_list *tmp)
{
	char	*res;

	res = tmp->content;
	tmp = tmp->next;
	while (tmp && (compare(tmp, DOLLAR) || compare(tmp, WORD)))
	{
		res = ft_strjoin(res, tmp->content);
		tmp = tmp->next;
	}
	return (res);
}
