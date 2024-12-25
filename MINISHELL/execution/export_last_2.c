/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_last_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:58:34 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:36:55 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_to(char *string, char *merge)
{
	t_all_not_vars	t;

	t.index = 0;
	t.increment = 0;
	t.aloca = gc(sizeof(char) *(le_count(string) \
	+ le_count(merge) + 1), 0, 0, 0);
	while (string[t.index])
	{
		t.aloca[t.increment] = string[t.index];
		t.index++ ;
		t.increment++ ;
	}
	t.index = 0 ;
	if (!merge)
	{
		t.aloca[t.increment] = '\0';
		return (t.aloca);
	}
	while (merge[t.index])
	{
		t.aloca[t.increment] = merge[t.index];
		t.increment++ ;
		t.index++ ;
	}
	return (t.aloca[t.increment] = '\0', t.aloca);
}

char	*move_quotes(char *string)
{
	int		index ;
	int		increment ;
	char	*allocation ;

	increment = 0;
	index = 0;
	allocation = gc(sizeof(char **) * (le_count(string) + 1), 0, 0, 0);
	while (string[index])
	{
		if (string[index] != 34 && string[index] != 39)
		{
			allocation[increment] = string[index];
			increment++ ;
		}
		index++ ;
	}
	allocation[increment] = '\0';
	return (allocation);
}

char	**extract_check(char *string, t_tree *leaf)
{
	if (le_count(string) > 2)
	{
		if (search_in_for(string, '=') == 0)
			return (leaf->tree_h->env);
		else
		{
			if (search_in_for(string, '$') == 1)
			{
				return (add_it_to_env(leaf->tree_h->env, \
				expand_factory(string, leaf->tree_h->env, NULL, 0)));
			}
			if (check_exist_in_env(copy_till_charac(string, '='), \
			leaf->tree_h->env) > -1)
				return (function_to_check(leaf->tree_h->env, \
				check_exist_in_env(copy_till_charac(string, '='), \
				leaf->tree_h->env), string));
			else if (check_exist_in_env(copy_till_charac(string, '='), \
			leaf->tree_h->env) == -1)
				return (add_it_to_env(leaf->tree_h->env, string));
		}
	}
	return (leaf->tree_h->env);
}
