/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:07:07 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 11:30:52 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	for_plus_check(char *string, t_tree *leaf, int *export)
{
	int	index;

	index = 0;
	if (count_twode(leaf->tree_h->export) > 0)
	{
		index = check_exist_in_env(copy_till_charac(string, '=') \
			, leaf->tree_h->export);
		if (index > -1)
			leaf->tree_h->export = delet_from(leaf->tree_h->export, index);
	}
	if ((string[turn_position(string, '+') - 1] != ' ' || \
	string[turn_position(string, '+') - 1] != ' ') \
	&& string[turn_position(string, '+') + 1] == '=')
	{
		for_this_one(string, leaf, *export);
	}
}

int	check_last_elem(char *string, char to_check)
{
	int	whole_len ;

	whole_len = le_count(string) - 1;
	if (string[whole_len] == to_check)
		return (-1);
	return (0);
}

char	**check_space(char **string)
{
	int		i;

	i = -1;
	if (!string[0])
		return (string);
	while (string[0] && (!here_comp(string[0], " ", 1) \
	|| !here_comp(string[0], "\t", 1)))
	{
		i = -1;
		while (string[++i + 1])
			string[i] = string[i + 1];
		string[i] = NULL;
	}
	return (string);
}
