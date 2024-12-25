/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:43:53 by mlouazir          #+#    #+#             */
/*   Updated: 2024/03/29 01:35:29 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	jump_helper(t_list *tmp)
{
	if (compare(tmp, PIPE) || compare(tmp, OR) \
	|| compare(tmp, AND) || compare(tmp, REDIR_APPEND) \
	|| compare(tmp, REDIR_OUT) \
	|| compare(tmp, REDIR_IN) || compare(tmp, HEREDOC))
		return (1);
	return (0);
}

int	is_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != 32 && input[i] != 9)
			return (1);
	return (0);
}

void	jump_over(t_list **node)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = (*node)->next;
	while (tmp && !(tmp->is_visited))
	{
		if (!tmp->is_visited && jump_helper(tmp))
			i = 1;
		tmp = tmp->next;
	}
	if (detect_para(*node, &i))
		return ;
	i = 0;
	while ((*node) && (*node)->prev && !((*node)->prev->is_visited))
	{
		if ((*node)->token_type == PARA_CLOSE)
			i++;
		if ((*node)->token_type == PARA_OPEN)
			i--;
		(*node) = (*node)->prev;
		if (!i)
			break ;
	}
}

void	delete_para(t_list *end, t_list *node)
{
	while (node && node->token_type != PARA_CLOSE)
		node = node->prev;
	while (end && end->token_type != PARA_OPEN)
		end = end->next;
	end->token_type = SPACEE;
	end->content = ft_substr(" ", 0, 1);
	node->token_type = SPACEE;
	node->content = ft_substr(" ", 0, 1);
}

int	detect_para(t_list *node, int *i)
{
	t_list	*tmp;
	t_list	*end;
	t_pt	bool;

	bool.bc_bool = 0;
	bool.s_bool = 0;
	tmp = node;
	end = node;
	while (end->prev && ((!end->prev->is_visited \
	|| end->prev->is_visited == 2)))
		end = end->prev;
	while (tmp != end->prev)
	{
		if (tmp->token_type == PARA_CLOSE)
			bool.bc_bool++;
		if (!tmp->is_visited && !bool.bc_bool && jump_helper(tmp))
			bool.s_bool = 1;
		if (tmp->token_type == PARA_OPEN)
			bool.bc_bool--;
		tmp = tmp->prev;
	}
	if (bool.s_bool || *i == 1)
		return (0);
	delete_para(end, node);
	return (1);
}
