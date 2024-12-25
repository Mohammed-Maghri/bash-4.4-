/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:53:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 11:30:15 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	for_condition(t_tree *leaf, char *string, int export)
{
	if (count_twode(leaf->tree_h->export) > 0)
	{
		export = check_exist_in_env(copy_till_charac(string, '='), \
		leaf->tree_h->export);
		if (export > -1)
			leaf->tree_h->export = delet_from(leaf->tree_h->export, export);
	}
	leaf->tree_h->env = add_it_to_env(leaf->tree_h->env, string);
}

void	for_one_if(char *string, t_tree *leaf)
{
	if (check_exist_in_env(string, leaf->tree_h->env) == -1)
	{
		if (check_exist_in_env(string, leaf->tree_h->export) > -1)
		{
			leaf->tree_h->export = delet_from(leaf->tree_h->export, \
			check_exist_in_env(string, \
			leaf->tree_h->export));
		}
		leaf->tree_h->export = \
			add_it_to_env(leaf->tree_h->export, string);
	}
}

void	check_if_checked(char *string, t_tree *leaf)
{
	int	env;
	int	export;

	export = -1;
	env = check_exist_in_env(copy_till_charac(string, '='), leaf->tree_h->env);
	if (!here_comp(copy_till_charac(string, '='), "_", 1))
		return ;
	if (env == -1)
	{
		if (search_in_for(string, '+') == 1 && search_in_for(string, '=') == 1 \
		&& string[turn_position(string, '+') + 1] == '=')
			for_plus_check(string, leaf, &export);
		else if (search_in_for(string, '='))
			for_condition(leaf, string, export);
		else
			for_one_if(string, leaf);
	}
	else if (env > -1 && search_in_for(string, '=') == 1)
	{
		leaf->tree_h->env = add_it_to_env_index(leaf->tree_h->env, string, env);
	}
}
