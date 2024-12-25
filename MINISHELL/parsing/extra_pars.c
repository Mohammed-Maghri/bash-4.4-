/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 23:21:20 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 15:53:38 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_for_here_doc(int pass)
{
	static int	waiting;

	if (pass == 1)
		waiting = 1;
	if (!pass)
		waiting = 0;
	return (waiting);
}

void	skip_red(t_list **tmp_2)
{
	if (compare((*tmp_2), HEREDOC))
		here_para(1);
	(*tmp_2) = (*tmp_2)->next;
	if ((*tmp_2) && (*tmp_2)->token_type == SPACEE)
		(*tmp_2) = (*tmp_2)->next;
	if ((*tmp_2) && (*tmp_2)->next)
		(*tmp_2) = (*tmp_2)->next;
}

void	close_herefiles(t_tracker *holder)
{
	t_list	*head;

	head = holder->head;
	while (head)
	{
		if (head->fd_in)
			close(head->fd_in);
		head = head->next;
	}
}
