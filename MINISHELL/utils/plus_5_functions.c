/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_5_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:13:38 by mlouazir          #+#    #+#             */
/*   Updated: 2024/03/29 01:20:09 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*jump_over_2(t_list *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->token_type == PARA_CLOSE)
			i++;
		if (node->token_type == PARA_OPEN)
			i--;
		node = node->next;
		if (!i)
			break ;
	}
	return (node);
}

int	is_delimiter(char c, int pass)
{
	if (!pass)
		return (c == ' ' || c == 9 || c == '\'' || \
		c == '\"' || c == '&' || c == '|' || \
		c == '<' || c == '>' || c == 0 || c == '(' || \
		c == ')' || c == '$');
	return (c == '<' || c == '>' || c == '&' || c == '|' || c == '(' || \
	c == ')');
}

void	jump_over_leftside(t_list **node)
{
	int		i;

	i = 0;
	while ((*node) && (*node)->next && !((*node)->next->is_visited))
	{
		if ((*node)->token_type == PARA_OPEN)
			i++;
		if ((*node)->token_type == PARA_CLOSE)
			i--;
		(*node) = (*node)->next;
		if (!i)
			break ;
	}
}
