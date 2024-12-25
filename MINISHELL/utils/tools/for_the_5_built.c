/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_the_5_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:41:45 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 19:40:56 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_check(t_tree *leaf)
{
	int	l;

	l = count_twode(leaf->content) - 1;
	if (!all_sapce(leaf->content[l]) \
	&& count_twode(leaf->content) == 2)
		leaf->content[l] = NULL;
	return (0);
}

void	for_the_export(char **env, t_tree *leaf)
{
	int	index;

	index = 2;
	while (env[index])
	{
		if (here_comp(env[index], " ", 1) && here_comp(env[index], "\t", 1))
		{
			if (!check_quotes_only(env[index]))
				check_if_checked(env[index], leaf);
		}
		index++;
	}
}

void	print_env(char **env, t_tree *leaf)
{
	int	index ;

	(void)leaf;
	index = 0;
	while (env[index])
	{
		printf("%s\n", env[index]);
		index++ ;
	}
}

int	turn_position(char *string, char here)
{
	int	index ;

	index = 0;
	while (string[index])
	{
		if (string[index] == here)
			break ;
		index++ ;
	}
	return (index);
}

void	add_function_export(t_tree *leaf)
{
	int	up;

	up = 0;
	while (leaf->tree_h->export[up])
	{
		printf("declare -x %s\n", leaf->tree_h->export[up]);
		up++;
	}
}
