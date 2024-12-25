/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:19:47 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/18 16:25:31 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_and(t_tree *leaf)
{
	execution(leaf->left);
	if (leaf->left->token_type == 3 \
	|| (6 <= leaf->left->token_type && leaf->left->token_type <= 8))
	{
		my_dup2(leaf->tree_h->sav_in, 0);
		my_dup2(leaf->tree_h->sav_out, 1);
	}
	if (!exit_status(0, 1))
	{
		leaf->tree_h->path = path_maker(leaf->tree_h->env);
		execution(leaf->right);
	}
	if (leaf->right->token_type == 3 \
	|| (6 <= leaf->right->token_type && leaf->right->token_type <= 8))
	{
		my_dup2(leaf->tree_h->sav_in, 0);
		my_dup2(leaf->tree_h->sav_out, 1);
	}
	return (0);
}

int	exec_or(t_tree *leaf)
{
	execution(leaf->left);
	if (leaf->left->token_type == 3 \
	|| (6 <= leaf->left->token_type && leaf->left->token_type <= 8))
	{
		my_dup2(leaf->tree_h->sav_in, 0);
		my_dup2(leaf->tree_h->sav_out, 1);
	}
	if (exit_status(0, 1))
	{
		leaf->tree_h->path = path_maker(leaf->tree_h->env);
		execution(leaf->right);
	}
	if (leaf->right->token_type == 3 \
	|| (6 <= leaf->right->token_type && leaf->right->token_type <= 8))
	{
		my_dup2(leaf->tree_h->sav_in, 0);
		my_dup2(leaf->tree_h->sav_out, 1);
	}
	return (0);
}

int	exec_pipe(t_tree *leaf)
{
	int	pid_1;
	int	pid_2;
	int	*pipe;

	pid_1 = 0;
	pid_2 = 0;
	leaf->tree_h->pipe_i++;
	pipe = add_pipes(leaf->tree_h);
	pid_1 = my_fork();
	if (!pid_1)
		exec_left(leaf, pipe);
	else
	{
		pid_2 = my_fork();
		if (!pid_2)
			exec_right(leaf, pipe);
	}
	close_fds(leaf);
	waitpid(pid_2, &leaf->exit_status, 0);
	while (wait(NULL) != -1)
		;
	exit_status(WEXITSTATUS(leaf->exit_status), 0);
	return (0);
}

int	execution(t_tree *leaf)
{
	int	status;

	if (!leaf)
		return (0);
	if (leaf->token_type == AND)
		status = exec_and(leaf);
	else if (leaf->token_type == OR)
		status = exec_or(leaf);
	else if (leaf->token_type == PIPE)
		status = exec_pipe(leaf);
	else if (leaf->token_type == REDIR_IN \
	|| leaf->token_type == HEREDOC)
		status = exec_red_in(leaf);
	else if (leaf->token_type == REDIR_OUT \
	|| leaf->token_type == REDIR_APPEND)
		status = exec_red_out(leaf);
	else
		status = exec_word(leaf);
	return (status);
}
