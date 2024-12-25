/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:26:08 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 15:42:21 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	only_second_pass(t_tree *leaf, int *check)
{
	if (!here_comp(leaf->content[0], "unset", 6))
	{
		if (!leaf->content[1])
			return (1);
		function_unset(leaf);
		return (1);
	}
	if (!here_comp(leaf->content[0], "env", 3) \
	&& count_twode(leaf->content) == 1)
		return (print_env(leaf->tree_h->env, leaf), 1);
	if (!here_comp(leaf->content[0], "exit", 5))
	{
		funcrtion_this_exit(leaf);
		*check = 1;
	}
	return (0);
}

int	function_for_echo(t_tree *leaf)
{
	int		i;
	int		up;
	int		index;
	char	*tmp;

	index = 1;
	if (!leaf->content[1])
		return (printf("\n"), 1);
	up = check_n(leaf->content, &index);
	while (leaf->content[index] && (!check_n(leaf->content, &index)))
		;
	(!here_comp(leaf->content[index], " ", 1) \
	|| !here_comp(leaf->content[index], "\t", 1)) && (index++, 0);
	while (leaf->content[index])
	{
		i = -1;
		tmp = leaf->content[index];
		while (tmp[++i])
			write(1, &tmp[i], 1);
		index++;
	}
	(up) && (printf("\n"), 0);
	return (1);
}

int	is_built(t_tree *leaf)
{
	int			check;
	int			th;

	if (!leaf->content[0] || (!here_comp(leaf->content[0], " ", 1) \
	|| !here_comp(leaf->content[0], "\t", 1)))
		return (0);
	leaf->content = check_space(leaf->content);
	check = only_pass(leaf);
	th = only_second_pass(leaf, &check);
	if (check || th)
	{
		if (here_para(5))
			exit_status(1, 0);
		else
			exit_status(0, 0);
		return (here_para(0), 1);
	}
	return (0);
}
