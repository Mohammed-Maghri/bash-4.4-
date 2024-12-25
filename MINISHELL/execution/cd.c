/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:33:18 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/22 10:12:42 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_this(char *first, char *second, int lenght)
{
	int	index;
	int	flag;

	flag = 0;
	index = 0;
	if (first[0] == second[0])
	{
		flag++ ;
		index++ ;
		while (first[index] && index < lenght)
		{
			if (first[index] == second[index])
				flag++ ;
			index++ ;
		}
		if (flag == lenght)
			return (1);
	}
	return (0);
}

int	function_search_for(char *value, char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (test_this(env[index], value, le_count(value)) == 1)
			return (1);
		index++ ;
	}
	return (0);
}

int	return_place(char *value, char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		if (test_this(env[index], value, le_count(value)) == 1)
			return (index);
		index++ ;
	}
	return (-1);
}

int	add_function_helper(char *for_current, t_tree *leaf)
{
	char	*get_current;

	get_current = getcwd(NULL, 0);
	if (!get_current)
		get_current = return_malloc(leaf->tree_h->extra_save);
	if (chdir(for_current) == -1 && count_twode(leaf->content) >= 2)
		return (free(get_current), 0);
	if (function_search_for("PWD=", leaf->tree_h->env) == 1)
		leaf->tree_h->env = add_it_to_env_index(leaf->tree_h->env, \
		merge_to("PWD=", for_current), \
		return_place("PWD=", leaf->tree_h->env));
	if (function_search_for("OLDPWD=", leaf->tree_h->env) == 0)
		leaf->tree_h->env = add_it_to_env(leaf->tree_h->env, \
			merge_to("OLDPWD=", get_current));
	else
		leaf->tree_h->env = add_it_to_env_index(leaf->tree_h->env, \
			merge_to("OLDPWD=", get_current), \
			return_place("OLDPWD=", leaf->tree_h->env));
	return (free(get_current), 0);
}

int	function_helper_two(t_tree *leaf)
{
	t_all_vars		for_func;
	t_all_not_vars	t;

	t.saftey = -1;
	leaf->saved = merge_path(leaf->saved, "..");
	t.saftey = chdir(leaf->saved);
	if (t.saftey == -1)
		print_error("error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory", NULL);
	for_func.env = getenv("USER");
	if (!for_func.env)
		return (-1);
	for_func.env = merge_to("/Users", for_func.env);
	add_function_helper(for_func.env, leaf);
	return (0);
}
