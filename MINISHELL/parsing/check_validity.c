/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:21:33 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/03 23:43:59 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal_received;

void	merge_nodes(t_list *starting_point, \
t_list *ending_point, int new_type)
{
	t_list	*tmp;

	tmp = starting_point->next;
	if (tmp == ending_point)
		starting_point->content = ft_strjoin(starting_point->content, \
		tmp->content);
	else
	{
		while (tmp != ending_point->next)
		{
			starting_point->content = ft_strjoin(starting_point->content, \
			tmp->content);
			tmp = tmp->next;
		}
	}
	starting_point->next = ending_point->next;
	if (ending_point && ending_point->next)
		ending_point->next->prev = starting_point;
	starting_point->token_type = new_type;
}

void	join_quotes(t_list **starting_point)
{
	t_list	*tmp;
	int		token_type;

	tmp = (*starting_point)->next;
	token_type = (*starting_point)->token_type;
	(*starting_point)->q_type = token_type;
	while (tmp && (tmp->token_type != token_type))
		tmp = tmp->next;
	merge_nodes((*starting_point), tmp, WORD);
}

int	syntax_checker(t_list *tmp)
{
	t_list	*tmp_2;

	if ((!(tmp->next) && (tmp->token_type != D_QU && \
	tmp->token_type != S_QU)) || (!(tmp->prev) && (tmp->token_type != REDIR_IN \
	&& tmp->token_type != REDIR_OUT && tmp->token_type != HEREDOC && \
	tmp->token_type != REDIR_APPEND)))
		return (print_error("syntax error", NULL), 1);
	else
	{
		tmp_2 = tmp;
		tmp_2 = tmp_2->next;
		if (tmp->next->token_type == SPACEE)
			tmp_2 = tmp_2->next;
		if (!ft_strncmp("||", tmp->content, 2) || !ft_strncmp("&&", \
		tmp->content, 2))
		{
			if (compare(tmp_2, PIPE) || compare(tmp_2, AND) \
			|| compare(tmp_2, OR))
				return (print_error("syntax error", NULL), 1);
		}
		else
			if (is_good(tmp, tmp_2))
				return (1);
	}
	return (0);
}

void	check_dollar(t_list	**tmp, t_list *next)
{
	t_list	*prev;

	if (compare((*tmp), DOLLAR) && compare(next, WORD))
	{
		if (compare((*tmp)->prev, WORD) && \
		((*tmp)->prev->q_type != 11 && (*tmp)->prev->q_type != 12))
			(*tmp) = (*tmp)->prev;
		merge_nodes((*tmp), next, DOLLAR);
	}
	else if (compare((*tmp), DOLLAR) \
	&& ((compare(next, D_QU) || compare(next, S_QU))))
	{
		if ((*tmp)->prev)
		{
			prev = (*tmp)->prev;
			prev->next = next;
			next->prev = prev;
		}
		else
		{
			(*tmp) = (*tmp)->next;
			(*tmp)->prev = NULL;
		}
	}
}

int	check_validity(t_tracker *holder)
{
	t_list		*tmp;
	int			detecter;

	tmp = holder->head;
	while (tmp && !g_signal_received)
	{
		detecter = 0;
		if (compare(tmp, DOLLAR))
			check_dollar(&tmp, tmp->next);
		if (compare(tmp, D_QU) || compare(tmp, S_QU))
			join_quotes(&tmp);
		else if (compare(tmp, HEREDOC) && tmp->fd_in == 0)
			detecter = run_here_doc(tmp, holder->env);
		else if (compare(tmp, PARA_OPEN) || compare(tmp, PARA_CLOSE))
			detecter = check_para(tmp);
		else if ((tmp->token_type != WORD) && \
		(tmp->token_type != SPACEE) && (tmp->token_type != DOLLAR) && \
		(tmp->token_type != PARA_CLOSE) && (tmp->token_type != PARA_OPEN))
			detecter = syntax_checker(tmp);
		if (detecter && !wait_for_here_doc(5))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
