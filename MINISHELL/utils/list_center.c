/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_center.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:43:57 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:39:40 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*declare_node(void)
{
	t_list	*new_node;

	new_node = gc(sizeof(t_list), 0, 1, 0);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->is_visited = 0;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->is_good = 1;
	new_node->q_type = -10;
	return (new_node);
}

void	link_new_nodes(t_tracker *holder, t_list *new_node_1, \
t_list *new_node_2)
{
	if (!(holder->head))
	{
		holder->head = new_node_1;
		new_node_1->next = new_node_2;
		new_node_2->prev = holder->head;
		holder->tail = new_node_2;
		return ;
	}
	holder->tail->next = new_node_1;
	new_node_1->next = new_node_2;
	new_node_1->prev = holder->tail;
	new_node_2->prev = new_node_1;
	holder->tail = new_node_2;
}

void	link_the_single_node(t_tracker *holder, t_list *new_node)
{
	if (!(holder->head))
	{
		holder->head = new_node;
		holder->tail = new_node;
		return ;
	}
	holder->tail->next = new_node;
	new_node->prev = holder->tail;
	holder->tail = new_node;
}

void	add_to_list_single(t_tracker *holder, char *input, int *start)
{
	t_list	*new_node;

	new_node = declare_node();
	if (input[*start] == '|' && input[*start + 1] == '|')
		new_node->content = ft_substr("||", 0, 2);
	else if (input[*start] == '&' && input[*start + 1] == '&')
		new_node->content = ft_substr("&&", 0, 2);
	else if (input[*start] == '<' && input[*start + 1] == '<')
		new_node->content = ft_substr("<<", 0, 2);
	else if (input[*start] == '>' && input[*start + 1] == '>')
		new_node->content = ft_substr(">>", 0, 2);
	else
		new_node->content = ft_substr(input, *start, 1);
	if ((input[*start] == '|' && input[*start + 1] == '|') || \
	(input[*start] == '&' && input[*start + 1] == '&') || \
	(input[*start] == '<' && input[*start + 1] == '<') || \
	(input[*start] == '>' && input[*start + 1] == '>'))
		*start += 1;
	link_the_single_node(holder, new_node);
}

void	add_to_list_double(t_tracker *holder, char *input, int start, int *end)
{
	t_list	*new_node_1;
	t_list	*new_node_2;

	new_node_1 = declare_node();
	new_node_2 = declare_node();
	new_node_1->content = ft_substr(input, start, (*end - start));
	if (input[*end] == '|' && input[*end + 1] == '|')
		new_node_2->content = ft_substr("||", 0, 2);
	else if (input[*end] == '&' && input[*end + 1] == '&')
		new_node_2->content = ft_substr("&&", 0, 2);
	else if (input[*end] == '<' && input[*end + 1] == '<')
		new_node_2->content = ft_substr("<<", 0, 2);
	else if (input[*end] == '>' && input[*end + 1] == '>')
		new_node_2->content = ft_substr(">>", 0, 2);
	else
		new_node_2->content = ft_substr(input, *end, 1);
	if ((input[*end] == '|' && input[*end + 1] == '|') || \
	(input[*end] == '&' && input[*end + 1] == '&') || \
	(input[*end] == '<' && input[*end + 1] == '<') || \
	(input[*end] == '>' && input[*end + 1] == '>'))
		*end += 1;
	link_new_nodes(holder, new_node_1, new_node_2);
}
