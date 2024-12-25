/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:15:37 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:41:35 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	one_check(char string)
{
	if (string == '|' || string == '*' || string == ' ' \
	|| string == '{' || string == '}')
		return (-1);
	if (string == '-' || string == '&' || string == '^' \
	|| string == '\'' || string == '#')
		return (-1);
	if (string == '/' || string == '~' || string == ':' || string == '\t')
		return (-1);
	if (string == ';' || string == '|' || string == '@' || string == '$')
		return (-1);
	if (string == '!' || string == '?' || string == '\"' || string == ',')
		return (-1);
	if (string == '%' || string == '(' || string == ')' \
	|| string == '.' || string == '\\')
		return (-1);
	return (0);
}

int	check_if_it_valid(char string)
{
	if ((string >= '0' && string <= '9'))
	{
		return (-1);
	}
	return (0);
}

char	**delet_from(char **env, int position)
{
	int		index;
	char	**allocation;
	int		increment;

	if (count_twode(env) < 1)
		return (env);
	index = 0;
	allocation = gc((sizeof(char *) * (count_twode(env) + 1)), 0, 0, 0);
	increment = 0;
	while (env[index])
	{
		if (index != position)
		{
			allocation[increment] = return_line(env[index]);
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = NULL;
	return (allocation);
}

void	for_complete(char *string, t_tree *leaf)
{
	int		test;
	char	*merged;
	char	*copy ;

	copy = copy_till_charac(string, '=');
	test = check_exist_in_env(copy_till_charac(copy, '+'), \
		leaf->tree_h->export);
	if (test > -1)
		leaf->tree_h->export = delet_from(leaf->tree_h->export, test);
	copy = copy_after_find(string, '+');
	merged = merge_to(copy_till_charac(string, '+'), copy);
	leaf->tree_h->env = \
	add_it_to_env(leaf->tree_h->env, merged);
}

void	for_this_one(char *string, t_tree *leaf, int e)
{
	char	*copy ;
	char	*o;
	char	*merged;
	int		test;

	copy = copy_till_charac(string, '=');
	e = check_exist_in_env(copy_till_charac(copy, '+'), \
	leaf->tree_h->env);
	if (e > -1)
	{
		test = check_exist_in_env(copy_till_charac(copy, '+'), \
		leaf->tree_h->export);
		if (test > -1)
			leaf->tree_h->export = delet_from(leaf->tree_h->export, test);
		o = copy_after_find(string, '=');
		merged = merge_to(leaf->tree_h->env[e], o);
		leaf->tree_h->env = \
		add_it_to_env_index(leaf->tree_h->env, merged, e);
	}
	else
		for_complete(string, leaf);
}
