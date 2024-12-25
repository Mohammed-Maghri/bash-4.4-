/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 23:09:30 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 18:32:22 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_red_in(t_tree *leaf)
{
	int	file;

	if (leaf->token_type == REDIR_IN)
	{
		file = open_in(leaf);
		if (file == -5)
			return (1);
	}
	else
	{
		file = leaf->here_fd;
		add_fd(leaf, file);
	}
	my_dup2(file, 0);
	exit_status(0, 0);
	if (!execution(leaf->right))
		execution(leaf->left);
	return (0);
}

int	exec_red_out(t_tree *leaf)
{
	int		file;

	file = open_out(leaf, leaf->token_type);
	if (file == -5)
		return (1);
	my_dup2(file, 1);
	exit_status(0, 0);
	if (!execution(leaf->right))
		execution(leaf->left);
	return (0);
}

void	exec_right(t_tree *leaf, int *pipe)
{
	my_dup2(pipe[0], 0);
	leaf->right->is_in_pipe = 1;
	execution(leaf->right);
	close_fds(leaf);
	gc(0, 2, 0, exit_status(0, 1));
}

void	exec_left(t_tree *leaf, int *pipe)
{
	my_dup2(pipe[1], 1);
	leaf->left->is_in_pipe = 1;
	execution(leaf->left);
	close_fds(leaf);
	gc(0, 2, 0, exit_status(0, 1));
}
