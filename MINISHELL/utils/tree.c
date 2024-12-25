/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:52:38 by mlouazir          #+#    #+#             */
/*   Updated: 2024/03/29 01:16:04 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*look_for(t_list *tmp, int token_type, int var)
{
	while (tmp && tmp->prev && !(tmp->prev->is_visited) && \
	tmp->token_type != token_type && tmp->token_type != var)
	{
		if (tmp->token_type == PARA_CLOSE)
			jump_over(&tmp);
		else
			tmp = tmp->prev;
	}
	return (tmp);
}

t_list	*find_leftside(t_list *node, int token_type)
{
	t_pt	var;

	if (token_type == REDIR_IN)
	{
		var.bc_bool = REDIR_APPEND;
		var.e_bool = REDIR_OUT;
		var.ex_bool = HEREDOC;
	}
	reset_to_left(&node);
	while (node && node->next && !(node->next->is_visited) \
	&& (!compare(node, token_type)))
	{
		if (token_type == REDIR_IN \
		&& (compare(node, var.bc_bool) \
		|| compare(node, var.e_bool) \
		|| compare(node, var.ex_bool)))
			break ;
		if (node->token_type == PARA_OPEN)
			jump_over_leftside(&node);
		else
			node = node->next;
	}
	return (node);
}

t_list	*search_for(t_list *node)
{
	t_list	*tmp;
	int		token_type;
	int		var;

	token_type = 0;
	reset_to_right(&node);
	while (++token_type < 6)
	{
		var = 15;
		(token_type == 1) && (var = 0, 0);
		tmp = node;
		if (token_type == PIPE || token_type == REDIR_IN)
			tmp = find_leftside(node, token_type);
		else
			tmp = look_for(tmp, token_type, var);
		if (tmp && (tmp->token_type == token_type || \
		tmp->token_type == var || (token_type == REDIR_IN \
		&& (compare(tmp, REDIR_IN) || compare(tmp, REDIR_APPEND) \
		|| compare(tmp, REDIR_OUT) || compare(tmp, HEREDOC)))))
			return (tmp);
	}
	return (NULL);
}

t_tree	*tree_generator(t_list *node, t_th *tree_h)
{
	t_tree	*leaf;

	if (!node)
		return (NULL);
	leaf = creat_leaf(search_for(node), tree_h);
	return (leaf);
}
