/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:18:35 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:18 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	helper(t_list **node, t_tree *leaf)
{
	if ((*node)->token_type == HEREDOC)
	{
		if (leaf->here_fd)
			close(leaf->here_fd);
		leaf->here_fd = (*node)->fd_in;
	}
	(*node) = (*node)->next;
	if ((*node)->token_type == SPACEE)
		(*node) = (*node)->next;
}

void	set_content(t_list *tmp_2, t_list *tmp, t_tree *leaf, int size)
{
	int	i;

	i = 0;
	leaf->content = gc(sizeof(char *) * (size + 1), 0, 0, 0);
	while (tmp_2 != tmp->next)
	{
		if (tmp_2->token_type == PARA_OPEN)
			tmp_2 = jump_over_2(tmp_2);
		if (tmp_2 && !tmp_2->is_visited)
		{
			leaf->content[i++] = tmp_2->content;
			tmp_2->is_visited = 1;
			tmp_2 = tmp_2->next;
		}
		else
			tmp_2 = tmp_2->next;
	}
	leaf->content[i] = NULL;
}

void	reset_to_right(t_list **node)
{
	if (!(*node))
		return ;
	while ((*node)->next && !((*node)->next->is_visited))
		(*node) = (*node)->next;
}

void	reset_to_left(t_list **node)
{
	if (!(*node))
		return ;
	while ((*node)->prev && !((*node)->prev->is_visited))
		(*node) = (*node)->prev;
}
