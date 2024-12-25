/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:28:11 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/23 17:44:42 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_to_turn(char *path, char **env, t_tree *leaf)
{
	t_all_vars	for_func;

	(void)env ;
	if (count_word(path) == 1 && le_count(path) == 2)
	{
		if (check_string(path, "cd") != 0)
			return (-1);
		for_func.res_type = chdir(path);
		if (function_search_for("HOME=", leaf->tree_h->env) == 0)
			return (printf("Home Not set\n"), here_para(0), here_para(1), -1);
		if (check_last_elem(leaf->tree_h->env[return_place("HOME=", \
		leaf->tree_h->env)], '=') == -1)
			return (-1);
		for_func.env = copy_after_find(leaf->tree_h->env[return_place("HOME=", \
		leaf->tree_h->env)], '=');
		add_function_helper(for_func.env, leaf);
		for_func.this_path = chdir(for_func.env);
		if (for_func.this_path == -1)
			return (putstr("cd: no such file or directory: \n"), -1);
		return_extra(leaf, for_func.env);
		return (-1);
	}
	return (0);
}

int	check_res_type(int res_type, char *path, char *for_cd)
{
	if (res_type == -1 && count_word(path) == 2)
	{
		putstr("cd: no such file or directory: \n");
		putstr(for_cd);
		return (-1);
	}
	else if (res_type == -1 && count_word(path) > 2)
	{
		putstr("cd: string not in pwd: \n");
		putstr(for_cd);
		return (-1);
	}
	return (0);
}

int	check_cd(char *path)
{
	int	index ;

	index = 0;
	while (path[index] && path[index] == ' ')
		index++ ;
	if (path[index] == 'c')
	{
		index++ ;
		if (path[index] != 'd')
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	merge_function(char *path, char **env, t_tree *leaf)
{
	t_all_vars	for_func;

	for_func.hold = check_cd(path);
	if (for_func.hold == -1)
		return (-1);
	for_func.flag = check_if_to_turn(path, env, leaf);
	if (for_func.flag == -1)
		return (-1);
	return (0);
}
