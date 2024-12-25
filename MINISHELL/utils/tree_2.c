/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:33:25 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 14:19:46 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_content(t_list **tmp, t_tree *leaf)
{
	t_list	*tmp_2;
	t_list	*tmp_3;
	t_pt	bool;

	bool.e_bool = 0;
	bool.d_bool = 0;
	(*tmp)->is_visited = 0;
	while ((*tmp)->next && (!((*tmp)->next->is_visited) \
	|| (*tmp)->next->is_visited == 2))
		(*tmp) = (*tmp)->next;
	tmp_2 = (*tmp);
	while (tmp_2->prev && ((!tmp_2->prev->is_visited \
	|| tmp_2->prev->is_visited == 2)))
		tmp_2 = tmp_2->prev;
	tmp_3 = tmp_2;
	while (tmp_3 != (*tmp)->next)
	{
		if (tmp_3->token_type == REDIR_IN || tmp_3->token_type == HEREDOC || \
		tmp_3->token_type == REDIR_APPEND || tmp_3->token_type == REDIR_OUT)
			bool.d_bool++;
		else
			bool.e_bool++;
		tmp_3 = tmp_3->next;
	}
	set_content(tmp_2, (*tmp), leaf, bool.e_bool);
}

void	red_content_helper(t_tree *leaf, t_list *saved, t_list *tmp, int i)
{
	leaf->content = gc (sizeof(char *) * (i + 1), 0, 0, 0);
	i = 0;
	while (saved != tmp)
	{
		leaf->content[i++] = saved->content;
		saved = saved->next;
	}
	leaf->content[i] = NULL;
}

void	red_content(t_list *tmp, t_tree *leaf, t_list **next)
{
	t_list	*saved;
	int		i;

	i = 0;
	tmp->is_visited = 2;
	tmp = tmp->next;
	tmp->is_visited = 2;
	if (tmp->token_type == SPACEE)
	{
		tmp = tmp->next;
		tmp->is_visited = 2;
	}
	saved = tmp;
	while (tmp && (compare(tmp, WORD) \
	|| compare(tmp, DOLLAR) || compare(tmp, D_QU) \
	|| compare(tmp, S_QU)))
	{
		tmp->is_visited = 2;
		tmp = tmp->next;
		i++;
	}
	(*next) = tmp;
	red_content_helper(leaf, saved, tmp, i);
}

void	creat_leaf_helper(t_tree *leaf, t_list *node)
{
	leaf->b_q = gc(sizeof(int), 0, 1, 0);
	leaf->b_q[0] = 0;
	leaf->content = gc(sizeof(char *) * 2, 0, 0, 0);
	leaf->content[0] = node->content;
	leaf->content[1] = NULL;
	leaf->saved = NULL;
	leaf->is_in_pipe = 0;
	leaf->fd_in = 0;
	leaf->fd_out = 1;
	leaf->here_fd = node->fd_in;
	leaf->token_type = node->token_type;
	node->is_visited = 1;
}

t_tree	*creat_leaf(t_list *node, t_th *tree_h)
{
	t_tree	*leaf;
	t_list	*next;

	if (!node)
		return (NULL);
	leaf = gc(sizeof(t_tree), 0, 1, 0);
	leaf->tree_h = tree_h;
	creat_leaf_helper(leaf, node);
	next = node->next;
	if (compare(node, REDIR_APPEND) \
	|| compare(node, HEREDOC) \
	|| compare(node, REDIR_OUT) \
	|| compare(node, REDIR_IN))
		red_content(node, leaf, &next);
	else if (node->token_type == WORD || node->token_type == DOLLAR)
		fill_content(&node, leaf);
	(!tree_h->root) && (tree_h->root = leaf, 0);
	leaf->left = NULL;
	leaf->right = NULL;
	if (next && !(next->is_visited))
		leaf->right = tree_generator(next, tree_h);
	if (node->prev && !(node->prev->is_visited))
		leaf->left = tree_generator(node->prev, tree_h);
	return (leaf);
}
