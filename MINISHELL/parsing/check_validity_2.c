/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:52:56 by mlouazir          #+#    #+#             */
/*   Updated: 2024/03/31 07:06:43 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_good(t_list *tmp, t_list *tmp_2)
{
	if (((compare(tmp, PIPE) || compare(tmp, REDIR_IN) || compare(tmp, \
	REDIR_OUT)) || compare(tmp, REDIR_APPEND) || compare(tmp, HEREDOC)) && \
	(compare(tmp_2, AND) || compare(tmp_2, OR) || \
	compare(tmp_2, PARA_CLOSE) || compare(tmp_2, PIPE)))
		return (print_error("syntax error", NULL), 1);
	if ((compare(tmp, REDIR_IN) || compare(tmp, REDIR_OUT) || \
	compare(tmp, OR) || compare(tmp, AND)) && (compare(tmp_2, \
	REDIR_IN) || compare(tmp_2, REDIR_OUT) || compare(tmp_2, \
	PARA_OPEN) || compare(tmp_2, PARA_CLOSE)))
		return (print_error("syntax error", NULL), 1);
	if (compare(tmp, REDIR_APPEND) && compare(tmp_2, REDIR_OUT))
		return (print_error("syntax error", NULL), 1);
	return (0);
}

int	helper_parc(t_list *tmp_2, int pass)
{
	if (!pass && (compare(tmp_2, WORD) || compare(tmp_2, PARA_CLOSE) || \
			compare(tmp_2, D_QU) || compare(tmp_2, S_QU) || \
			compare(tmp_2, HEREDOC) || compare(tmp_2, REDIR_IN) || \
			compare(tmp_2, REDIR_OUT) || compare(tmp_2, REDIR_APPEND) || \
			compare(tmp_2, DOLLAR)))
		return (1);
	if (pass && (compare(tmp_2, WORD) || compare(tmp_2, PARA_OPEN) || \
			compare(tmp_2, D_QU) || compare(tmp_2, S_QU) || \
			compare(tmp_2, HEREDOC) || compare(tmp_2, REDIR_IN) || \
			compare(tmp_2, REDIR_OUT) || compare(tmp_2, REDIR_APPEND) || \
			compare(tmp_2, DOLLAR)))
		return (1);
	return (0);
}

int	para_red(t_list *tmp_2)
{
	int	saved;

	saved = 0;
	while (tmp_2 && (!compare(tmp_2, PIPE) \
	&& !compare(tmp_2, AND) && !compare(tmp_2, OR) \
	&& !compare(tmp_2, PARA_CLOSE)))
	{
		if (compare(tmp_2, REDIR_APPEND) || \
		compare(tmp_2, REDIR_OUT) || compare(tmp_2, REDIR_IN) \
		|| (compare(tmp_2, HEREDOC)))
		{
			(compare(tmp_2, HEREDOC)) && (saved = 1);
			skip_red(&tmp_2);
		}
		else if (saved && ((compare(tmp_2, WORD) \
		|| compare(tmp_2, DOLLAR)) && compare(tmp_2->prev, SPACEE)))
			return (wait_for_here_doc(1), 2);
		else if (!saved && ((compare(tmp_2, WORD) \
		|| compare(tmp_2, DOLLAR)) && compare(tmp_2->prev, SPACEE)))
			return (1);
		else
			tmp_2 = tmp_2->next;
	}
	return (0);
}

int	check_para_2(t_list *tmp)
{
	t_list	*tmp_2;

	if (tmp->next)
	{
		tmp_2 = tmp->next;
		if (tmp_2->next && tmp_2->token_type == SPACEE)
			tmp_2 = tmp_2->next;
		if (para_red(tmp_2) || compare(tmp_2, PARA_OPEN) || \
			compare(tmp_2, D_QU) || compare(tmp_2, S_QU) \
			|| compare(tmp_2, WORD))
			return (print_error("syntax error", NULL), 1);
	}
	tmp_2 = tmp->prev;
	if (tmp_2->token_type == SPACEE)
		tmp_2 = tmp_2->prev;
	if (compare(tmp_2, PARA_OPEN) || \
	compare(tmp_2, OR) || compare(tmp_2, AND))
		return (print_error("syntax error", NULL), 1);
	return (0);
}

int	check_para(t_list *tmp)
{
	t_list	*tmp_2;

	if (tmp->token_type == PARA_OPEN)
	{
		if (tmp->prev)
		{
			tmp_2 = tmp->prev;
			while (tmp_2->prev && tmp_2->token_type == SPACEE)
				tmp_2 = tmp_2->prev;
			if (helper_parc(tmp_2, 0))
				return (print_error("syntax error", NULL), 1);
		}
		tmp_2 = tmp->next;
		if (tmp_2->token_type == SPACEE)
			tmp_2 = tmp_2->next;
		if (compare(tmp_2, PARA_CLOSE) || compare(tmp_2, SPACEE) || \
		compare(tmp_2, AND) || compare(tmp_2, OR) || compare(tmp_2, PIPE))
			return (print_error("syntax error", NULL), 1);
	}
	else
		if (check_para_2(tmp))
			return (1);
	return (0);
}
